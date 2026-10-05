# RoveComm Protocol Guide Table of Contents

Welcome to the **RoveComm Protocol Guide**! This is the centralized engineering reference and operations manual for the Missouri S&T Mars Rover Design Team inter-system communications architecture.

---

## Guide Navigation

### Core Protocol & Transport
- [01. Protocol Specification & Wire Format](01_Protocol_Specification.md)
- [02. Transport Layers: UDP vs TCP](02_Transport_Layers.md)
- [03. The Manifest Ecosystem & Automated CI Pipeline](03_Manifest_Ecosystem.md)

### Multi-Language Implementation Guides
- [04. C++ Implementation Guide](04_CPP_Implementation.md)
- [05. C# (.NET / Blazor) Implementation Guide](05_CSharp_Implementation.md)
- [06. Python Implementation Guide](06_Python_Implementation.md)
- [07. Embedded (Arduino / Microcontroller) Guide](07_Embedded_Implementation.md)

### Diagnostics & Integration Tooling
- [08. RoveComm Tester Software & Diagnostic Tooling](08_Tester_Software.md)
- [09. RoveSoDocs Hub Integration Playbook](09_Docs_Integration.md)
- [10. Pandoc Single Markdown & PDF Compilation](10_Pandoc_PDF_Build.md)

---

## External Resources & Documentation Portals

| Resource | URL | Description |
| :--- | :--- | :--- |
| **MRDT Documentation Portal** | [docs.themrdt.org](https://docs.themrdt.org/) | Central organization wiki, systems specifications, and team-wide documentation. |
| **RoveComm Base Repository** | [MissouriMRDT/RoveComm_Base](https://github.com/MissouriMRDT/RoveComm_Base) | Authoritative repository hosting `manifest.json` schema and automated CI sync. |
| **RoveComm C++ Doxygen API** | [docs.themrdt.org/rovecomm/_cpp/](https://docs.themrdt.org/rovecomm/_cpp/) | Doxygen-generated API documentation for the C++ library. |
| **RoveComm C# NuGet Package** | [nuget.org/packages/RoveComm](https://www.nuget.org/packages/RoveComm) | Official .NET NuGet package for BaseStation and C# services. |
| **Autonomy Software Binder** | [docs.themrdt.org/autonomy/_j/](https://docs.themrdt.org/autonomy/_j/) | Comprehensive engineering manual and operations guide for Autonomy. |
| **RoveComm Tester Utility** | [MissouriMRDT/RoveComm_Tester_Software](https://github.com/MissouriMRDT/RoveComm_Tester_Software) | Graphical desktop packet crafting, sniffing, and diagnostic tool. |

---

## Operational Cheat Sheet

| Operation | Command |
| :--- | :--- |
| **Generate Human-Readable README** | `python .github/scripts/readme-generate.py --json manifest.json --output README.md` |
| **Compile Complete PDF Manual** | `bash tools/compile_rovecomm_pandoc.sh` |
| **Launch Tester GUI** | `python RoveComm_Tester/RoveComm_Tester.py` |
| **Default Ethernet UDP Port** | `11000` |
| **Default Ethernet TCP Port** | `12000` |
| **Core Board Static IP** | `192.168.2.110` |
| **PMS Board Static IP** | `192.168.2.102` |
| **Nav Board Static IP** | `192.168.2.104` |
| **Autonomy Jetson Static IP** | `192.168.2.108` |
