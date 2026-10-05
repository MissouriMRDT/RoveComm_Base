---
layout: default
title: "04. C++ Implementation Guide"
---

# Chapter 04: C++ Implementation Guide

The C++ implementation of RoveComm (`MissouriMRDT/RoveComm_CPP`) is the high-performance communications engine powering both the onboard rover software stack (`Autonomy_Software`) and the Unreal Engine 5 digital twin simulator (`RoveSoSimulator`). Engineered in modern C++20, it provides asynchronous non-blocking network I/O, multi-threaded worker pools, and compile-time type safety.

---

## 1. Architecture & Threading Model

Network I/O in high-speed robotics must never block the main perception or path-planning control loops. In `RoveComm_CPP`, all socket listening and callback dispatches execute in dedicated background threads managed by `AutonomyThread`:

```text
+-----------------------------------------------------------------------------------+
| Autonomy_Software Main Thread (State Machine / Path Planning Loop @ 50 Hz)        |
+-----------------------------------------------------------------------------------+
       |                                                   ^
       | SendUDPPacket()                                   | Asynchronous Callback
       v                                                   | (Invoked on packet match)
+------------------------------------+  +-------------------------------------------+
| RoveCommUDP Send Queue             |  | RoveCommUDP Receiver Thread               |
| - Mutex-protected sendto()         |  | - select() / IOCP Event Loop              |
| - Direct network serialization     |  | - Header validation & unpack              |
+------------------------------------+  | - Dispatches to matching registered ID    |
                                        +-------------------------------------------+
```

### Platform Compatibility

`RoveComm_CPP` abstracts OS-level socket differences:
- **Linux (Jetson AGX Orin / Ubuntu 22.04 / 24.04)**: Standard non-blocking POSIX sockets using `sys/socket.h`, `netinet/in.h`, and `arpa/inet.h`.
- **Windows (Development PCs / Unreal Engine 5)**: Windows Sockets 2 (`ws2tcpip.h`, `winsock2.h`) with optional I/O Completion Ports (IOCP) for asynchronous message dispatching.

---

## 2. Core Classes & Data Structures

### `rovecomm::RoveCommPacket<T>`

The templated struct representing an in-memory packet. Type parameter `T` must be an arithmetic primitive matching the manifest (`int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t`, `float`, `double`, or `char`):

```cpp
template<typename T>
struct RoveCommPacket
{
    uint16_t unDataId;
    uint16_t unDataCount;
    manifest::DataTypes eDataType;
    std::vector<T> vData;
};
```

### `rovecomm::RoveCommUDP`

Manages UDP transmission, subscription tracking, and asynchronous datagram reception:

```cpp
class RoveCommUDP : AutonomyThread<void>
{
public:
    RoveCommUDP();
    ~RoveCommUDP();

    bool InitUDPSocket(int nPort);

    template<typename T>
    ssize_t SendUDPPacket(const RoveCommPacket<T>& stPacket, const char* cIPAddress, int nPort);

    template<typename T>
    void AddUDPCallback(std::function<void(const RoveCommPacket<T>&, const sockaddr_in&)> fnCallback, 
                        const uint16_t& unCondition);

    template<typename T>
    void RemoveUDPCallback(std::function<void(const RoveCommPacket<T>&, const sockaddr_in&)> fnCallback);
};
```

### `rovecomm::RoveCommTCP`

Manages connection-oriented TCP socket streams, boundary reassembly, and reliable command transmission:

```cpp
class RoveCommTCP : AutonomyThread<void>
{
public:
    RoveCommTCP();
    ~RoveCommTCP();

    bool InitTCPSocket(const char* cIPAddress, int nPort);

    template<typename T>
    ssize_t SendTCPPacket(const RoveCommPacket<T>& stData, const char* cClientIPAddress, int nClientPort);

    template<typename T>
    void AddTCPCallback(std::function<void(const RoveCommPacket<T>&)> fnCallback, 
                        const uint16_t& unCondition);

    void CloseTCPSocket();
};
```

---

## 3. Production Code Examples

### Example 1: Transmitting Drive Commands over UDP

This pattern demonstrates how the Autonomy control loop sends differential wheel speeds to the Core Board:

