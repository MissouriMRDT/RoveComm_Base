# RoveComm Base

This is the repository that contains `manifest.json`, which is used by all RoveComm implementations as a schema for
sending and parsing RoveComm packets. These are the current implementations of RoveComm so far:

- [RoveComm_Arduino](https://github.com/MissouriMRDT/RoveComm_Arduino) -- Used by embedded microcontrollers.
  Written for the Arduino framework.
- [RoveComm_CPP](https://github.com/MissouriMRDT/RoveComm_CPP) -- Used by
  [Autonomy_Software](https://github.com/MissouriMRDT/Autonomy_Software) and the
  [Simulator](https://github.com/MissouriMRDT/RoveSoSimulator). Written in multithreaded C++.
- [RoveComm_Python](https://github.com/MissouriMRDT/RoveComm_Python)
  -- Used by [RoveCommTester](https://github.com/MissouriMRDT/RoveComm_Tester_Software) and
  [Old Autonomy](https://github.com/MissouriMRDT/Autonomy_Software_Python). It is also used where shell scripts need to
  interact with RoveComm, such as on [NavBoard](https://github.com/MissouriMRDT/Differential_GPS) and on the Camera PIs.
- [RoveComm_CSharp](https://github.com/MissouriMRDT/RoveComm_CSharp) -- Used by
  [New BaseStation](https://github.com/MissouriMRDT/Basestation_Software_Blazor). Written for C# .NET projects.
  Hosted on [nuget.org](https://www.nuget.org/packages/RoveComm).
- [RoveComm_TypeScript](https://github.com/MissouriMRDT/BaseStation_Software/blob/dev/src/Core/RoveProtocol/Rovecomm.ts)
  -- Used by [Old BaseStation](https://github.com/MissouriMRDT/BaseStation_Software). Written for Node.js apps.
- Though not actively maintained, there are also implementations for
  [Dart](https://github.com/MissouriMRDT/RoveSoRemote/blob/master/rove_so_remote/lib/RoveComm.dart) and
  [Swift](https://github.com/MissouriMRDT/RoveComm_Swift).

# RoveComm Manifest

## Core Board

**IP**: 192.168.2.110

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **DriveLeftRight** | 3000 | `FLOAT_T` | 2 | [LeftSpeed, RightSpeed] (-1 - 1) -> (-100% - 100%) |
| **DriveIndividual** | 3001 | `FLOAT_T` | 6 | [LF, LM, LR, RF, RM, RR] (-1 - 1) -> (-100% - 100%) |
| **WatchdogOverride** | 3002 | `UINT8_T` | 1 | [Enabled] |
| **LeftGimbal** | 3003 | `INT16_T` | 2 | [Pan, Tilt] (0 - 180) |
| **RightGimbal** | 3004 | `INT16_T` | 2 | [Pan, Tilt] (0 - 180) |
| **BackGimbal** | 3005 | `INT16_T` | 2 | [Pan, Tilt] (0 - 180) |
| **LEDRGB** | 3006 | `UINT8_T` | 3 | [R, G, B] (brightness 0 - 255) |
| **BackImage** | 3007 | `UINT32_T` | 256 | [Color] (RGBA) |
| **InternalRGB** | 3008 | `UINT8_T` | 3 | [R, G, B] (brightness 0 - 255) |
| **InternalImage** | 3009 | `UINT32_T` | 256 | [Color] (RGBA) |
| **StateDisplay** | 3010 | `UINT8_T` | 1 | [State] (DisplayState) |
| **Brightness** | 3011 | `UINT8_T` | 1 | [Brightness] (0 - 255) |
| **SetWatchdogMode** | 3012 | `UINT8_T` | 1 | [Mode] (0: Teleop 1: Autonomy) |
| **LEDText** | 3013 | `CHAR` | 256 | [Message] (null terminated string) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **MotorSpeeds** | 3100 | `FLOAT_T` | 6 | [FL, ML, BL, FR, MR, BR] (-1 - 1) -> (-100% - 100%) |
| **MotorCurrents** | 3101 | `FLOAT_T` | 6 | [FL, ML, BL, FR, MR, BR] (A) |
| **VESCCurrents** | 3102 | `FLOAT_T` | 6 | [FL, ML, BL, FR, MR, BR] (A battery side) |
| **IMUData** | 3103 | `FLOAT_T` | 2 | [Roll, Pitch] (deg) |
| **AccelerometerData** | 3104 | `FLOAT_T` | 3 | [X, Y, Z] (m/s2) |
| **Thermal** | 3105 | `FLOAT_T` | 3 | [FanSpeed, BoardTemperature, OtherTemperature] (rpm, C, C) |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **VESCFault** | 3200 | `UINT8_T` | 2 | [MotorID, FaultCode] |

### Enums

**Motors**
```
0: FRONT_LEFT
1: MIDDLE_LEFT
2: BACK_LEFT
3: FRONT_RIGHT
4: MIDDLE_RIGHT
5: BACK_RIGHT
```
**DisplayState**
```
0: TELEOP
1: AUTONOMY
2: REACHED_GOAL
```
**VESCFaultCode**
```
0: NONE
1: OVER_VOLTAGE
2: UNDER_VOLTAGE
3: DRV
4: ABS_OVER_CURRENT
5: OVER_TEMP_FET
6: OVER_TEMP_MOTOR
7: GATE_DRIVER_OVER_VOLTAGE
8: GATE_DRIVER_UNDER_VOLTAGE
9: MCU_UNDER_VOLTAGE
10: BOOTING_FROM_WATCHDOG_RESET
11: ENCODER_SPI
12: ENCODER_SINCOS_BELOW_MIN_AMPLITUDE
13: ENCODER_SINCOS_ABOVE_MAX_AMPLITUDE
14: FLASH_CORRUPTION
15: HIGH_OFFSET_CURRENT_SENSOR_1
16: HIGH_OFFSET_CURRENT_SENSOR_2
17: HIGH_OFFSET_CURRENT_SENSOR_3
18: UNBALANCED_CURRENTS
19: BRK
20: RESOLVER_LOT
21: RESOLVER_DOS
22: RESOLVER_LOS
23: FLASH_CORRUPTION_APP_CFG
24: FLASH_CORRUPTION_MC_CFG
25: ENCODER_NO_MAGNET
26: ENCODER_MAGNET_TOO_STRONG
27: PHASE_FILTER
```
## PMS Board

**IP**: 192.168.2.102

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **EStop** | 4000 | `UINT8_T` | 0 | Power off all systems except network (PMS will stay on) |
| **Suicide** | 4001 | `UINT8_T` | 0 | Power off all systems including network, cannot recover without physical reboot (PMS will stay on) |
| **Reboot** | 4002 | `UINT8_T` | 0 | Cycle all systems including network off and back on (PMS will stay on) |
| **EnableBus** | 4003 | `UINT8_T` | 1 | [Motor, Core, Aux] (bitmask enable) |
| **DisableBus** | 4004 | `UINT8_T` | 1 | [Motor, Core, Aux] (bitmask disable) |
| **SetBus** | 4005 | `UINT8_T` | 1 | [Motor, Core, Aux] (bitmask enabled) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **CurrentAndVoltage** | 4100 | `FLOAT_T` | 12 | [PackCurrent, AuxCurrent, LowCurrent, NetworkCurrent, RadioM2Current, RadioM9Current, Cell1Voltage, Cell2Voltage, Cell3Voltage, Cell4Voltage, Cell5Voltage, Cell6Voltage] (A, A, A, A, A, A, V, V, V, V, V, V) |
| **BusStatus** | 4101 | `UINT8_T` | 1 | [Motor, Core, Aux, RadioM2, RadioM9, Network] (bitmask enabled) |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **PackOvercurrent** | 4200 | `UINT8_T` | 0 | Higher current draw than the battery can support. Rover will Reboot automatically |
| **CellUndervoltage** | 4201 | `UINT8_T` | 1 | [C1, C2, C3, C4, C5, C6] (bitmask undervolt) Rover will EStop automatically |
| **CellCritical** | 4202 | `UINT8_T` | 1 | [C1, C2, C3, C4, C5, C6] (bitmask critical) Rover will Suicide automatically |
| **AuxOvercurrent** | 4203 | `UINT8_T` | 0 | Aux system current draw too high. Rover will disable Aux bus automatically |

## Nav Board

**IP**: 192.168.2.104

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **GPSLatLonAlt** | 6100 | `DOUBLE_T` | 8 | [Lat, Lon, Alt, HorizontalAccuracy, VerticalAccuracy, HeadingAccuracy, FixType, IsDifferential] (deg, deg, m, m, m, deg, ublox_navpvt fix type http://docs.ros.org/en/noetic/api/ublox_msgs/html/msg/NavPVT.html, bool) |
| **CompassData** | 6102 | `FLOAT_T` | 1 | [Heading] (0 - 360) |
| **SatelliteCountData** | 6103 | `UINT8_T` | 1 | [Satellites] |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **GPSLockError** | 6200 | `UINT8_T` | 0 |  |

## SignalStack Board

**IP**: 192.168.100.101

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **OpenLoop** | 7000 | `INT16_T` | 1 | [Speed] (-1000 - 1000) -> (-100% - 100%) |
| **SetAngleTarget** | 7001 | `FLOAT_T` | 1 | [Heading] (0 - 360) |
| **SetGPSTarget** | 7002 | `DOUBLE_T` | 4 | [Rover Lat, Rover Lon, Basestation Lat, Basestation Lon] (-90 - 90, -180 - 180, -90 - 90, -180 - 180) |
| **WatchdogOverride** | 7003 | `UINT8_T` | 1 | [Enabled] |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **CompassAngle** | 7100 | `FLOAT_T` | 1 | [Heading] (0 - 360) |

## Arm Board

**IP**: 192.168.2.107

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **OpenLoop** | 8000 | `INT16_T` | 6 | [X, J2, J3, J4, J5, J6] (-32768 - 32767) -> (-100% - 100%) |
| **TargetAngle** | 8001 | `FLOAT_T` | 6 | [X, J2, J3, J4, J5, J6] (in, deg, deg, deg, deg, deg) |
| **TargetAngleIncrement** | 8002 | `FLOAT_T` | 6 | [X, J2, J3, J4, J5, J6] (in, deg, deg, deg, deg, deg) |
| **GripperOpenLoop** | 8003 | `INT16_T` | 1 | [Gripper] (-32768 - 32767) -> (-100% - 100%) |
| **IKPosition** | 8004 | `FLOAT_T` | 6 | [X, Y, Z, J4, J5, J6] (in, in, in, deg, deg, deg) |
| **IKPositionIncrement** | 8005 | `FLOAT_T` | 6 | [X, Y, Z, J4, J5, J6] (in, in, in, deg, deg, deg) |
| **IKPoseIncrement** | 8006 | `FLOAT_T` | 6 | [TX, TY, TZ, RX, RY, RZ] (in, in, in, deg, deg, deg) |
| **Laser** | 8007 | `UINT8_T` | 1 | [Enabled] |
| **LinearServo** | 8008 | `UINT8_T` | 1 | [Position] (0 - 180) |
| **Cache** | 8009 | `UINT8_T` | 1 | [Position] (0 - 180) |
| **WatchdogOverride** | 8010 | `UINT8_T` | 1 | [Enabled] |
| **LimitSwitchOverride** | 8011 | `UINT16_T` | 1 | [X+, X-, J2+, J2-, J3+, J3-, J4+, J4-, J5+, J5-] (bitmask override enabled) |
| **ClosedLoopOverride** | 8012 | `UINT8_T` | 1 | [X, J2, J3, J4, J5, J6] (bitmask override enabled) |
| **CalibrateEncoder** | 8013 | `UINT8_T` | 1 | [X, Roll] (bitmask start calibration) |
| **SoftLimitOverride** | 8014 | `UINT16_T` | 1 | [X+, X-, J2+, J2-, J3+, J3-, J4+, J4-, J5+, J5-] (bitmask override enabled) |
| **ArmGimbal1** | 8015 | `INT16_T` | 2 | [Pan, Tilt] (0 - 180) |
| **ArmGimbal2** | 8016 | `INT16_T` | 2 | [Pan, Tilt] (0 - 180) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **Position** | 8100 | `FLOAT_T` | 9 | [X, J2, J3, J4, J5, J6, GX, GY, GZ] (in, deg, deg, deg, deg, deg, in, in, in) |
| **LimitSwitch** | 8101 | `UINT16_T` | 1 | [X+, X-, J2+, J2-, J3+, J3-, J4+, J4-, J5+, J5-] (bitmask depressed) |
| **SoftLimit** | 8102 | `UINT16_T` | 1 | [X+, X-, J2+, J2-, J3+, J3-, J4+, J4-, J5+, J5-] (bitmask triggered) |
| **SMOCOPing** | 8103 | `UINT16_T` | 7 | [X, J2, J3, J4, J5, J6, G] (ping time ms) |

## Auger Board

**IP**: 192.168.2.108

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **AugerAxis** | 9000 | `INT16_T` | 1 | [Speed] (-32768 - 32767) -> (-100% - 100%) |
| **LimitSwitchOverride** | 9001 | `UINT8_T` | 1 | [AugerAxis+, AugerAxis-] (bitmask override enabled) |
| **CalibrateEncoder** | 9002 | `UINT8_T` | 0 | Request calibration of the AugerAxis encoder |
| **Auger** | 9003 | `INT16_T` | 1 | [Speed] (-1000 - 1000) -> (-100% - 100%) |
| **WatchdogOverride** | 9004 | `UINT8_T` | 1 | [Enabled] |
| **LED** | 9005 | `UINT8_T` | 4 | [White, 365, 405, 500] (brightness 0 - 255) |
| **AugerServo** | 9006 | `INT16_T` | 2 | [AFFilters, SoilTrapdoor] (0 - 180) |
| **AugerGimbal** | 9007 | `INT16_T` | 2 | [Pan, Tilt] (0 - 180) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **Position** | 9100 | `FLOAT_T` | 1 | [AugerAxis] (in) |
| **AugerSpeed** | 9101 | `FLOAT_T` | 1 | [AugerSpeed] (rpm) |
| **LimitSwitch** | 9102 | `UINT8_T` | 1 | [AugerAxis+, AugerAxis-] (bitmask depressed) |
| **Environmental** | 9103 | `FLOAT_T` | 2 | [Temperature, Humidity] (C, relative %) |
| **AugerCurrent** | 9104 | `FLOAT_T` | 1 | [AugerCurrent] (A) |
| **SMOCOPing** | 9105 | `UINT16_T` | 1 | [AugerAxis] (ping time ms) |

## Autonomy Board

**IP**: 192.168.3.100

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **StartAutonomy** | 11000 | `UINT8_T` | 1 | Start Autonomy_Software |
| **DisableAutonomy** | 11001 | `UINT8_T` | 1 | Return Autonomy_Software to Idle state |
| **AddPositionLeg** | 11002 | `DOUBLE_T` | 3 | [Lat, Lon, AUTONOMYWAYPOINTTYPES] |
| **AddMarkerLeg** | 11003 | `DOUBLE_T` | 4 | [Lat, Lon, AUTONOMYWAYPOINTTYPES, MarkerRadius (meters)] |
| **AddObjectLeg** | 11004 | `DOUBLE_T` | 4 | [Lat, Lon, AUTONOMYWAYPOINTTYPES, ObjectRadius (meters)] |
| **ClearWaypoints** | 11005 | `UINT8_T` | 1 | Clear queued positions, markers, and objects waypoints. |
| **SetMaxSpeed** | 11006 | `FLOAT_T` | 1 | A multiplier from 0.0 to 1.0 that will scale the max power effort of Autonomy. |
| **SetMinTravScore** | 11007 | `FLOAT_T` | 1 | A multiplier from 0.0 to 1.0 that will filter points from the traversability map. Higher values will result in more conservative pathing. |
| **SetBetaBias** | 11008 | `FLOAT_T` | 1 | A multiplier from 0.0 to 1.0 that will bias the pathing algorithm towards shorter paths (lower values) or safer paths (higher values). |
| **SetLoggingLevels** | 11009 | `UINT8_T` | 3 | [Enum (AUTONOMYLOG), Enum (AUTONOMYLOG), Enum (AUTONOMYLOG)] {Console, File, RoveComm} |
| **AddObstacle** | 11010 | `DOUBLE_T` | 3 | [Lat, Lon, ObstacleRadius (meters)] |
| **ClearObstacles** | 11011 | `UINT8_T` | 1 | Clear queued permanent obstacles. |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **CurrentState** | 11100 | `UINT8_T` | 1 | [State] (AUTONOMYSTATE) |
| **StateDisplay** | 11101 | `UINT8_T` | 1 | [State] (0: Teleop 1: Autonomy 2: Reached Goal) |
| **ThreadFPS** | 11103 | `UINT32_T` | 2 | [Thread, FPS] (AUTONOMYTHREADS, fps) |

### Enums

**AUTONOMYSTATE**
```
0: Idle
1: Navigating
2: SearchPattern
3: ApproachingMarker
4: ApproachingObject
5: VerifyingGPS
6: VerifyingMarker
7: VerifyingObject
8: Reversing
9: Stuck
```
**AUTONOMYLOG**
```
0: TraceL3
1: TraceL2
2: TraceL1
3: Debug
4: Info
5: Notice
6: Warning
7: Error
8: Critical
```
**AUTONOMYTHREADS**
```
0: NotSet
1: MainProcess
2: MainCam
3: RearCam
4: TagDetector
5: ObjectDetector
6: StateMachine
7: RoveCommUDP
8: RoveCommTCP
```
**AUTONOMYWAYPOINTTYPES**
```
-99: ContinuousNavigate
-4: RockPick
-3: WaterBottle
-2: Mallet
-1: Any
0: Tag0
1: Tag1
2: Tag2
3: Tag3
```
## Camera1 Board

**IP**: 192.168.4.100

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **TakePicture** | 12000 | `UINT8_T` | 2 | [Camera, Restart] |
| **ToggleStream** | 12001 | `UINT8_T` | 2 | [Camera, Restart] |
| **SetFFMPEGArguments** | 12002 | `CHAR` | 16384 | [Arguments] (0x1f delimited, 0x04 terminated list with maximum length of 16384 characters for RPi-Camera/config.toml/ffmpeg_arguments. Accepts the following substitutions: $index: camera index, $input: input device file, $ip: output ip, $port: output port, $brightness, $contrast) |
| **SetPictureArguments** | 12003 | `CHAR` | 16384 | [Arguments] (0x1f delimited, 0x04 terminated list with maximum length of 16384 characters for RPi-Camera/config.toml/picture_arguments. Accepts the following substitutions: $index: camera index, $input: input device file, $output: output file without extension, $brightness, $contrast) |
| **SetBrightness** | 12004 | `FLOAT_T` | 4 | [Camera0, Camera1, Camera2, Camera3] (-1.0 - 1.0) |
| **SetContrast** | 12005 | `FLOAT_T` | 4 | [Camera0, Camera1, Camera2, Camera3] (-1.0 - 2.0) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **AvailableCameras** | 12100 | `UINT8_T` | 1 | [AvailableCameras] |
| **StreamingCameras** | 12101 | `UINT8_T` | 1 | [StreamingCameras] |
| **PictureTaken** | 12102 | `UINT8_T` | 0 | Picture has been taken. |
| **Utilization** | 12103 | `UINT8_T` | 6 | [cpu0, cpu1, cpu2, cpu3, mem, storage] (% usage) |

## Camera2 Board

**IP**: 192.168.4.101

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **TakePicture** | 13000 | `UINT8_T` | 2 | [Camera, Restart] |
| **ToggleStream** | 13001 | `UINT8_T` | 2 | [Camera, Restart] |
| **SetFFMPEGArguments** | 13002 | `CHAR` | 16384 | [Arguments] (0x1f delimited, 0x04 terminated list with maximum length of 16384 characters for RPi-Camera/config.toml/ffmpeg_arguments. Accepts the following substitutions: $index: camera index, $input: input device file, $ip: output ip, $port: output port, $brightness, $contrast) |
| **SetPictureArguments** | 13003 | `CHAR` | 16384 | [Arguments] (0x1f delimited, 0x04 terminated list with maximum length of 16384 characters for RPi-Camera/config.toml/picture_arguments. Accepts the following substitutions: $index: camera index, $input: input device file, $output: output file without extension, $brightness, $contrast) |
| **SetBrightness** | 13004 | `FLOAT_T` | 4 | [Camera0, Camera1, Camera2, Camera3] (-1.0 - 1.0) |
| **SetContrast** | 13005 | `FLOAT_T` | 4 | [Camera0, Camera1, Camera2, Camera3] (-1.0 - 2.0) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **AvailableCameras** | 13100 | `UINT8_T` | 1 | [AvailableCameras] |
| **StreamingCameras** | 13101 | `UINT8_T` | 1 | [StreamingCameras] |
| **PictureTaken** | 13102 | `UINT8_T` | 0 | Picture has been taken. |
| **Utilization** | 13103 | `UINT8_T` | 6 | [cpu0, cpu1, cpu2, cpu3, mem, storage] (% usage) |

## CameraServer Board

**IP**: 192.168.4.102

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **TakePhoto** | 14000 | `UINT8_T` | 1 | [Camera] |
| **ToggleStream** | 14001 | `UINT8_T` | 2 | [Camera, Action] (id, 0: Shutdown 1: Startup 2: Restart) |
| **AdjustBrightness** | 14002 | `UINT8_T` | 2 | [Camera, Brightness] (id, 0 - 255) |
| **AdjustContrast** | 14003 | `UINT8_T` | 2 | [Camera, Contrast] (id, 0 - 255) |
| **AdjustSaturation** | 14004 | `UINT8_T` | 2 | [Camera, Saturation] (id, 0 - 255) |
| **AdjustHue** | 14005 | `UINT8_T` | 2 | [Camera, Hue] (id, 0 - 255) |
| **SetWhiteBalance** | 14008 | `UINT8_T` | 2 | [Camera, Temperature] |
| **AdjustBacklightContrast** | 14009 | `UINT8_T` | 2 | [Camera, BacklightContrast] |
| **SetExposure** | 14010 | `INT32_T` | 2 | [Camera, Exposure] |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **AvailableCameras** | 14100 | `UINT8_T` | 1 | [Camera0, Camera1, Camera2, Camera3, Camera4, Camera5, Camera6, Camera7] (bitmask able to stream) |
| **StreamingCameras** | 14101 | `UINT8_T` | 4 | [Port0, Port1, Port2, Port3] (currently streaming on each port) |
| **PictureTaken** | 14102 | `UINT8_T` | 0 | Picture has been taken |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **CameraUnavailable** | 14200 | `UINT8_T` | 1 | [Camera] (id) Camera has errored and stopped streaming |

## Raman Board

**IP**: 192.168.3.105

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **InstrumentsAxis** | 16000 | `INT16_T` | 1 | [Speed] (-32768 - 32767) -> (-100% - 100%) |
| **LimitSwitchOverride** | 16001 | `UINT8_T` | 1 | [InstrumentsAxis+, InstrumentsAxis-] (bitmask override enabled) |
| **CalibrateEncoder** | 16002 | `UINT8_T` | 0 | Request calibration of the InstrumentsAxis encoder |
| **WatchdogOverride** | 16003 | `UINT8_T` | 1 | [Enabled] |
| **Laser** | 16004 | `UINT8_T` | 1 | [Enabled] |
| **RequestRamanReading** | 16005 | `UINT32_T` | 1 | [Integration Time] (ms) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **Position** | 16100 | `FLOAT_T` | 2 | [InstrumentsAxis, TOF] (mm, mm) |
| **LimitSwitch** | 16101 | `UINT8_T` | 1 | [InstrumentsAxis+, InstrumentsAxis-] (bitmask depressed) |
| **RamanReading_Part1** | 16102 | `UINT16_T` | 512 | Raman CCD elements 1-512 |
| **RamanReading_Part2** | 16103 | `UINT16_T` | 512 | Raman CCD elements 513-1024 |
| **RamanReading_Part3** | 16104 | `UINT16_T` | 512 | Raman CCD elements 1025-1536 |
| **RamanReading_Part4** | 16105 | `UINT16_T` | 512 | Raman CCD elements 1537-2048 |
| **SMOCOPing** | 16106 | `UINT16_T` | 1 | [InstrumentsAxis] (ping time ms) |

## RoveSoSimulator Board

**IP**: 127.0.0.1

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **IMU** | 99100 | `DOUBLE_T` | 10 | [Accel X, Accel Y, Accel Z, Gyro X, Gyro Y, Gyro Z, Quat X, Quat Y, Quat Z, Quat W] |

# Network Devices

| name | ip  |
| :--- | --- |
| **BasestationSwitch** | `192.168.254.2` |
| **RoverSwitch** | `192.168.254.1` |
| **Rover900MHzRocket** | `10.0.0.3` |
| **Basestation900MHzRocket** | `10.0.0.4` |
| **Rover5GHzRocket** | `10.0.0.19` |
| **Basestation5GHzRocket** | `10.0.0.20` |
| **Rover2_4GHzRocket** | `10.0.0.11` |
| **Basestation2_4GHzRocket** | `10.0.0.12` |
# Multicast Devices

| name | ip  | port | device |
| :--- | --- | ---- | ------ |
| **DriveCamLeft** | `239.0.0.1` | `50000` | `0` |
| **DriveCamRight** | `239.0.0.2` | `50000` | `1` |
| **GimbalCamLeft** | `239.0.0.3` | `50000` | `2` |
| **GimbalCamRight** | `239.0.0.4` | `50000` | `3` |
| **BackCam** | `239.0.0.5` | `50000` | `4` |
| **AuxCam1** | `239.0.0.6` | `50000` | `5` |
| **AuxCam2** | `239.0.0.7` | `50000` | `6` |
| **AuxCam3** | `239.0.0.8` | `50000` | `7` |
| **AuxCam4** | `239.0.0.9` | `50000` | `8` |
| **Microscope** | `239.0.0.10` | `50000` | `9` |
