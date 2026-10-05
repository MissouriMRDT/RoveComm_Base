---
layout: default
title: "02. Transport Layers: UDP vs TCP"
---

# Chapter 02: Transport Layers: UDP vs TCP

RoveComm provides unified packet framing over both **User Datagram Protocol (UDP)** and **Transmission Control Protocol (TCP)**. Each transport layer is selected based on the specific operational characteristics of the subsystem: high-frequency streaming sensor telemetry requires minimal latency and can tolerate occasional packet drop, whereas discrete actuator switching, safety-critical E-Stop triggers, and large scientific datasets require guaranteed, ordered delivery.

---

## 1. Architectural Decision Matrix

The following decision matrix governs the transport layer selection across all MRDT subsystems:

| Metric | UDP Transport (`Port 11000`) | TCP Transport (`Port 12000`) |
| :--- | :--- | :--- |
| **Connection Model** | Connectionless (fire-and-forget datagrams) | Connection-oriented (persistent 3-way handshake stream) |
| **Delivery Guarantee** | Best-effort (packets may drop or arrive out of order) | Guaranteed delivery with automated link-layer retransmission |
| **Ordering** | No ordering guarantee | Guaranteed strict FIFO packet ordering |
| **Latency Profile** | Sub-millisecond latency; zero head-of-line blocking | Latency spikes during packet loss due to ACK timeouts |
| **Header Overhead** | Low (8-byte UDP header + 6-byte RoveComm header) | Higher (20-byte TCP header + 6-byte RoveComm header) |
| **Primary Use Cases** | - Drive wheel motor speeds<br>- Real-time IMU roll/pitch/yaw<br>- Continuous GPS Doppler velocities<br>- Teleoperation joystick commands<br>- LiDAR telemetry streams | - PMS E-Stop & Suicide triggers<br>- Power bus toggle commands<br>- Raman CCD spectrometer dataset downloads<br>- Autonomous mission waypoint injection<br>- Subsystem configuration updates |

---

## 2. UDP Transport & The Subscription Model

UDP operates without persistent connection overhead. On the rover network, microcontroller boards broadcast high-frequency telemetry (e.g., motor current at 50 Hz, IMU heading at 100 Hz) using the **RoveComm Subscription Model**.

### The UDP Subscription Lifecycle

Rather than broadcasting telemetry to all network devices (which degrades wireless bandwidth over 900 MHz Rocket links), RoveComm servers only stream telemetry to clients that have explicitly requested it:

```text
[Client Node (BaseStation / Autonomy)]                [Server Node (Core / PMS / Nav)]
                |                                                     |
                |------------- 1. SUBSCRIBE Packet (ID: 3) ---------->|
                |                 (Port 11000, DataCount: 0)          |
                |                                                     | [Registers Client IP & Port]
                |                                                     | [Adds to vSubscribers List]
                |                                                     |
                |<------------ 2. Telemetry Stream (ID: 3100) --------|
                |<------------ 3. Telemetry Stream (ID: 3101) --------|
                |<------------ 4. Telemetry Stream (ID: 3103) --------|
                |                                                     |
                |                                                     |
                |------------ 5. UNSUBSCRIBE Packet (ID: 4) --------->|
                |                 (Port 11000, DataCount: 0)          |
                |                                                     | [Removes Client from List]
                |                                                     |
```

### Subscription Protocol Implementation Details

1. **Subscribing**: To subscribe, a client transmits a UDP packet to the target board's IP address on port `11000` with `DataID = 3` (`SUBSCRIBE`), `DataType = UINT8_T`, and `DataCount = 0`.
2. **Subscriber Storage**: The receiving board records the sender's IP address and UDP port in an internal table. In `RoveComm_CPP`, this is bounded by `ROVECOMM_ETHERNET_UDP_MAX_SUBSCRIBERS = 10`.
3. **Telemetry Streaming**: During each board execution loop (typically 10 ms to 100 ms intervals), the board iterates through its active subscribers and sends copies of its telemetry packets using unicast `sendto()`.
4. **Unsubscribing**: When a client shuts down or changes operational modes, it sends an `UNSUBSCRIBE` packet (`DataID = 4`) to remove itself from the server's streaming loop.
5. **Heartbeat & Stale Subscriber Pruning**: If a subscriber fails to send any packet or heartbeat for over 10 seconds, embedded firmware automatically evicts the stale subscriber to conserve network resources.