```cpp
#include "RoveComm/RoveComm.h"
#include "RoveComm/RoveCommManifest.h"

void DriveRover(rovecomm::RoveCommUDP& udpNode, float leftSpeed, float rightSpeed)
{
    // 1. Construct RoveComm packet using manifest metadata
    rovecomm::RoveCommPacket<float> drivePacket;
    drivePacket.unDataId = manifest::Core::Commands::DriveLeftRight.DATA_ID;
    drivePacket.eDataType = manifest::Core::Commands::DriveLeftRight.DATA_TYPE;
    drivePacket.unDataCount = manifest::Core::Commands::DriveLeftRight.DATA_COUNT; // 2
    drivePacket.vData = {leftSpeed, rightSpeed};

    // 2. Transmit to Core Board IP on default UDP port 11000
    const char* coreIP = manifest::Core::IP.IP_STR.c_str();
    ssize_t bytesSent = udpNode.SendUDPPacket(drivePacket, coreIP, ROVECOMM_ETHERNET_UDP_PORT);

    if (bytesSent < 0)
    {
        // Handle socket transmission error
    }
}
```

### Example 2: Subscribing to GPS Telemetry with Asynchronous Callbacks

This pattern demonstrates how an autonomy sensor driver subscribes to Nav Board telemetry and processes GPS updates asynchronously:

```cpp
#include "RoveComm/RoveComm.h"
#include "RoveComm/RoveCommManifest.h"
#include <iostream>

class GPSReceiver
{
private:
    rovecomm::RoveCommUDP m_udpNode;

    void OnGPSPoseReceived(const rovecomm::RoveCommPacket<double>& packet, const sockaddr_in& senderAddr)
    {
        if (packet.vData.size() >= 3)
        {
            double latitude  = packet.vData[0];
            double longitude = packet.vData[1];
            double altitude  = packet.vData[2];
            std::cout << "Received GPS Pose: Lat=" << latitude << ", Lon=" << longitude << "\n";
        }
    }

public:
    bool Initialize()
    {
        // 1. Bind local UDP listening socket
        if (!m_udpNode.InitUDPSocket(ROVECOMM_ETHERNET_UDP_PORT))
        {
            return false;
        }

        // 2. Register callback matching NavBoard GPSPose DataID (11100)
        m_udpNode.AddUDPCallback<double>(
            [this](const rovecomm::RoveCommPacket<double>& pkt, const sockaddr_in& addr) {
                this->OnGPSPoseReceived(pkt, addr);
            },
            manifest::Nav::Telemetry::GPSPose.DATA_ID
        );

        // 3. Send SUBSCRIBE packet to NavBoard
        rovecomm::RoveCommPacket<uint8_t> subPacket;
        subPacket.unDataId = manifest::SystemPackets::SUBSCRIBE;
        subPacket.eDataType = manifest::DataTypes::UINT8_T;
        subPacket.unDataCount = 0;
        subPacket.vData = {};

        m_udpNode.SendUDPPacket(subPacket, manifest::Nav::IP.IP_STR.c_str(), ROVECOMM_ETHERNET_UDP_PORT);
        return true;
    }
};
```

### Example 3: Transmitting Critical E-Stop Command over TCP

```cpp
#include "RoveComm/RoveComm.h"
#include "RoveComm/RoveCommManifest.h"

bool TriggerEmergencyStop(rovecomm::RoveCommTCP& tcpNode)
{
    // EStop packet on PMS Board (DataID: 4000, DataCount: 0)
    rovecomm::RoveCommPacket<uint8_t> estopPacket;
    estopPacket.unDataId = manifest::PMS::Commands::EStop.DATA_ID;
    estopPacket.eDataType = manifest::PMS::Commands::EStop.DATA_TYPE;
    estopPacket.unDataCount = 0;
    estopPacket.vData = {};

    ssize_t bytes = tcpNode.SendTCPPacket(
        estopPacket, 
        manifest::PMS::IP.IP_STR.c_str(), 
        ROVECOMM_ETHERNET_TCP_PORT
    );

    return (bytes > 0);
}
```

---

## 4. CMake Integration in Downstream Projects

To use `RoveComm_CPP` in any downstream C++ repository (such as `Autonomy_Software` or `RoveSoSimulator`):

```cmake
# Add RoveComm as submodule or subdirectory
add_subdirectory(external/rovecomm)

# Link to application target
target_link_libraries(Autonomy_Software PRIVATE RoveComm_CPP)
target_include_directories(Autonomy_Software PRIVATE external/rovecomm/src)
```
