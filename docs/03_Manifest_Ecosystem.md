---
layout: default
title: "03. The Manifest Ecosystem & Automated CI Pipeline"
---

# Chapter 03: The Manifest Ecosystem & Automated CI Pipeline

In a large collegiate robotics team with dozens of engineers writing code in C++, C#, Python, and Arduino across separate microcontrollers, Jetson computers, and ground station dashboards, packet definitions inevitably diverge if maintained manually. 

To solve this, MRDT utilizes **`RoveComm_Base`** as the single authoritative source of truth. Every board IP, command, telemetry metric, error code, and enumeration is declared in a single JSON schema (`manifest.json`). Whenever a developer commits an update to `manifest.json`, an automated GitHub Actions CI pipeline regenerates human-readable documentation, emits cross-repository webhooks, updates git submodules across downstream language repositories, and triggers code generators to compile native language bindings (`RoveCommManifest.h`, `RoveCommBoards.cs`, etc.).

---

## 1. Anatomy of `manifest.json`

The root configuration of `manifest.json` defines protocol-wide network constants, primitive types, and system packets:

```json
{
    "ManifestSpecVersion": 3,
    "DataTypes": {
        "INT8_T": 0,
        "UINT8_T": 1,
        "INT16_T": 2,
        "UINT16_T": 3,
        "INT32_T": 4,
        "UINT32_T": 5,
        "FLOAT_T": 6,
        "DOUBLE_T": 7,
        "CHAR": 8
    },
    "dataSizes": [1, 1, 2, 2, 4, 4, 4, 8, 1],
    "SystemPackets": {
        "PING": 1,
        "PING_REPLY": 2,
        "SUBSCRIBE": 3,
        "UNSUBSCRIBE": 4,
        "INVALID_VERSION": 5,
        "NO_DATA": 6
    },
    "updateRate": 100,
    "ethernetUDPPort": 11000,
    "ethernetTCPPort": 12000,
    "MACaddressPrefix": [222, 173],
    "headerLength": 6,
    "RovecommManifest": { ... }
}
```

### Board Declaration Schema

Under `RovecommManifest`, each physical board or virtual simulator is declared as an object containing its static IP address, commands, telemetry, errors, and enums:

```json
"Core": {
    "Ip": "192.168.2.110",
    "Commands": {
        "DriveLeftRight": {
            "dataId": 3000,
            "dataType": "FLOAT_T",
            "dataCount": 2,
            "comments": "[LeftSpeed, RightSpeed] (-1 - 1) -> (-100% - 100%)"
        },
        "StateDisplay": {
            "dataId": 3010,
            "dataType": "UINT8_T",
            "dataCount": 1,
            "comments": "[State] (DisplayState)"
        }
    },
    "Telemetry": {
        "MotorSpeeds": {
            "dataId": 3100,
            "dataType": "FLOAT_T",
            "dataCount": 6,
            "comments": "[FL, ML, BL, FR, MR, BR] (-1 - 1) -> (-100% - 100%)"
        }
    },
    "Error": {
        "VESCFault": {
            "dataId": 3200,
            "dataType": "UINT8_T",
            "dataCount": 2,
            "comments": "[MotorID, FaultCode]"
        }
    },
    "enums": {
        "DisplayState": [
            "TELEOP",
            "AUTONOMY",
            "REACHED_GOAL"
        ]
    }
}
```

### Comment Formatting Conventions

To allow automated parsers and downstream developers to understand packet semantics instantly, the `comments` string follows a strict convention:
`"[Param1, Param2, ...] (Unit1, Unit2, ...) Description"`

- **Parameter Names**: Wrapped in brackets `[...]` matching array indices.
- **Units**: Wrapped in parentheses `(...)`, e.g., `(deg, m/s, A, V, mm)`. If a parameter is an enum, the enum name is placed in parentheses (e.g., `(DisplayState)`). If it is a normalized ratio, the range is specified: `(-1 - 1) -> (-100% - 100%)`.
- **Textual Description**: Explains physical behavior, safety limits, or operational nuances.

---

## 2. Automated README Generation

Inside `RoveComm_Base`, `.github/workflows/readme-generate.yml` runs whenever a commit is pushed to `master`:

```yaml
name: Generate README from Manifest
on:
  push:
    branches: ["master"]

permissions:
  contents: write

jobs:
  generate_readme:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v4
        with:
          fetch-depth: 0

      - name: Set up Python environment
        uses: actions/setup-python@v5
        with:
          python-version: "3.12"

      - name: Run README generation script
        run: |
          python .github/scripts/readme-generate.py --json ./manifest.json --output ./README.md
```

The script `.github/scripts/readme-generate.py` parses `manifest.json`, validates schema structure, and formats every board, command, telemetry metric, and error into GitHub-Flavored Markdown tables. If changes are detected, it commits `README.md` directly back to `master` with the message `[Automated] Human Readable Manifest Update`.

---

## 3. The Webhook Dispatch Pipeline

Immediately after updating `README.md`, the workflow notifies downstream implementations via GitHub's `repository_dispatch` REST API:

