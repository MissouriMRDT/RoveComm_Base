---
layout: default
title: "07. Embedded (Arduino / Microcontroller) Guide"
---

# Chapter 07: Embedded (Arduino / Microcontroller) Guide

The embedded implementation of RoveComm (`MissouriMRDT/RoveComm_Arduino`) operates on the physical microcontroller boards distributed across the rover chassis. These boards -- primarily **Teensy 4.1** (ARM Cortex-M7 running at 600 MHz) and **STM32** controllers running the Arduino framework -- directly actuate drive motors, monitor battery cells, control robotic arm joints, and trigger science mechanisms.

---

## 1. Embedded Constraints & Architecture

Microcontroller environments impose strict constraints that differ radically from desktop operating systems:

1. **Zero Dynamic Allocation**: Calling `malloc()`, `free()`, or constructing dynamic `std::vector` objects within high-frequency control loops introduces memory fragmentation and non-deterministic latency. All RoveComm buffers are statically allocated at compile time.
2. **Polling vs Multi-Threading**: Most microcontrollers run bare-metal or on lightweight RTOSs without operating-system thread pools. RoveComm processing executes inside the main `loop()` through non-blocking `read()` checks.
3. **Hardware Ethernet PHY**: Teensy 4.1 utilizes the onboard 10/100 Mbit DP83825I PHY transceiver driven by the `NativeEthernet` library, providing direct hardware MAC and IP stack acceleration.

```text
+-----------------------------------------------------------------------------------+
| Teensy 4.1 Microcontroller Main Loop (100 Hz Cycle)                               |
+-----------------------------------------------------------------------------------+
           |                                                   ^
           | rovecomm.read() [Non-blocking]                    |
           v                                                   |
+--------------------------------------------------+           |
| Check for Incoming Packets                       |           |
| - Parse 6-byte header                            |           |
| - Switch on DataID:                              |           |
|   * SUBSCRIBE   -> Add to static subscriber list |           |
|   * UNSUBSCRIBE -> Remove from subscriber list   |           |
|   * Command ID  -> Update Actuator PWM/CAN state |           |
+--------------------------------------------------+           |
           |                                                   |
           v                                                   |
+--------------------------------------------------+           |
| Telemetry Transmission (Periodic @ 20 Hz)        |           |
| - Sample ADC / CAN bus sensor data               |-----------+
| - Iterate through static subscriber table        |
| - Transmit unicast UDP packets                   |
+--------------------------------------------------+
```

---

## 2. Production Firmware Example

The following code illustrates a production-ready microcontroller firmware loop implementing the Core Board drive receiver:

```cpp
#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>
#include <RoveComm.h>

// Static IP and Network Configuration from manifest.json
IPAddress boardIP(192, 168, 2, 110);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);
byte macAddress[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x02, 0x6E };

// RoveComm Ethernet UDP Instance
EthernetUDP udpSocket;
RoveCommEthernetUdp rovecomm(udpSocket);

// Actuator State
float targetLeftSpeed = 0.0f;
float targetRightSpeed = 0.0f;
unsigned long lastCommandTime = 0;
const unsigned long WATCHDOG_TIMEOUT_MS = 500;

void setup()
{
    Serial.begin(115200);
    Ethernet.begin(macAddress, boardIP, gateway, gateway, subnet);
    rovecomm.begin(ROVECOMM_ETHERNET_UDP_PORT);
    Serial.println("Core Board RoveComm Node Initialized.");
}

void loop()
{
    // 1. Process Incoming Packets
    rovecomm_packet packet;
    if (rovecomm.read(&packet))
    {
        switch (packet.data_id)
        {
            // Core Board DriveLeftRight Command (DataID: 3000)
            case 3000:
                if (packet.data_type == ROVECOMM_FLOAT_T && packet.data_count == 2)
                {
                    float* speeds = (float*)packet.data;
                    targetLeftSpeed = speeds[0];
                    targetRightSpeed = speeds[1];
                    lastCommandTime = millis();
                }
                break;

            // Power Management System E-Stop
            case 4000:
                targetLeftSpeed = 0.0f;
                targetRightSpeed = 0.0f;
                break;
        }
    }

    // 2. Hardware Watchdog Timeout (Safety Invariant)
    if (millis() - lastCommandTime > WATCHDOG_TIMEOUT_MS)
    {
        targetLeftSpeed = 0.0f;
        targetRightSpeed = 0.0f;
    }

    // 3. Command Motor Actuators via CAN Bus
    ApplyMotorPowers(targetLeftSpeed, targetRightSpeed);

    // 4. Stream Telemetry to Subscribers @ 20 Hz
    static unsigned long lastTelemetryTime = 0;
    if (millis() - lastTelemetryTime >= 50)
    {
        lastTelemetryTime = millis();
        float currentWheelSpeeds[6] = { targetLeftSpeed, targetLeftSpeed, targetLeftSpeed,
                                        targetRightSpeed, targetRightSpeed, targetRightSpeed };

        // Transmits MotorSpeeds (DataID: 3100) to all registered subscribers
        rovecomm.write(3100, ROVECOMM_FLOAT_T, 6, currentWheelSpeeds);
    }
}
```
