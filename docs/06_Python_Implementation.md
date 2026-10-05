---
layout: default
title: "06. Python Implementation Guide"
---

# Chapter 06: Python Implementation Guide

The Python implementation of RoveComm (`MissouriMRDT/RoveComm_Python` and `RoveComm_Tester_Software/RoveComm_Tester/rovecomm_module/rovecomm.py`) is widely used across MRDT for auxiliary robotics services:
- Differential GPS correction injection on the Navigation Board (`NavBoard`).
- Video feed control and status telemetry on Raspberry Pi camera nodes.
- Automated hardware-in-the-loop diagnostic scripts and regression test suites.
- The desktop diagnostic GUI (`RoveComm_Tester_Software`).

---

## 1. Architecture of `rovecomm.py`

The Python implementation encapsulates packet packing and network transmission using standard library modules (`socket`, `struct`, `threading`, `select`):

```text
+-----------------------------------------------------------------------------------+
| Python Application Script (e.g., GPS Logger, NavBoard Bridge, Camera Streamer)    |
+-----------------------------------------------------------------------------------+
           |                                                   ^
           | rovecomm_node.write()                             | Callback / Queue
           v                                                   |
+-----------------------------------------------------------------------------------+
| RoveComm Python Core (rovecomm.py)                                                |
| - Header Packing: struct.pack(">BHHB", 3, data_id, data_count, data_type)         |
| - Background Daemon Thread: runs select.select() over listening UDP/TCP sockets   |
| - Callback Registry: maps data_id -> callback(packet)                             |
+-----------------------------------------------------------------------------------+
```

### Struct Packing & Header Format

In Python, binary conversion is performed with the format string `">BHHB"`:
- `>`: Network byte order (Big-Endian).
- `B`: 1-byte unsigned char (`Version = 3`).
- `H`: 2-byte unsigned short (`DataID`).
- `H`: 2-byte unsigned short (`DataCount`).
- `B`: 1-byte unsigned char (`DataType`).

```python
ROVECOMM_HEADER_FORMAT = ">BHHB"
ROVECOMM_VERSION = 3
```

---

## 2. Core Python Classes

### `RoveCommPacket`

```python
class RoveCommPacket:
    def __init__(self, data_id=0, data_type="b", data=(), ip="", port=11000):
        self.data_id = data_id
        self.data_type = data_type
        self.data_count = len(data)
        self.data = data
        self.ip_address = (ip, port) if ip else ("0.0.0.0", 0)
```

### `RoveComm` Node

```python
class RoveComm:
    def __init__(self, udp_port=11000, tcp_port=12000):
        # Initializes non-blocking sockets and launches background listening daemon
        ...

    def write(self, packet: RoveCommPacket, use_tcp=False):
        # Packs header and payload, transmits over UDP or TCP
        ...

    def set_callback(self, data_id: int, callback_fn):
        # Registers callback function triggered when packet with data_id arrives
        ...
```

---

## 3. Production Code Examples

### Example 1: Publishing GPS Doppler Velocity from Python

This script illustrates how the NavBoard Python bridge reads Doppler ground speed from an external GNSS receiver and publishes it over RoveComm for Autonomy Software:

```python
import time
from rovecomm_module.rovecomm import RoveComm, RoveCommPacket

# Initialize RoveComm Node
rc = RoveComm()

# Destination: Autonomy Jetson Computer
AUTONOMY_IP = "192.168.2.108"
AUTONOMY_PORT = 11000

# NavBoard GPSVelocity telemetry (DataID: 11105, 3 floats)
# Data: [VelocityNorth, VelocityEast, VelocityDown] in m/s
def publish_velocity(vel_north, vel_east, vel_down):
    packet = RoveCommPacket(
        data_id=11105,
        data_type="f",  # 4-byte IEEE 754 float
        data=(vel_north, vel_east, vel_down),
        ip=AUTONOMY_IP,
        port=AUTONOMY_PORT
    )
    rc.write(packet, use_tcp=False)

# Main publication loop @ 20 Hz
while True:
    # Simulated 1.2 m/s forward velocity
    publish_velocity(1.2, 0.0, 0.0)
    time.sleep(0.05)
```

### Example 2: Subscribing & Logging Rover Motor Currents

This script subscribes to Core Board motor currents and logs them to a CSV file for post-run energy analysis:

```python
import csv
import time
from rovecomm_module.rovecomm import RoveComm, RoveCommPacket

rc = RoveComm()
CORE_BOARD_IP = "192.168.2.110"

# Open CSV log file
csv_file = open("motor_currents.csv", "w", newline="")
writer = csv.writer(csv_file)
writer.writerow(["Timestamp", "FL", "ML", "BL", "FR", "MR", "BR"])

def on_motor_currents_received(packet: RoveCommPacket):
    if len(packet.data) == 6:
        timestamp = time.time()
        writer.writerow([timestamp] + list(packet.data))
        csv_file.flush()

# 1. Register callback for Core Board MotorCurrents (ID: 3101)
rc.set_callback(3101, on_motor_currents_received)

# 2. Subscribe to Core Board
sub_packet = RoveCommPacket(
    data_id=3,          # SUBSCRIBE
    data_type="B",
    data=(),
    ip=CORE_BOARD_IP,
    port=11000
)
rc.write(sub_packet)

print("Subscribed to Core Board. Logging motor currents... Press Ctrl+C to exit.")
try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    csv_file.close()
    print("Logging complete.")
```
