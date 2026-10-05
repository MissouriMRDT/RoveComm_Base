---
layout: default
title: "01. Protocol Specification & Wire Format"
---

# Chapter 01: Protocol Specification & Wire Format

The **RoveComm** protocol is the custom application-layer binary messaging protocol engineered by the Missouri S&T Mars Rover Design Team (MRDT). It interconnects all computing nodes on the rover and ground control station—including embedded microcontrollers (Teensy 4.1, STM32, SAM), single-board computers (NVIDIA Jetson AGX Orin, Raspberry Pi 5), high-level autonomy software stacks, simulation engines (Unreal Engine 5), and the mission control web dashboard (Blazor BaseStation).

This chapter defines the low-level wire format, byte framing, data types, system-reserved packets, and network IP routing topology for **RoveComm Version 3**.

---

## 1. Design Philosophy & Requirements

Traditional general-purpose messaging protocols (such as ROS 2 DDS, Protobuf over gRPC, or JSON over WebSockets) introduce substantial serialization overhead, large memory footprints, and complex runtime dependencies that cannot operate efficiently on resource-constrained embedded microcontrollers. 

RoveComm is engineered around four core tenets:

1. **Minimal Header Overhead**: A fixed 6-byte header allows embedded microcontrollers to parse packets with zero dynamic memory allocation and minimal CPU cycles.
2. **Deterministic Serialization**: Strict big-endian network byte ordering guarantees binary interoperability across heterogeneous CPU architectures (x86_64, ARM Cortex-A78AE, ARM Cortex-M7, and RISC-V).
3. **Schema-Driven Network Contract**: The entire team's networking catalog—every board, IP address, command, telemetry stream, error flag, and enum—is declared in a single central repository (`RoveComm_Base/manifest.json`), eliminating packet definition drift across multidisciplinary subteams.
4. **Dual Transport Support**: Native abstraction over both low-latency connectionless UDP (for high-frequency sensor telemetry and teleoperation drive commands) and connection-oriented TCP (for mission-critical state transitions, file transfers, and E-Stop commands).

---

## 2. Wire Format & Header Layout

Every RoveComm packet transmitted over Ethernet or Wi-Fi begins with an identical **6-byte header**, followed by an optional variable-length payload:

