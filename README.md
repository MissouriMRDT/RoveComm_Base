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
| **DriveLeftRight** | 3000 | `FLOAT_T` | 2 | [LeftSpeed, RightSpeed] (-1, 1)-> (-100%, 100%) |
| **DriveIndividual** | 3001 | `FLOAT_T` | 6 | [LF, LM, LR, RF, RM, RR] (-1, 1)-> (-100%, 100%) |
| **WatchdogOverride** | 3002 | `UINT8_T` | 1 | [0-override off, 1-override on] |
| **LeftDriveGimbalIncrement** | 3003 | `INT16_T` | 1 | [Tilt](degrees -180-180) |
| **RightDriveGimbalIncrement** | 3004 | `INT16_T` | 1 | [Tilt](degrees -180-180) |
| **LeftMainGimbalIncrement** | 3005 | `INT16_T` | 2 | [Pan, Tilt](degrees -180-180) |
| **RightMainGimbalIncrement** | 3006 | `INT16_T` | 2 | [Pan, Tilt](degrees -180-180) |
| **BackDriveGimbalIncrement** | 3007 | `INT16_T` | 1 | [Tilt](degrees -180-180) |
| **LEDRGB** | 3008 | `UINT8_T` | 3 | [R, G, B] (0, 255) |
| **LEDPatterns** | 3009 | `UINT8_T` | 1 | [Pattern] (Enum) |
| **StateDisplay** | 3010 | `UINT8_T` | 1 | [Teleop, Autonomy, Reached Goal] (enum) |
| **Brightness** | 3011 | `UINT8_T` | 1 | Set Brightness (0-255) |
| **SetWatchdogMode** | 3012 | `UINT8_T` | 1 | 0: Teleop, 1: Autonomy |
| **LEDText** | 3013 | `CHAR` | 256 | Set the message to display on the lighting panel; null terminator ends string early |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **MotorSpeeds** | 3100 | `FLOAT_T` | 6 | [FL, ML, BL, FR, MR, BR] (-1, 1)-> (-100%, 100%) |
| **MotorCurrents** | 3101 | `FLOAT_T` | 6 | [FL, ML, BL, FR, MR, BR] Motor current draw |
| **VESCCurrents** | 3102 | `FLOAT_T` | 6 | [FL, ML, BL, FR, MR, BR] VESC (battery side) current draw |
| **IMUData** | 3103 | `FLOAT_T` | 3 | [Roll, Pitch, Yaw] degrees |
| **AccelerometerData** | 3104 | `FLOAT_T` | 3 | [xAxis, yAxis, zAxis] Accel in m/s^2 |

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
**Patterns**
```
0: MRDT
1: BELGIUM
2: MERICA
3: DIRT
4: DOTA
5: MCD
6: WINDOWS
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
| **EStop** | 4000 | `UINT8_T` | 1 | Power off all systems except network (PMS will stay on) |
| **Suicide** | 4001 | `UINT8_T` | 1 | Power off all systems including network, cannot recover without physical reboot (PMS will stay on) |
| **Reboot** | 4002 | `UINT8_T` | 1 | Cycle all systems including network off and back on (PMS will stay on) |
| **EnableBus** | 4003 | `UINT8_T` | 1 | [Motor, Core, Aux] (bitmasked) [1-Enable, 0-No change] |
| **DisableBus** | 4004 | `UINT8_T` | 1 | [Motor, Core, Aux] (bitmasked) [1-Disable, 0-No change] |
| **SetBus** | 4005 | `UINT8_T` | 1 | [Motor, Core, Aux] (bitmasked) [1-Enable, 0-Disable] |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **PackCurrent** | 4100 | `FLOAT_T` | 1 | Total current draw from battery |
| **PackVoltage** | 4101 | `FLOAT_T` | 1 | Pack voltage |
| **CellVoltage** | 4102 | `FLOAT_T` | 6 | C1, C2, C3, C4, C5, C6 |
| **AuxCurrent** | 4103 | `FLOAT_T` | 1 | Current draw by aux systems (before 12V buck) |
| **MiscCurrent** | 4104 | `FLOAT_T` | 3 | Current draw from other devices (CS1, CS2, CS3) |
| **BusStatus** | 4105 | `UINT8_T` | 1 | [Motor, Core, Aux, Network] (bitmasked) [1-Enabled, 0-Disabled] |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **PackOvercurrent** | 4200 | `UINT8_T` | 1 | Higher current draw than the battery can support. Rover will Reboot automatically |
| **CellUndervoltage** | 4201 | `UINT8_T` | 1 | (bitmasked) [1-Undervolt, 0-OK]. Rover will EStop automatically |
| **CellCritical** | 4202 | `UINT8_T` | 1 | (bitmasked) [1-Critical, 0-OK]. Rover will Suicide automatically |
| **AuxOvercurrent** | 4203 | `UINT8_T` | 1 | Aux system current draw too high. Rover will disable Aux bus automatically |

## Nav Board

**IP**: 192.168.2.104

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **GPSLatLonAlt** | 6100 | `DOUBLE_T` | 3 | [Lat, Long, Alt] [(-90, 90), (-180, 180)(deg), (0, 1000)] |
| **IMUData** | 6101 | `FLOAT_T` | 3 | [Pitch, Yaw, Roll] [(-90, 90), (0, 360), (-90, 90)] (deg) |
| **CompassData** | 6102 | `FLOAT_T` | 1 | [Heading] [ 0, 360 ] |
| **SatelliteCountData** | 6103 | `UINT8_T` | 1 | [Number of satellites] |
| **AccelerometerData** | 6104 | `FLOAT_T` | 3 | [xAxis, yAxis, zAxis] Accel in m/s^2 |
| **AccuracyData** | 6105 | `FLOAT_T` | 5 | [horizontal_accur, vertical_accur, heading_accur, fix_type, is_differentia] [meters, meters, degrees, ublox_navpvt fix type (http://docs.ros.org/en/noetic/api/ublox_msgs/html/msg/NavPVT.html), boolean] |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **GPSLockError** | 6200 | `UINT8_T` | 1 |  |

## BaseStationNav Board

**IP**: 192.168.100.112

## SignalStack Board

**IP**: 192.168.100.101

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **OpenLoop** | 7000 | `INT16_T` | 1 | Motor decipercent [-1000, 1000] |
| **SetAngleTarget** | 7001 | `FLOAT_T` | 1 | [Heading] [0, 360) |
| **SetGPSTarget** | 7002 | `DOUBLE_T` | 4 | [Rover Lat, Rover Long, Basestation Lat, Basestation Long] [Lat:(-90, 90), Long:(-180, 180)] (deg) |
| **WatchdogOverride** | 7003 | `UINT8_T` | 1 | [0-override off, 1-override on] |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **CompassAngle** | 7100 | `FLOAT_T` | 1 | [Heading] [0, 360) |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **WatchdogStatus** | 7200 | `UINT8_T` | 1 | (1-Watchdog timeout, 0-OK) |

## Arm Board

**IP**: 192.168.2.107

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **SetIndividualSpeeds** | 8000 | `INT16_T` | 6 | [X, J2, J3, J4, P, R] Motor decipercent [-1000, 1000] |
| **SetJointSpeed** | 8001 | `INT16_T` | 2 | [JointID, Decipercent] Motor decipercent [-1000, 1000] |
| **SetIndividualTargetAngles** | 8002 | `FLOAT_T` | 6 | [X, J2, J3, J4, P, R] (in, deg, deg, deg, deg, deg) |
| **SetJointTargetAngle** | 8003 | `FLOAT_T` | 2 | [JointID, Position] (in for id 0, deg otherwise) |
| **IncrementIndividualTargetAngles** | 8004 | `FLOAT_T` | 6 | [X, J2, J3, J4, P, R] (in, deg, deg, deg, deg, deg) |
| **IncrementJointTargetAngle** | 8005 | `FLOAT_T` | 2 | [JointID, Angle] (in for id 0, deg otherwise) |
| **SetIKPosition** | 8006 | `FLOAT_T` | 6 | [X, Y, Z, J4, P, R] (in, in, in, deg, deg, deg) |
| **IncrementIKPosition** | 8007 | `FLOAT_T` | 6 | [X, Y, Z, J4, P, R] (in, in, in, deg, deg, deg) |
| **SetLockModePosition** | 8008 | `FLOAT_T` | 3 | [J4, P, R] (deg, deg, deg) |
| **IncrementLockModePosition** | 8009 | `FLOAT_T` | 3 | [J4, P, R] (deg, deg, deg) |
| **Laser** | 8010 | `UINT8_T` | 1 | [0-disable, 1-enable] |
| **Solenoid** | 8011 | `UINT8_T` | 1 | [0-retract, 1-extend] |
| **SetGripperSpeed** | 8012 | `INT16_T` | 2 | [Motor decipercent (-1000, 1000), Gripper number (0, 1)] |
| **WatchdogOverride** | 8013 | `UINT8_T` | 1 | [0-override off, 1-override on] (bitmasked) |
| **LimitSwitchOverride** | 8014 | `UINT16_T` | 1 | [X+, X-, J2+, J2-, J3+, J3-, J4+, J4-, P] (0-override off, 1-override on) (bitmasked) |
| **ClosedLoopOverride** | 8015 | `UINT8_T` | 1 | [X, J2, J3, J4, P, R] (0-override off, 1-override on) (bitmasked) |
| **CalibrateEncoder** | 8016 | `UINT8_T` | 1 | [X, Roll] (1-calibrate, 0-no action) (bitmasked) |
| **SoftLimitOverride** | 8017 | `UINT16_T` | 1 | [X+, X-, J2+, J2-, J3+, J3-, J4+, J4-, P+, P-] (0-override off, 1-override on) (bitmasked) |
| **EStop** | 8018 | `UINT8_T` | 1 | Shut off all motors (set decipercents to 0 and disable closed loop) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **Positions** | 8100 | `FLOAT_T` | 7 | [X, J2, J3, J4, P, R, AP] (in, deg, deg, deg, deg, deg, deg, deg) |
| **Coordinates** | 8101 | `FLOAT_T` | 6 | [X, Y, Z, J4, P, R] (in, in, in, deg, deg, deg) |
| **LimitSwitchTriggered** | 8102 | `UINT16_T` | 1 | [X+, X-, J2+, J2-, J3+, J3-, J4+, J4-, P] (0-off, 1-on) (bitmasked) |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **WatchdogStatus** | 8200 | `UINT8_T` | 1 | (1-Watchdog timeout, 0-OK) |

### Enums

**Joints**
```
0: X
1: J2
2: J3
3: J4
4: PITCH
5: ROLL
```
## Auger Board

**IP**: 192.168.2.108

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **AugerAxis_OpenLoop** | 9000 | `INT16_T` | 1 | Motor decipercent [-1000, 1000] |
| **AugerAxis_SetPosition** | 9001 | `FLOAT_T` | 1 | Absolute position (in) |
| **AugerAxis_IncrementPosition** | 9002 | `FLOAT_T` | 1 | (in) |
| **LimitSwitchOverride** | 9003 | `UINT8_T` | 1 | [AugerAxis+, AugerAxis-] (0-override off, 1-override on) (bitmasked) |
| **CalibrateEncoder** | 9004 | `UINT8_T` | 1 | Request calibration of the AugerAxis encoder |
| **Auger** | 9005 | `INT16_T` | 1 | Motor decipercent [-1000, 1000] |
| **WatchdogOverride** | 9006 | `UINT8_T` | 1 | [0-override off, 1-override on] |
| **RequestTemperature** | 9007 | `UINT8_T` | 1 | Request a reading of the temperature at the end of the auger |
| **RequestHumidity** | 9008 | `UINT8_T` | 1 | Request a reading of the humidity at the end of the auger |
| **UVLED** | 9009 | `UINT8_T` | 1 | Ultraviolet LED on AutoFluorescence (0-off, 1-on) |
| **AugerMultiplexerServo** | 9010 | `INT16_T` | 1 | [Position](degrees -180-180) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **Position** | 9100 | `FLOAT_T` | 1 | [AugerAxis] (in) |
| **AugerSpeed** | 9101 | `FLOAT_T` | 1 | (in/s) |
| **LimitSwitchTriggered** | 9102 | `UINT8_T` | 1 | [AugerAxis+, AugerAxis-] (0-off, 1-on) (bitmasked) |
| **Temperature** | 9103 | `FLOAT_T` | 1 | [Temperature] (degrees C) |
| **Humidity** | 9104 | `FLOAT_T` | 1 | [Humidity] (relative humidity %) |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **WatchdogStatus** | 9200 | `UINT8_T` | 1 | (1-Watchdog timeout, 0-OK) |
| **AugerStalled** | 9201 | `UINT8_T` | 1 | (1-Stalled, 0-OK) |

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
| **SetLoggingLevels** | 11007 | `UINT8_T` | 3 | [Enum (AUTONOMYLOG), Enum (AUTONOMYLOG), Enum (AUTONOMYLOG)] {Console, File, RoveComm} |
| **AddObstacle** | 11008 | `DOUBLE_T` | 3 | [Lat, Lon, ObstacleRadius (meters)] |
| **ClearObstacles** | 11009 | `UINT8_T` | 1 | Clear queued permanent obstacles. |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **CurrentState** | 11100 | `UINT8_T` | 1 | Enum (AUTONOMYSTATE) |
| **ReachedGoal** | 11101 | `UINT8_T` | 1 |  |
| **CurrentLog** | 11102 | `CHAR` | 255 | String version of most current error log |
| **ThreadFPS** | 11103 | `UINT32_T` | 2 | [Thread Enum ID, FPS Value] |

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
8: Avoidance
9: Reversing
10: Stuck
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
3: GroundCam
4: TagDetector
5: ObjectDetector
6: StateMachine
7: RoveCommUDP
8: RoveCommTCP
```
**AUTONOMYWAYPOINTTYPES**
```
-99: ContinuousNavigate
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
| **TakePicture** | 12000 | `UINT8_T` | 2 | Take a picture with the current camera. [0] is the camera to take a picture with. [1] tells the camera whether to restart the stream afterwards. |
| **ToggleStream** | 12001 | `UINT8_T` | 2 | Stop the current camera stream. [0] is the camera to stop streaming. [1] is whether to restart the stream. |
| **SetFFMPEGArguments** | 12002 | `CHAR` | 16384 | 0x1f delimited, 0x04 terminated list with maximum length of 16384 characters for RPi-Camera/config.toml/ffmpeg_arguments. Accepts the following substitutions: $index: camera index, $input: input device file, $ip: output ip, $port: output port, $brightness, $contrast. |
| **SetPictureArguments** | 12003 | `CHAR` | 16384 | 0x1f delimited, 0x04 terminated list with maximum length of 16384 characters for RPi-Camera/config.toml/picture_arguments. Accepts the following substitutions: $index: camera index, $input: input device file, $output: output file without extension, $brightness, $contrast. |
| **SetBrightness** | 12004 | `FLOAT_T` | 4 | Brightness for each camera (-1.0, 1.0) |
| **SetContrast** | 12005 | `FLOAT_T` | 4 | Contrast for each camera (0, 2) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **AvailableCameras** | 12100 | `UINT8_T` | 1 | Number of detected cameras. |
| **StreamingCameras** | 12101 | `UINT8_T` | 1 | Number of streaming cameras. |
| **PictureTaken** | 12102 | `UINT8_T` | 1 | Picture has been taken. |
| **Utilization** | 12103 | `UINT8_T` | 6 | [cpu0, cpu1, cpu2, cpu3, mem, storage], (% usage) |

## Camera2 Board

**IP**: 192.168.4.101

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **TakePicture** | 13000 | `UINT8_T` | 2 | Take a picture with the current camera. [0] is the camera to take a picture with. [1] tells the camera whether to restart the stream afterwards. |
| **ToggleStream** | 13001 | `UINT8_T` | 2 | Stop the current camera stream. [0] is the camera to stop streaming. [1] is whether to restart the stream. |
| **SetFFMPEGArguments** | 13002 | `CHAR` | 16384 | 0x1f delimited, 0x04 terminated list with maximum length of 16384 characters for RPi-Camera/config.toml/ffmpeg_arguments. Accepts the following substitutions: $index: camera index, $input: input device file, $ip: output ip, $port: output port, $brightness, $contrast. |
| **SetPictureArguments** | 13003 | `CHAR` | 16384 | 0x1f delimited, 0x04 terminated list with maximum length of 16384 characters for RPi-Camera/config.toml/picture_arguments. Accepts the following substitutions: $index: camera index, $input: input device file, $output: output file without extension, $brightness, $contrast. |
| **SetBrightness** | 13004 | `FLOAT_T` | 4 | Brightness for each camera (-1.0, 1.0) |
| **SetContrast** | 13005 | `FLOAT_T` | 4 | Contrast for each camera (0, 2) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **AvailableCameras** | 13100 | `UINT8_T` | 1 | Number of detected cameras. |
| **StreamingCameras** | 13101 | `UINT8_T` | 1 | Number of streaming cameras. |
| **PictureTaken** | 13102 | `UINT8_T` | 1 | Picture has been taken. |
| **Utilization** | 13103 | `UINT8_T` | 6 | [cpu0, cpu1, cpu2, cpu3, mem, storage], (% usage) |

## CameraServer Board

**IP**: 192.168.4.102

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **TakePhoto** | 14000 | `UINT8_T` | 1 | Take a picture with the current camera. [0] is the camera to take a picture with. |
| **ToggleStream** | 14001 | `UINT8_T` | 2 | Stop the current camera stream. [0] is the camera to stop streaming. [1] is the action (0 = Shutdown, 1 = Startup, 2 = Restart). |
| **AdjustBrightness** | 14002 | `UINT8_T` | 2 | Adjust brightness level (0-255). [0] is the camera ID, [1] is the brightness level. |
| **AdjustContrast** | 14003 | `UINT8_T` | 2 | Adjust contrast level (0-255). [0] is the camera ID, [1] is the contrast level. |
| **AdjustSaturation** | 14004 | `UINT8_T` | 2 | Adjust saturation level (0-255). [0] is the camera ID, [1] is the saturation level. |
| **AdjustHue** | 14005 | `UINT8_T` | 2 | Adjust hue level (0-255). [0] is the camera ID, [1] is the hue level. |
| **SetWhiteBalance** | 14008 | `UINT8_T` | 2 | Set white balance temperature. [0] is the camera ID, [1] is the white balance level. |
| **AdjustBacklightContrast** | 14009 | `UINT8_T` | 2 | Adjust backlight contrast level (0-255). [0] is the camera ID, [1] is the backlight contrast level. |
| **SetExposure** | 14010 | `INT32_T` | 2 | Set exposure level. [0] is the camera ID, [1] is the exposure level. |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **AvailableCameras** | 14100 | `UINT8_T` | 1 | Bitmask values for which cameras are able to stream. LSB is Camera 0, MSB is Camera 7. |
| **StreamingCameras** | 14101 | `UINT8_T` | 4 | Which cameras the system is currently streaming on each port |
| **PictureTaken1** | 14102 | `UINT8_T` | 1 | Picture has been taken. |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **CameraUnavailable** | 14200 | `UINT8_T` | 1 | Camera has errored and stopped streaming. [0] is ID of camera as an integer (not bitmask). |

## IRSpectrometer Board

**IP**: 192.168.3.104

## Raman Board

**IP**: 192.168.3.105

### Commands

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **InstrumentsAxis_OpenLoop** | 16000 | `INT16_T` | 1 | Motor decipercent [-1000, 1000] |
| **InstrumentsAxis_SetPosition** | 16001 | `FLOAT_T` | 1 | Absolute position (in) |
| **InstrumentsAxis_IncrementPosition** | 16002 | `FLOAT_T` | 1 | (in) |
| **LimitSwitchOverride** | 16003 | `UINT8_T` | 1 | [InstrumentsAxis+, InstrumentsAxis-] (0-override off, 1-override on) (bitmasked) |
| **CalibrateEncoder** | 16004 | `UINT8_T` | 1 | Request calibration of the InstrumentsAxis encoder |
| **WatchdogOverride** | 16005 | `UINT8_T` | 1 | [0-override off, 1-override on] |
| **Laser** | 16006 | `UINT8_T` | 1 | [0-disable, 1-enable] |
| **RequestRamanReading** | 16007 | `UINT32_T` | 1 | Start a Raman reading, with the provided integration time (milliseconds) |
| **RamanGimbalIncrement** | 16008 | `INT16_T` | 2 | [Pan, Tilt](degrees -180-180) |

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **Position** | 16100 | `FLOAT_T` | 1 | [InstrumentsAxis] (in) |
| **LimitSwitchTriggered** | 16101 | `UINT8_T` | 1 | [InstrumentsAxis+, InstrumentsAxis-] (0-off, 1-on) (bitmasked) |
| **RamanReading_Part1** | 16102 | `UINT16_T` | 512 | Raman CCD elements 1-512 |
| **RamanReading_Part2** | 16103 | `UINT16_T` | 512 | Raman CCD elements 513-1024 |
| **RamanReading_Part3** | 16104 | `UINT16_T` | 512 | Raman CCD elements 1025-1536 |
| **RamanReading_Part4** | 16105 | `UINT16_T` | 512 | Raman CCD elements 1537-2048 |

### Errors

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **WatchdogStatus** | 16200 | `UINT8_T` | 1 | (1-Watchdog timeout, 0-OK) |

## RoveSoSimulator Board

**IP**: 127.0.0.1

### Telemetry

| name | dataId | type | count | description |
| :--- | ------ | ---- | ----- | ----------- |
| **Ultrasonic1** | 99100 | `FLOAT_T` | 2 | Ultrasonic sensor distance reading in centimeters (cm). Value ranges from 0.00 to 500.00 cm |

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
