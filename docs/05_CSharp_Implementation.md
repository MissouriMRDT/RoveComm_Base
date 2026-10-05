---
layout: default
title: "05. C# (.NET / Blazor) Implementation Guide"
---

# Chapter 05: C# (.NET / Blazor) Implementation Guide

The C# implementation of RoveComm (`MissouriMRDT/RoveComm_CSharp`) is the official networking layer for MRDT's mission control software (`Basestation_Software_Blazor`). Hosted publicly on [NuGet.org](https://www.nuget.org/packages/RoveComm), it integrates natively with modern .NET 8 / 9 asynchronous paradigms, dependency injection, and Blazor web components.

---

## 1. Architecture & BaseStation Integration

Modern BaseStation runs as a high-performance Blazor web application. `RoveComm_CSharp` is engineered as a thread-safe singleton service (`RoveCommService`) that runs in the background of the ASP.NET runtime, handling non-blocking socket reads via `async`/`await` and dispatching telemetry updates to web UI components via C# delegates:

```text
+-----------------------------------------------------------------------------------+
| Blazor Web UI / Razor Components (DrivePage.razor, BatteryWidget.razor)           |
+-----------------------------------------------------------------------------------+
           |                                                   ^
           | RoveCommService.SendPacketAsync()                 | Event Callback
           v                                                   | (Invokes StateHasChanged)
+-----------------------------------------------------------------------------------+
| RoveCommService (ASP.NET Dependency-Injected Singleton)                           |
| - UdpClient & TcpClient asynchronous message loop                                 |
| - BinaryPrimitives big-endian packing (BinaryPrimitives.WriteInt16BigEndian)      |
| - ConcurrentDictionary<int, List<Delegate>> subscriber dispatch table             |
+-----------------------------------------------------------------------------------+
```

---

## 2. Core API Reference

### `RoveCommPacket<T>`

Represents a strongly-typed packet. Valid generic types: `sbyte`, `byte`, `short`, `ushort`, `int`, `uint`, `float`, `double`, or `char`:

```csharp
namespace RoveComm;

public class RoveCommPacket<T>
{
    public int DataID { get; set; }
    public int DataCount => Data.Count;
    public RoveCommDataType DataType { get; init; }
    public List<T> Data { get; set; }

    public RoveCommPacket(int dataId, IEnumerable<T> data);
    public RoveCommPacket(int dataId, int dataCount);
    public RoveCommHeader GetHeader();
}
```

### `RoveCommService`

The central manager for network sockets and subscription delegates:

```csharp
public class RoveCommService
{
    // Transmit packets
    public async Task<int> SendPacket<T>(RoveCommPacket<T> packet, string ip, int port = 11000);

    // Register callbacks for incoming packets
    public void Subscribe<T>(int dataId, RoveCommCallback<T> callback);
    public void Unsubscribe<T>(int dataId, RoveCommCallback<T> callback);

    // TCP client connection management
    public async Task ConnectTCP(string ip, int port = 12000);
}
```

---

## 3. Production Code Examples

### Example 1: Registering `RoveCommService` in `Program.cs`

In a Blazor or ASP.NET application, register RoveComm as a singleton service:

```csharp
using RoveComm;

var builder = WebApplication.CreateBuilder(args);

// Add Blazor services
builder.Services.AddRazorPages();
builder.Services.AddServerSideBlazor();

// Register RoveComm as a Singleton
builder.Services.AddSingleton<RoveCommService>();

var app = builder.Build();
app.Run();
```

### Example 2: Subscribing to Telemetry in a Blazor Component

This Razor component binds real-time battery voltage and current from the PMS Board (`DataID = 4100`) directly to a UI widget:

```razor
@page "/pms-monitor"
@using RoveComm
@inject RoveCommService RoveComm
@implements IDisposable

<h3>Power Management System Telemetry</h3>

@if (batteryData != null)
{
    <p><strong>Pack Current:</strong> @batteryData[0] A</p>
    <p><strong>Aux Current:</strong> @batteryData[1] A</p>
    <p><strong>Cell 1 Voltage:</strong> @batteryData[6] V</p>
    <p><strong>Cell 2 Voltage:</strong> @batteryData[7] V</p>
}
else
{
    <p><em>Waiting for PMS telemetry stream...</em></p>
}

@code {
    private List<float>? batteryData;

    protected override async Task OnInitializedAsync()
    {
        // 1. Register callback for PMS CurrentAndVoltage packet (ID: 4100)
        RoveComm.Subscribe<float>(4100, OnPMSDataReceived);

        // 2. Transmit SUBSCRIBE request to PMS Board IP (192.168.2.102)
        var subPacket = new RoveCommPacket<byte>(3, Array.Empty<byte>());
        await RoveComm.SendPacket(subPacket, "192.168.2.102", 11000);
    }

    private Task OnPMSDataReceived(RoveCommPacket<float> packet)
    {
        batteryData = packet.Data;
        InvokeAsync(StateHasChanged);
        return Task.CompletedTask;
    }

    public void Dispose()
    {
        // Clean up callback when component unmounts
        RoveComm.Unsubscribe<float>(4100, OnPMSDataReceived);
    }
}
```

### Example 3: Dispatching Drive Commands from Joystick Input

```csharp
public async Task UpdateDriveSpeeds(float leftPower, float rightPower)
{
    // Clamp speeds to valid normalized range (-1.0 to 1.0)
    leftPower = Math.Clamp(leftPower, -1.0f, 1.0f);
    rightPower = Math.Clamp(rightPower, -1.0f, 1.0f);

    // Core Board DriveLeftRight command (DataID: 3000, 2 floats)
    var packet = new RoveCommPacket<float>(3000, new float[] { leftPower, rightPower });

    // Send UDP packet to Core Board IP
    await _roveCommService.SendPacket(packet, "192.168.2.110", 11000);
}
```