```text
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| RoveComm Ver  |            Data ID            |  Data Count   |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| (Cnt cont'd)  |   Data Type   |        Payload Data ...       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                            ...                                |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

### Byte-by-Byte Header Field Breakdown

| Byte Offset | Field Name | Data Type | Description |
| :--- | :--- | :--- | :--- |
| **Byte 0** | `RoveComm Version` | `uint8_t` | Protocol specification version. For current MRDT rovers, this value **MUST** equal `3` (`0x03`). Packets with mismatching versions are rejected. |
| **Bytes 1–2** | `Data ID` | `uint16_t` | Unique identifier (0–65535) denoting the command, telemetry stream, or error type as registered in `manifest.json`. Big-endian network byte order. |
| **Bytes 3–4** | `Data Count` | `uint16_t` | Number of elements of type `Data Type` contained in the following payload. Big-endian network byte order. |
| **Byte 5** | `Data Type` | `uint8_t` | Primitive data type enum (values `0` to `8`) defining how the payload bytes must be decoded. |
| **Bytes 6+** | `Data Payload` | Variable | The binary array of data elements. Total payload byte size is calculated as $\text{DataCount} \times \text{sizeof}(\text{DataType})$. |

### Maximum Packet Limits

- **Header Size**: Exactly 6 bytes (`ROVECOMM_PACKET_HEADER_SIZE = 6`).
- **Maximum Data Count**: 65,535 elements (`ROVECOMM_PACKET_MAX_DATA_COUNT = 65535`).
- **Standard Maximum Transmission Unit (MTU)**: For standard Ethernet UDP datagrams without IP fragmentation, payloads are typically kept under 1,466 bytes ($1500 - 20\text{ (IP)} - 8\text{ (UDP)} - 6\text{ (RoveComm)}$). Large telemetry bursts (such as Raman CCD spectrometer readings consisting of 2,560 elements) are split into multiple smaller packets (`RamanReading_Part1` through `RamanReading_Part5`) to prevent packet fragmentation.

---

## 3. Endianness & Network Byte Ordering

All multi-byte numeric fields in both the RoveComm header (`DataID`, `DataCount`) and the payload (`int16_t`, `uint16_t`, `int32_t`, `uint32_t`, `float`, `double`) **MUST** be transmitted in **Big-Endian (Network Byte Order)**.

When serializing and deserializing packets on little-endian architectures (such as x86 and ARM):

- **16-bit integers**: Converted using `htons()` (Host TO Network Short) and `ntohs()`.
- **32-bit integers**: Converted using `htonl()` (Host TO Network Long) and `ntohl()`.
- **64-bit integers & doubles**: Converted using 64-bit bit-shift swapping (`htonll()` and `ntohll()`).
- **Single-precision floats (`FLOAT_T`)**: Serialized according to IEEE 754 standard, with the 4 raw bytes swapped via `htonl()` before network transmission.
- **8-bit integers & characters (`INT8_T`, `UINT8_T`, `CHAR`)**: Transmitted directly without byte-swapping.

```cpp
// 64-bit Big-Endian Byte Swap Helper
#define htonll(x) ((1 == htonl(1)) ? (x) : (((uint64_t) htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t) ((x) >> 32)))
#define ntohll(x) ((1 == ntohl(1)) ? (x) : (((uint64_t) ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t) ((x) >> 32)))
```

---

## 4. Supported Data Types Reference

RoveComm defines 9 standard primitive data types mapped to fixed integer identifiers in `manifest.json`:

| Enum ID | Type Name | Byte Size | Description | C++ Equivalent | C# (.NET) Type | Python `struct` Code |
| :---: | :--- | :---: | :--- | :--- | :--- | :---: |
| `0` | `INT8_T` | 1 | Signed 8-bit integer | `int8_t` | `sbyte` | `'b'` |
| `1` | `UINT8_T` | 1 | Unsigned 8-bit integer / byte / bitmask | `uint8_t` | `byte` | `'B'` |
| `2` | `INT16_T` | 2 | Signed 16-bit integer | `int16_t` | `short` | `'h'` |
| `3` | `UINT16_T` | 2 | Unsigned 16-bit integer | `uint16_t` | `ushort` | `'H'` |
| `4` | `INT32_T` | 4 | Signed 32-bit integer | `int32_t` | `int` | `'l'` |
| `5` | `UINT32_T` | 4 | Unsigned 32-bit integer | `uint32_t` | `uint` | `'L'` |
| `6` | `FLOAT_T` | 4 | IEEE 754 single-precision floating point | `float` | `float` | `'f'` |
| `7` | `DOUBLE_T` | 8 | IEEE 754 double-precision floating point | `double` | `double` | `'d'` |
| `8` | `CHAR` | 1 | 8-bit ASCII character / null-terminated string | `char` | `char` | `'c'` |

---

## 5. System Reserved Packets (Control IDs 1–6)

Data IDs `1` through `6` are globally reserved across all boards for protocol control and connection management. They must not be assigned to board-specific commands or telemetry:

| System Data ID | Packet Name | Transport | Description |
| :---: | :--- | :---: | :--- |
| `1` | **`PING`** | UDP / TCP | Sent to verify socket liveness and network connectivity. The receiving node must respond immediately with a `PING_REPLY`. Payload is empty (`DataCount = 0`). |
| `2` | **`PING_REPLY`** | UDP / TCP | Transmitted in response to a `PING` packet. Carries round-trip latency verification. Payload is empty (`DataCount = 0`). |
| `3` | **`SUBSCRIBE`** | UDP | Instructs the receiving UDP server to add the sender's IP and port to its active telemetry distribution list. Payload is empty (`DataCount = 0`). |
| `4` | **`UNSUBSCRIBE`** | UDP | Instructs the receiving UDP server to remove the sender from its active telemetry distribution list. Payload is empty (`DataCount = 0`). |
| `5` | **`INVALID_VERSION`** | UDP / TCP | Emitted by a receiving node when an incoming packet's `Version` field does not match the receiver's supported version. Payload contains the receiver's supported version as `UINT8_T`. |
| `6` | **`NO_DATA`** | UDP / TCP | Sent as a heartbeat or acknowledgment indicating zero payload update. |

---

## 6. Network IP & Subnet Topology

MRDT operates an isolated physical Gigabit Ethernet and 5 GHz / 900 MHz Ubiquiti wireless network. Computing devices and microcontroller boards use static IP addresses partitioned into dedicated operational subnets:

### Standard Port Allocations

- **`11000`**: Default Ethernet UDP Port (`ethernetUDPPort`).
- **`12000`**: Default Ethernet TCP Port (`ethernetTCPPort`).

### Static Subnet Allocations

```text
+-----------------------+--------------------+---------------------------------------------+
| Subnet Range          | Network Domain     | Description & Primary Devices               |
+-----------------------+--------------------+---------------------------------------------+
| 192.168.2.0/24        | Main Rover Subnet  | Core Board (192.168.2.110)                  |
|                       |                    | Power Management System - PMS (.102)        |
|                       |                    | Navigation Board (.104)                     |
|                       |                    | Multimedia Board (.106)                     |
|                       |                    | Autonomy Jetson Computer (.108)             |
|                       |                    | Robotic Arm Controller (.112)               |
| 192.168.3.0/24        | Science Subnet     | Raman Spectrometer Board (192.168.3.105)    |
|                       |                    | Science Carousel Controller (.106)          |
| 192.168.100.0/24      | Drone Subnet       | Drone Flight Controller (192.168.100.102)   |
| 192.168.254.0/24      | Network Core       | Rover Managed Switch (192.168.254.1)        |
|                       |                    | BaseStation Managed Switch (192.168.254.2)  |
| 10.0.0.0/24           | RF Rocket Links    | Rover 900 MHz Ubiquiti Rocket (10.0.0.3)    |
|                       |                    | BaseStation 900 MHz Rocket (10.0.0.4)       |
|                       |                    | Rover 5 GHz Ubiquiti Rocket (10.0.0.19)     |
|                       |                    | BaseStation 5 GHz Rocket (10.0.0.20)        |
| 127.0.0.1             | Local Loopback     | RoveSoSimulator (127.0.0.1)                 |
+-----------------------+--------------------+---------------------------------------------+
```

---

## 7. Packet Validation Rules

When receiving a RoveComm frame, implementations **MUST** execute the following verification pipeline before passing data to subsystem callbacks:

1. **Length Check**: Total bytes received must be $\ge 6$ bytes.
2. **Version Check**: Byte 0 must equal `ROVECOMM_VERSION` (`3`). If invalid, emit an `INVALID_VERSION` packet back to the sender and discard.
3. **Payload Bound Check**: The expected payload size ($S = \text{DataCount} \times \text{DataTypeSize}$) must equal $\text{TotalBytesReceived} - 6$. If fewer bytes are present, the frame is corrupted and must be dropped.
4. **Data ID Verification**: Ensure `DataID` is known in the board's manifest before executing actuator commands.