---

## 3. TCP Transport & Stream Framing

TCP provides reliable, ordered data transfer over port `12000`. However, because TCP is a byte-stream protocol rather than a message-oriented protocol, multiple RoveComm packets may arrive coalesced within a single TCP segment, or a single packet may be fragmented across multiple TCP reads.

### Handling TCP Stream Delimitation

Implementations of RoveComm over TCP **MUST** implement stateful buffering to extract individual packets cleanly:

```text
Incoming TCP Stream Buffer:
[ 0x03 | 0x0F 0xA0 | 0x00 0x02 | 0x06 | 0x3F 0x80 0x00 0x00 | 0x3F 0x80 0x00 0x00 ] [ 0x03 ...
|<- - - - - - - - - - Fixed 6-Byte Header - - - - - - - ->|<- - - Payload (8 Bytes) - ->|
|< - - - - - - - - - - - - - - - Complete RoveComm Packet (14 Bytes) - - - - - - - - - >|
```

### TCP Frame Extraction Algorithm

```cpp
void ProcessTCPBuffer(std::vector<uint8_t>& receiveBuffer)
{
    while (receiveBuffer.size() >= ROVECOMM_PACKET_HEADER_SIZE)
    {
        // 1. Inspect Header
        uint8_t version = receiveBuffer[0];
        if (version != ROVECOMM_VERSION)
        {
            // Drop corrupt byte and resynchronize
            receiveBuffer.erase(receiveBuffer.begin());
            continue;
        }

        uint16_t dataId = (receiveBuffer[1] << 8) | receiveBuffer[2];
        uint16_t dataCount = (receiveBuffer[3] << 8) | receiveBuffer[4];
        uint8_t dataType = receiveBuffer[5];
        size_t elementSize = GetDataTypeSize(dataType);
        size_t totalPacketSize = ROVECOMM_PACKET_HEADER_SIZE + (dataCount * elementSize);

        // 2. Check if complete packet has arrived
        if (receiveBuffer.size() < totalPacketSize)
        {
            // Incomplete packet; wait for next TCP socket read
            break;
        }

        // 3. Extract and dispatch packet
        RoveCommData packetBytes;
        std::copy(receiveBuffer.begin(), receiveBuffer.begin() + totalPacketSize, packetBytes.unBytes);
        DispatchCallbacks(packetBytes);

        // 4. Remove processed frame from buffer
        receiveBuffer.erase(receiveBuffer.begin(), receiveBuffer.begin() + totalPacketSize);
    }
}
```

---

## 4. Connection State Machine & Fault Recovery

### Link Monitoring & Keep-Alives

Wireless connections in the desert (Hanksville, UT for URC) experience RF multipath interference and periodic link drops. The TCP client layer (in Autonomy or BaseStation) implements an automated state machine for fault recovery:

1. **Periodic Ping**: Every 1,000 ms of socket inactivity, the client transmits a `PING` packet (`DataID = 1`).
2. **Ping Timeout**: If the server fails to respond with a `PING_REPLY` (`DataID = 2`) within 2,500 ms, the connection is marked broken.
3. **Graceful Reconnection**: The client closes the existing socket file descriptor, resets socket buffers, waits for an exponential backoff period (250 ms, 500 ms, 1000 ms, max 3000 ms), and attempts `connect()` until the board is back online.
4. **Actuator Safety Timeout**: All embedded actuator boards (Drive, Arm, Science) feature a 500 ms watchdog. If no valid command packet is received within 500 ms, the board immediately sets motor outputs to zero (`EStop` safe state).
