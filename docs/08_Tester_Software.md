---
layout: default
title: "08. RoveComm Tester Software & Diagnostic Tooling"
---

# Chapter 08: RoveComm Tester Software & Diagnostic Tooling

`RoveComm_Tester_Software` (`MissouriMRDT/RoveComm_Tester_Software`) is MRDT's primary graphical diagnostics and hardware-in-the-loop validation utility. Written in Python 3 using PyQt5, it enables software and electrical engineers to inspect raw packet streams, craft and inject arbitrary command packets, simulate missing rover subsystems during software development, and teleoperate rover mechanisms directly using an Xbox gamepad without running the full BaseStation suite.

---

## 1. Overview & System Architecture

`RoveComm_Tester_Software` couples a dual-pane PyQt5 interface with the underlying `rovecomm.py` networking engine:

```text
+-----------------------------------------------------------------------------------+
| RoveComm Tester Desktop Application (RoveComm_Tester.py)                          |
+-----------------------------------------------------------------------------------+
           |                                                   |
           v                                                   v
+---------------------------------------+   +---------------------------------------+
| Packet Sender Pane (QtSender.py)      |   | Packet Receiver Pane (QtReciever.py)  |
| - Dynamic manifest dropdowns          |   | - Real-time packet sniffer            |
| - Custom IP / Port / DataID crafting  |   | - Decodes binary payload to values    |
| - UDP & TCP transmission modes        |   | - Filter by DataID or source IP       |
| - Preset saving (Autonomy.json)       |   | - One-click SUBSCRIBE request button  |
+---------------------------------------+   +---------------------------------------+
           |                                                   ^
           +-------------------------+-------------------------+
                                     |
                                     v
+-----------------------------------------------------------------------------------+
| Xbox Controller Engine (XboxController.py)                                        |
| - Polls joysticks and triggers via Pygame                                         |
| - Normalizes axes to (-1.0 to 1.0)                                                |
| - Maps sticks directly to Core Board DriveLeftRight packets                       |
+-----------------------------------------------------------------------------------+
```

---

## 2. Installation & Quick Start

### Prerequisites

- Python 3.10+
- Pip package manager

### Setup Instructions

```bash
# Clone the repository
git clone --recurse-submodules https://github.com/MissouriMRDT/RoveComm_Tester_Software.git
cd RoveComm_Tester_Software

# Install dependencies
pip install -r requirements.txt
pip install PyQt5 pygame

# Launch the Tester GUI
python RoveComm_Tester/RoveComm_Tester.py
```

---

## 3. Core Modules Deep Dive

### A. The Packet Sender (`QtSender.py`)

The sender module allows interactive crafting of any packet registered in `manifest.json`:

1. **Board & Packet Dropdown**: Select the target board (e.g., `Core`, `PMS`, `Nav`) and command/telemetry name. The tool automatically populates the destination IP, port, default Data ID, and data type.
2. **Payload Editor**: Dynamically renders input fields based on `dataCount` and `dataType`. Array elements are validated against valid integer or float ranges before transmission.
3. **Transport Toggle**: Switch seamlessly between connectionless UDP (`Port 11000`) and reliable TCP (`Port 12000`).
4. **Configuration Presets**: Save frequently used test sequences (e.g., `1-Configs/Autonomy.json`, `DriveConfig.json`) to disk and recall them with a single click.

### B. The Packet Sniffer & Receiver (`QtReciever.py`)

The receiver module binds to local UDP port `11000` and TCP port `12000`:

1. **Live Feed Table**: Displays timestamp, source IP, Data ID, decoded packet name (resolved from manifest), data count, and unpacked values.
2. **Filtering**: Filter incoming traffic by specific `DataID` (e.g., isolate `3100 MotorSpeeds`) or source IP.
3. **Auto-Subscribe**: Selecting a board and clicking **Subscribe** emits an automated `SUBSCRIBE` packet (`DataID = 3`), prompting the board to begin streaming telemetry to the tester PC.

### C. Gamepad Teleoperation (`XboxController.py`)

For rapid chassis testing without deploying BaseStation, `RoveComm_Tester` interfaces directly with Xbox One and Series X controllers via `pygame.joystick`:

- **Left Stick Vertical**: Controls left wheel bank speed $(-1.0 \text{ to } 1.0)$.
- **Right Stick Vertical**: Controls right wheel bank speed $(-1.0 \text{ to } 1.0)$.
- **Right Bumper (Deadman Switch)**: Must be depressed for drive packets to transmit, preventing accidental rover runaway.
- **D-Pad**: Commands camera gimbals on the Multimedia Board (`LeftGimbal`, `RightGimbal`).

---

## 4. Common Diagnostic Workflows

### Diagnostic 1: Verifying Board Network Liveness (Ping)

When an embedded board fails to respond to commands:

1. Launch `RoveComm_Tester`.
2. Set Target IP to the board's static IP (e.g., `192.168.2.110` for Core).
3. Set Data ID to `1` (`PING`), Data Type to `UINT8_T`, Data Count to `0`.
4. Click **Send UDP**.
5. Observe the Receiver table: a healthy board responds within 10 ms with `DataID = 2` (`PING_REPLY`). If no reply is received, investigate Ethernet physical layer (link lights on the switch) or static IP configuration.

### Diagnostic 2: Simulating Sensor Telemetry for Autonomy Testing

When developing Autonomy navigation algorithms without physical rover hardware:

1. Launch `RoveComm_Tester` on a secondary computer (or local loopback).
2. Configure Sender to transmit `Nav Board GPSPose` (`DataID = 11100`, Data Type: `DOUBLE_T`, Count: 3).
3. Enter current test coordinates: `[37.95155, -91.77812, 320.0]`.
4. Enable **Continuous Send** @ 10 Hz.
5. In `Autonomy_Software`, verify that the State Machine detects valid GPS lock and transitions from `IDLE` to `NAVIGATING`.