```yaml
      - name: Update RoveComm_CPP
        run: |
          curl -L \
          -X POST \
          -H "Accept: application/vnd.github+json" \
          -H "Authorization: Bearer ${{ secrets.RC_PAT_TOKEN }}" \
          -H "X-GitHub-Api-Version: 2022-11-28" \
          https://api.github.com/repos/MissouriMRDT/RoveComm_CPP/dispatches \
          -d '{"event_type":"rovecomm_sync", "client_payload":{}}'
```

### End-to-End Synchronization Architecture

```text
[Developer modifies manifest.json in RoveComm_Base]
                         |
                         v
          [Push to RoveComm_Base:master]
                         |
                         v
      [Workflow: readme-generate.yml executes]
        +-- 1. python readme-generate.py -> commits README.md
        \-- 2. Emits repository_dispatch (event_type: rovecomm_sync)
                         |
         +---------------+---------------+
         |                               |
         v                               v
[RoveComm_CPP Workflow]         [RoveComm_CSharp Workflow]
sync-rovecomm.yml               sync-rovecomm.yml
         |                               |
1. git submodule update         1. git submodule update
   (--remote data/RoveComm)        (--remote data/RoveComm)
2. Opens Automated PR to        2. Opens Automated PR to
   development branch              development branch
         |                               |
         v                               v
[Workflow: manifest.yml]        [Workflow: generate.yml]
Runs tools/RoveComm/parser.py   Runs tools/generate_boards.py
         |                               |
Generates:                      Generates:
src/RoveComm/RoveCommManifest.h RoveCommBoards.cs & Manifest.cs
         |                               |
3. Reviews & Merges PR          3. Reviews & Merges PR
         |                               |
         v                               v
[Submodule & Code Updated]      [Submodule & Code Updated]
```

---

## 4. Downstream Code Binding Generators

### C++ Code Generation (`RoveComm_CPP`)

In `MissouriMRDT/RoveComm_CPP`, the script `tools/RoveComm/parser.py` parses `data/RoveComm/manifest.json` and produces `src/RoveComm/RoveCommManifest.h`.

This header generates type-safe C++ namespaces and data structs:

```cpp
namespace manifest
{
    namespace Core
    {
        const AddressEntry IP = {192, 168, 2, 110};

        namespace Commands
        {
            const ManifestEntry DriveLeftRight = {3000, FLOAT_T, 2};
            const ManifestEntry DriveIndividual = {3001, FLOAT_T, 6};
            const ManifestEntry StateDisplay = {3010, UINT8_T, 1};
        }

        namespace Telemetry
        {
            const ManifestEntry MotorSpeeds = {3100, FLOAT_T, 6};
            const ManifestEntry MotorCurrents = {3101, FLOAT_T, 6};
        }

        namespace Enums
        {
            enum class DisplayState
            {
                TELEOP = 0,
                AUTONOMY = 1,
                REACHED_GOAL = 2
            };
        }
    }
}
```

This guarantees compile-time validation: if a developer attempts to send an invalid data ID or mismatching data type in Autonomy Software, the C++ compiler catches it immediately.

### C# Code Generation (`RoveComm_CSharp`)

In `MissouriMRDT/RoveComm_CSharp`, `tools/generate_boards.py` and `tools/parser.py` generate strongly-typed classes:

- **`RoveCommBoards.cs`**: Static definitions of each board with typed command methods and telemetry observables.
- **`RoveCommManifest.cs`**: In-memory dictionary enabling dynamic packet lookup by name or `DataID` for the BaseStation UI and diagnostic logs.

---

## 5. How to Add a New Packet to RoveComm (Tutorial)

When integrating a new sensor (such as the Doppler velocity sensor) or actuator into the rover network, follow this standard procedure:

1. **Clone `RoveComm_Base`**:
   ```bash
   git clone https://github.com/MissouriMRDT/RoveComm_Base.git
   cd RoveComm_Base
   git checkout -b feature/<sensor-name>-packet
   ```

2. **Edit `manifest.json`**:
   Navigate to the appropriate board section (e.g., `Nav` for navigation sensors). Choose an unused `dataId` in the board's range (e.g., `11100` for Nav telemetry):
   ```json
   "GPSVelocity": {
       "dataId": 11105,
       "dataType": "FLOAT_T",
       "dataCount": 3,
       "comments": "[VelX, VelY, VelZ] (m/s) Doppler GPS ground velocity vector in NED frame"
   }
   ```

3. **Verify Locally**:
   Run the README generator script locally to ensure JSON syntax is valid:
   ```bash
   python .github/scripts/readme-generate.py --json manifest.json --output README.md
   git diff README.md
   ```

4. **Submit Pull Request**:
   Commit `manifest.json` and push to GitHub. Open a Pull Request targeting `master`.
   Once reviewed by software leadership and merged, the automated CI pipeline automatically propagates the new packet to `RoveComm_CPP`, `RoveComm_CSharp`, and all dependent robotics repositories!
