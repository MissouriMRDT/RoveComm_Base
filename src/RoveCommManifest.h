#ifndef RoveCommManifest_h
#define RoveCommManifest_h

#include <stdint.h>
#include"RoveCommPacket.h"

#define RC_DRIVE_FOURTHOCTET                      134       
#define RC_ROVECOMM_DRIVE_PORT                    11004     

#define RC_BMS_FOURTHOCTET                        133       
#define RC_ROVECOMM_BMS_PORT                      11003     

#define RC_POWER_FOURTHOCTET                      132       
#define RC_ROVECOMM_POWER_PORT                    11002     

#define RC_NAV_FOURTHOCTET                        136       
#define RC_ROVECOMM_NAV_PORT                      11006     

#define RC_GIMBAL_FOURTHOCTET                     135       
#define RC_ROVECOMM_GIMBAL_PORT                   11005     

#define RC_MULTIMEDIA_FOURTHOCTET                 140       
#define RC_ROVECOMM_MULTIMEDIA_PORT               11010     

#define RC_ARM_FOURTHOCTET                        131       
#define RC_ROVECOMM_ARM_PORT                      11001     

#define RC_SCIENCEACTUATION_FOURTHOCTET           137       
#define RC_ROVECOMM_SCIENCEACTUATION_PORT         11007     

#define RC_SCIENCESENSORS_FOURTHOCTET             138       
#define RC_ROVECOMM_SCIENCESENSORS_PORT           11008     

#define RC_AUTONOMY_FOURTHOCTET                   139       
#define RC_ROVECOMM_AUTONOMY_PORT                 11009     

#define RC_CAMERA1_FOURTHOCTET                    141       
#define RC_ROVECOMM_CAMERA1_PORT                  11011     

#define RC_CAMERA2_FOURTHOCTET                    142       
#define RC_ROVECOMM_CAMERA2_PORT                  11012     



///////////////////////////////////////////////////
////////////        System Packets      ///////////         
///////////////////////////////////////////////////

#define RC_ROVECOMM_PING_DATA_ID                  1         
#define RC_ROVECOMM_PING_REPLY_DATA_ID            2         
#define RC_ROVECOMM_SUBSCRIBE_DATA_ID             3         
#define RC_ROVECOMM_UNSUBSCRIBE_DATA_ID           4         
#define RC_ROVECOMM_INVALID_VERSION_DATA_ID       5         
#define RC_ROVECOMM_NO_DATA_DATA_ID               6         


///////////////////////////////////////////////////
////////////        DRIVE               ///////////         
///////////////////////////////////////////////////

////////////////////Commands
//[LeftSpeed, RightSpeed] (-1000, 1000)-> (-100%, 100%)
#define RC_DRIVE_DRIVELEFTRIGHT_DATA_ID                               1000      
#define RC_DRIVE_DRIVELEFTRIGHT_DATA_COUNT                            2         
#define RC_DRIVE_DRIVELEFTRIGHT_DATA_TYPE                             int16_t   

//[LF, LR, RF, RR] (-1000, 1000)-> (-100%, 100%)
#define RC_DRIVE_DRIVEINDIVIDUAL_DATA_ID                              1001      
#define RC_DRIVE_DRIVEINDIVIDUAL_DATA_COUNT                           4         
#define RC_DRIVE_DRIVEINDIVIDUAL_DATA_TYPE                            int16_t   

//[LF, LR, RF, RR] (0, 359)
#define RC_DRIVE_SETSTEERINGANGLE_DATA_ID                             1002      
#define RC_DRIVE_SETSTEERINGANGLE_DATA_COUNT                          4         
#define RC_DRIVE_SETSTEERINGANGLE_DATA_TYPE                           int16_t   

//[PointTurnSpeed] (-1000,1000) (Full speed CCW, full speed CW)
#define RC_DRIVE_POINTTURN_DATA_ID                                    1003      
#define RC_DRIVE_POINTTURN_DATA_COUNT                                 1         
#define RC_DRIVE_POINTTURN_DATA_TYPE                                  int16_t   

//[0-Turn off Watchdog Override, 1-Turn on Watchdog Override]
#define RC_DRIVE_WATCHDOGOVERRIDE_DATA_ID                             1004      
#define RC_DRIVE_WATCHDOGOVERRIDE_DATA_COUNT                          1         
#define RC_DRIVE_WATCHDOGOVERRIDE_DATA_TYPE                           uint8_t   

////////////////////Telemetry
//[LF, LR, RF, RR] (-1000, 1000)-> (-100%, 100%)
#define RC_DRIVE_DRIVESPEEDS_DATA_ID                                  1100      
#define RC_DRIVE_DRIVESPEEDS_DATA_COUNT                               4         
#define RC_DRIVE_DRIVESPEEDS_DATA_TYPE                                int16_t   

//[LF, LR, RF, RR] -> (0, 360)
#define RC_DRIVE_DRIVEANGLES_DATA_ID                                  1101      
#define RC_DRIVE_DRIVEANGLES_DATA_COUNT                               4         
#define RC_DRIVE_DRIVEANGLES_DATA_TYPE                                int16_t   

//[M1, M2, M3, M4] (A)
#define RC_DRIVE_STEERINGMOTORCURRENTS_DATA_ID                        1102      
#define RC_DRIVE_STEERINGMOTORCURRENTS_DATA_COUNT                     4         
#define RC_DRIVE_STEERINGMOTORCURRENTS_DATA_TYPE                      float     

////////////////////Error
//[(0-undermaxcurrent, 1-overcurrent)] [LF, LR, RF, RL (Bitmask)]
#define RC_DRIVE_STEERINGMOTOROVERCURRENT_DATA_ID                     1200      
#define RC_DRIVE_STEERINGMOTOROVERCURRENT_DATA_COUNT                  1         
#define RC_DRIVE_STEERINGMOTOROVERCURRENT_DATA_TYPE                   uint8_t   



///////////////////////////////////////////////////
////////////        BMS                 ///////////         
///////////////////////////////////////////////////

////////////////////Commands
//[delay] (s) -> a delay of 0 will shutdown, not restart and cannot be reversed
#define RC_BMS_BMSSTOP_DATA_ID                                        2000      
#define RC_BMS_BMSSTOP_DATA_COUNT                                     1         
#define RC_BMS_BMSSTOP_DATA_TYPE                                      uint8_t   

////////////////////Telemetry
//[Main] (A)
#define RC_BMS_PACKI_MEAS_DATA_ID                                     2100      
#define RC_BMS_PACKI_MEAS_DATA_COUNT                                  1         
#define RC_BMS_PACKI_MEAS_DATA_TYPE                                   float     

//[Pack_Out] (V)
#define RC_BMS_PACKV_MEAS_DATA_ID                                     2101      
#define RC_BMS_PACKV_MEAS_DATA_COUNT                                  1         
#define RC_BMS_PACKV_MEAS_DATA_TYPE                                   float     

//[C1-G, C2-1, C3-2, C4-3, C5-4, C6-5, C7-6, C8-7] (V)
#define RC_BMS_CELLV_MEAS_DATA_ID                                     2102      
#define RC_BMS_CELLV_MEAS_DATA_COUNT                                  8         
#define RC_BMS_CELLV_MEAS_DATA_TYPE                                   float     

//[Temp] (degC)
#define RC_BMS_TEMP_MEAS_DATA_ID                                      2103      
#define RC_BMS_TEMP_MEAS_DATA_COUNT                                   1         
#define RC_BMS_TEMP_MEAS_DATA_TYPE                                    float     

////////////////////Error
//
#define RC_BMS_PACKOVERCURRENT_DATA_ID                                2200      
#define RC_BMS_PACKOVERCURRENT_DATA_COUNT                             1         
#define RC_BMS_PACKOVERCURRENT_DATA_TYPE                              uint8_t   

//(bitmasked)
#define RC_BMS_CELLUNDERVOLTAGE_DATA_ID                               2201      
#define RC_BMS_CELLUNDERVOLTAGE_DATA_COUNT                            1         
#define RC_BMS_CELLUNDERVOLTAGE_DATA_TYPE                             uint8_t   

//
#define RC_BMS_PACKUNDERVOLTAGE_DATA_ID                               2202      
#define RC_BMS_PACKUNDERVOLTAGE_DATA_COUNT                            1         
#define RC_BMS_PACKUNDERVOLTAGE_DATA_TYPE                             uint8_t   

//
#define RC_BMS_PACKSUPERHOT_DATA_ID                                   2203      
#define RC_BMS_PACKSUPERHOT_DATA_COUNT                                1         
#define RC_BMS_PACKSUPERHOT_DATA_TYPE                                 uint8_t   



///////////////////////////////////////////////////
////////////        POWER               ///////////         
///////////////////////////////////////////////////

////////////////////Commands
//[(0-Disable, 1-Enable)], [M1, M2, M3, M4, Spare (Bitmask)]
#define RC_POWER_MOTORBUSENABLE_DATA_ID                               3000      
#define RC_POWER_MOTORBUSENABLE_DATA_COUNT                            1         
#define RC_POWER_MOTORBUSENABLE_DATA_TYPE                             uint8_t   

//[(0-Disable, 1-Enable)], [Gimbal, Multi, Aux (Bitmask)]
#define RC_POWER_12VACTBUSENABLE_DATA_ID                              3001      
#define RC_POWER_12VACTBUSENABLE_DATA_COUNT                           1         
#define RC_POWER_12VACTBUSENABLE_DATA_TYPE                            uint8_t   

//[(0-Disable, 1-Enable)], [Gimbal, Multi, Aux, Drive, Nav, Cam, Extra (Bitmask)]
#define RC_POWER_12VLOGICBUSENABLE_DATA_ID                            3002      
#define RC_POWER_12VLOGICBUSENABLE_DATA_COUNT                         1         
#define RC_POWER_12VLOGICBUSENABLE_DATA_TYPE                          uint8_t   

//[(0-Disable, 1-Enable)], [12V, Rockets, Aux, Drive (Bitmask)]
#define RC_POWER_30VBUSENABLED_DATA_ID                                3003      
#define RC_POWER_30VBUSENABLED_DATA_COUNT                             1         
#define RC_POWER_30VBUSENABLED_DATA_TYPE                              uint8_t   

//[(0-Disable, 1-Enable)]
#define RC_POWER_VACUUMENABLED_DATA_ID                                3004      
#define RC_POWER_VACUUMENABLED_DATA_COUNT                             1         
#define RC_POWER_VACUUMENABLED_DATA_TYPE                              uint8_t   

////////////////////Telemetry
//[(0-Disabled, 1-Enabled)],[M1, M2, M3, M4, Spare(Bitmask)]
#define RC_POWER_MOTORBUSENABLED_DATA_ID                              3100      
#define RC_POWER_MOTORBUSENABLED_DATA_COUNT                           1         
#define RC_POWER_MOTORBUSENABLED_DATA_TYPE                            uint8_t   

//[(0-Disable, 1-Enable)], [Gimbal, Multi, Aux (Bitmask)]
#define RC_POWER_12VACTBUSENABLED_DATA_ID                             3101      
#define RC_POWER_12VACTBUSENABLED_DATA_COUNT                          1         
#define RC_POWER_12VACTBUSENABLED_DATA_TYPE                           uint8_t   

//[(0-Disable, 1-Enable)], [Gimbal, Multi, Aux, Drive, Nav, Cam, Extra (Bitmask)]
#define RC_POWER_12VLOGICBUSENABLED_DATA_ID                           3102      
#define RC_POWER_12VLOGICBUSENABLED_DATA_COUNT                        1         
#define RC_POWER_12VLOGICBUSENABLED_DATA_TYPE                         uint8_t   

//[(0-Disable, 1-Enable)], [12V, Rockets, Aux, Drive (Bitmask)]
#define RC_POWER_THIRTYVENABLED_DATA_ID                               3103      
#define RC_POWER_THIRTYVENABLED_DATA_COUNT                            1         
#define RC_POWER_THIRTYVENABLED_DATA_TYPE                             uint8_t   

//[(0-Disabled, 1-Enabled)]
#define RC_POWER_VACUUMENABLED_DATA_ID                                3104      
#define RC_POWER_VACUUMENABLED_DATA_COUNT                             1         
#define RC_POWER_VACUUMENABLED_DATA_TYPE                              uint8_t   

//[M1, M2, M3, M4, Spare] (A)
#define RC_POWER_MOTORBUSCURRENT_DATA_ID                              3105      
#define RC_POWER_MOTORBUSCURRENT_DATA_COUNT                           5         
#define RC_POWER_MOTORBUSCURRENT_DATA_TYPE                            float     

//[Gimbal, Multi, Aux, Logic] (A)
#define RC_POWER_12VBUSCURRENT_DATA_ID                                3106      
#define RC_POWER_12VBUSCURRENT_DATA_COUNT                             4         
#define RC_POWER_12VBUSCURRENT_DATA_TYPE                              float     

//[12V Board, Rockets, Aux, Drive] (A)
#define RC_POWER_30VBUSCURRENT_DATA_ID                                3107      
#define RC_POWER_30VBUSCURRENT_DATA_COUNT                             4         
#define RC_POWER_30VBUSCURRENT_DATA_TYPE                              float     

//[Vacuum] (A)
#define RC_POWER_VACUUMCURRENT_DATA_ID                                3108      
#define RC_POWER_VACUUMCURRENT_DATA_COUNT                             1         
#define RC_POWER_VACUUMCURRENT_DATA_TYPE                              float     

////////////////////Error
//[(0-undermaxcurrent, 1-overcurrent)] [M1, M2, M3, M4, Spare (Bitmask)]
#define RC_POWER_MOTORBUSOVERCURRENT_DATA_ID                          3200      
#define RC_POWER_MOTORBUSOVERCURRENT_DATA_COUNT                       1         
#define RC_POWER_MOTORBUSOVERCURRENT_DATA_TYPE                        uint8_t   

//[(0-undermaxcurrent, 1-overcurrent)] [Gimbal, Multi, Aux, Logic (Bitmask)]
#define RC_POWER_12VBUSOVERCURRENT_DATA_ID                            3201      
#define RC_POWER_12VBUSOVERCURRENT_DATA_COUNT                         1         
#define RC_POWER_12VBUSOVERCURRENT_DATA_TYPE                          uint8_t   

//[(0-undermaxcurrent, 1-overcurrent)] [12V Board, Rockets, Aux, Drive (Bitmask)]
#define RC_POWER_30VBUSOVERCURRENT_DATA_ID                            3202      
#define RC_POWER_30VBUSOVERCURRENT_DATA_COUNT                         1         
#define RC_POWER_30VBUSOVERCURRENT_DATA_TYPE                          uint8_t   

//[(0-undermaxcurrent, 1-overcurrent)] [Vacuum]
#define RC_POWER_VACCUUMOVERCURRENT_DATA_ID                           3203      
#define RC_POWER_VACCUUMOVERCURRENT_DATA_COUNT                        1         
#define RC_POWER_VACCUUMOVERCURRENT_DATA_TYPE                         uint8_t   



///////////////////////////////////////////////////
////////////        NAV                 ///////////         
///////////////////////////////////////////////////

////////////////////Commands
////////////////////Telemetry
//[Lat, Long] [(-90, 90), (-180, 180)] (deg)
#define RC_NAV_GPSLATLON_DATA_ID                                      5100      
#define RC_NAV_GPSLATLON_DATA_COUNT                                   2         
#define RC_NAV_GPSLATLON_DATA_TYPE                                    double    

//[Pitch, Yaw, Roll] [(-90, 90), (0, 360), (-90, 90)] (deg)
#define RC_NAV_IMUDATA_DATA_ID                                        5101      
#define RC_NAV_IMUDATA_DATA_COUNT                                     3         
#define RC_NAV_IMUDATA_DATA_TYPE                                      float     

//[Distance, Quality]
#define RC_NAV_LIDARDATA_DATA_ID                                      5101      
#define RC_NAV_LIDARDATA_DATA_COUNT                                   2         
#define RC_NAV_LIDARDATA_DATA_TYPE                                    float     

////////////////////Error
//
#define RC_NAV_GPSLOCKERROR_DATA_ID                                   5200      
#define RC_NAV_GPSLOCKERROR_DATA_COUNT                                1         
#define RC_NAV_GPSLOCKERROR_DATA_TYPE                                 uint8_t   



///////////////////////////////////////////////////
////////////        GIMBAL              ///////////         
///////////////////////////////////////////////////

////////////////////Commands
//[Pan, Tilt](degrees 0-270)
#define RC_GIMBAL_LEFTDRIVEGIMBALINCREMENT_DATA_ID                    6000      
#define RC_GIMBAL_LEFTDRIVEGIMBALINCREMENT_DATA_COUNT                 2         
#define RC_GIMBAL_LEFTDRIVEGIMBALINCREMENT_DATA_TYPE                  int16_t   

//[Pan, Tilt](degrees 0-270)
#define RC_GIMBAL_RIGHTDRIVEGIMBALINCREMENT_DATA_ID                   6001      
#define RC_GIMBAL_RIGHTDRIVEGIMBALINCREMENT_DATA_COUNT                2         
#define RC_GIMBAL_RIGHTDRIVEGIMBALINCREMENT_DATA_TYPE                 int16_t   

//[Pan, Tilt](degrees 0-270)
#define RC_GIMBAL_LEFTMAINGIMBALINCREMENT_DATA_ID                     6002      
#define RC_GIMBAL_LEFTMAINGIMBALINCREMENT_DATA_COUNT                  2         
#define RC_GIMBAL_LEFTMAINGIMBALINCREMENT_DATA_TYPE                   int16_t   

//[Pan, Tilt](degrees 0-270)
#define RC_GIMBAL_RIGHTMAINGIMBALINCREMENT_DATA_ID                    6003      
#define RC_GIMBAL_RIGHTMAINGIMBALINCREMENT_DATA_COUNT                 2         
#define RC_GIMBAL_RIGHTMAINGIMBALINCREMENT_DATA_TYPE                  int16_t   

//[Pan, Tilt](degrees 0-270)
#define RC_GIMBAL_LEFTDRIVEGIMBALABSOLUTE_DATA_ID                     6004      
#define RC_GIMBAL_LEFTDRIVEGIMBALABSOLUTE_DATA_COUNT                  2         
#define RC_GIMBAL_LEFTDRIVEGIMBALABSOLUTE_DATA_TYPE                   int16_t   

//[Pan, Tilt](degrees 0-270)
#define RC_GIMBAL_RIGHTDRIVEGIMBALABSOLUTE_DATA_ID                    6005      
#define RC_GIMBAL_RIGHTDRIVEGIMBALABSOLUTE_DATA_COUNT                 2         
#define RC_GIMBAL_RIGHTDRIVEGIMBALABSOLUTE_DATA_TYPE                  int16_t   

//[Pan, Tilt](degrees 0-270)
#define RC_GIMBAL_LEFTMAINGIMBALABSOLUTE_DATA_ID                      6006      
#define RC_GIMBAL_LEFTMAINGIMBALABSOLUTE_DATA_COUNT                   2         
#define RC_GIMBAL_LEFTMAINGIMBALABSOLUTE_DATA_TYPE                    int16_t   

//[Pan, Tilt](degrees 0-270)
#define RC_GIMBAL_RIGHTMAINGIMBALABSOLUTE_DATA_ID                     6007      
#define RC_GIMBAL_RIGHTMAINGIMBALABSOLUTE_DATA_COUNT                  2         
#define RC_GIMBAL_RIGHTMAINGIMBALABSOLUTE_DATA_TYPE                   int16_t   

//
#define RC_GIMBAL_INITIATETESTROUTINE_DATA_ID                         6008      
#define RC_GIMBAL_INITIATETESTROUTINE_DATA_COUNT                      1         
#define RC_GIMBAL_INITIATETESTROUTINE_DATA_TYPE                       uint8_t   

////////////////////Telemetry
//Array of 8 servo positions
#define RC_GIMBAL_SERVOPOSITION_DATA_ID                               6100      
#define RC_GIMBAL_SERVOPOSITION_DATA_COUNT                            8         
#define RC_GIMBAL_SERVOPOSITION_DATA_TYPE                             int16_t   

////////////////////Error


///////////////////////////////////////////////////
////////////        MULTIMEDIA          ///////////         
///////////////////////////////////////////////////

////////////////////Commands
//Headlight intensity for the front of rover
#define RC_MULTIMEDIA_HEADLIGHTINTENSITY_DATA_ID                      7000      
#define RC_MULTIMEDIA_HEADLIGHTINTENSITY_DATA_COUNT                   1         
#define RC_MULTIMEDIA_HEADLIGHTINTENSITY_DATA_TYPE                    uint8_t   

//[R, G, B] (0, 255)
#define RC_MULTIMEDIA_LEDRGB_DATA_ID                                  7001      
#define RC_MULTIMEDIA_LEDRGB_DATA_COUNT                               3         
#define RC_MULTIMEDIA_LEDRGB_DATA_TYPE                                uint8_t   

//[Pattern] (Enum)
#define RC_MULTIMEDIA_LEDPATTERNS_DATA_ID                             7002      
#define RC_MULTIMEDIA_LEDPATTERNS_DATA_COUNT                          1         
#define RC_MULTIMEDIA_LEDPATTERNS_DATA_TYPE                           uint8_t   

//[Teleop, Autonomy, Reached Goal] (enum)
#define RC_MULTIMEDIA_STATEDISPLAY_DATA_ID                            7003      
#define RC_MULTIMEDIA_STATEDISPLAY_DATA_COUNT                         1         
#define RC_MULTIMEDIA_STATEDISPLAY_DATA_TYPE                          uint8_t   

////////////////////Telemetry
////////////////////Error


///////////////////////////////////////////////////
////////////        ARM                 ///////////         
///////////////////////////////////////////////////

////////////////////Commands
//[J1, J2, J3, J4, J5, J6] (rpm)
#define RC_ARM_ARMVELOCITYCONTROL_DATA_ID                             8000      
#define RC_ARM_ARMVELOCITYCONTROL_DATA_COUNT                          6         
#define RC_ARM_ARMVELOCITYCONTROL_DATA_TYPE                           int16_t   

//[J1, J2, J3, J4, J5, J6] (Degrees)
#define RC_ARM_ARMMOVETOPOSITION_DATA_ID                              8001      
#define RC_ARM_ARMMOVETOPOSITION_DATA_COUNT                           6         
#define RC_ARM_ARMMOVETOPOSITION_DATA_TYPE                            float     

//[J1, J2, J3, J4, J5, J6] (Degrees)
#define RC_ARM_ARMINCREMENTPOSITION_DATA_ID                           8002      
#define RC_ARM_ARMINCREMENTPOSITION_DATA_COUNT                        6         
#define RC_ARM_ARMINCREMENTPOSITION_DATA_TYPE                         float     

//[X, Y, Z, Y, P, R] (in)
#define RC_ARM_ARMMOVEIK_DATA_ID                                      8003      
#define RC_ARM_ARMMOVEIK_DATA_COUNT                                   6         
#define RC_ARM_ARMMOVEIK_DATA_TYPE                                    float     

//[X, Y, Z, Y, P, R] (in)
#define RC_ARM_ARMINCREMENTIKROVER_DATA_ID                            8004      
#define RC_ARM_ARMINCREMENTIKROVER_DATA_COUNT                         6         
#define RC_ARM_ARMINCREMENTIKROVER_DATA_TYPE                          float     

//[X, Y, Z, Y, P, R] (in)
#define RC_ARM_ARMINCREMENTIKWRIST_DATA_ID                            8005      
#define RC_ARM_ARMINCREMENTIKWRIST_DATA_COUNT                         6         
#define RC_ARM_ARMINCREMENTIKWRIST_DATA_TYPE                          float     

//0-Disable Closed Loop, 1-Enable Closed Loop
#define RC_ARM_SETCLOSEDLOOPSTATE_DATA_ID                             8006      
#define RC_ARM_SETCLOSEDLOOPSTATE_DATA_COUNT                          1         
#define RC_ARM_SETCLOSEDLOOPSTATE_DATA_TYPE                           uint8_t   

//[Power] (-1000, 1000) (m%)
#define RC_ARM_GRIPPERMOVE_DATA_ID                                    8010      
#define RC_ARM_GRIPPERMOVE_DATA_COUNT                                 1         
#define RC_ARM_GRIPPERMOVE_DATA_TYPE                                  int16_t   

//[0-Turn off Watchdog Override, 1-Turn on Watchdog Override]
#define RC_ARM_WATCHDOGOVERRIDE_DATA_ID                               8011      
#define RC_ARM_WATCHDOGOVERRIDE_DATA_COUNT                            1         
#define RC_ARM_WATCHDOGOVERRIDE_DATA_TYPE                             uint8_t   

//[Base Tilt Up, Base Tilt Down, Base Twist CW, Base Twist CCW, Elbow Tilt Up, Elbow Tilt Down, Elbow  Twist CW, Elbow  Twist CCW] (0-Turn off Limit Switch Override, 1-Turn on Limit Switch Override) (bitmasked)
#define RC_ARM_LIMITSWITCHOVERRIDE_DATA_ID                            8012      
#define RC_ARM_LIMITSWITCHOVERRIDE_DATA_COUNT                         1         
#define RC_ARM_LIMITSWITCHOVERRIDE_DATA_TYPE                          uint8_t   

//[1-Base, 2-Elbow, 3-Wrist]
#define RC_ARM_REBOOTODRIVE_DATA_ID                                   8013      
#define RC_ARM_REBOOTODRIVE_DATA_COUNT                                1         
#define RC_ARM_REBOOTODRIVE_DATA_TYPE                                 uint8_t   

//Prompt arm for J1-6 positions
#define RC_ARM_REQUESTJOINTPOSITIONS_DATA_ID                          8014      
#define RC_ARM_REQUESTJOINTPOSITIONS_DATA_COUNT                       1         
#define RC_ARM_REQUESTJOINTPOSITIONS_DATA_TYPE                        uint8_t   

//Start auto pushing arm J1-6 positions
#define RC_ARM_TOGGLEPOSITIONTELEM_DATA_ID                            8015      
#define RC_ARM_TOGGLEPOSITIONTELEM_DATA_COUNT                         1         
#define RC_ARM_TOGGLEPOSITIONTELEM_DATA_TYPE                          uint8_t   

//Prompt arm for XYZPYR Data
#define RC_ARM_REQUESTAXESPOSITIONS_DATA_ID                           8016      
#define RC_ARM_REQUESTAXESPOSITIONS_DATA_COUNT                        1         
#define RC_ARM_REQUESTAXESPOSITIONS_DATA_TYPE                         uint8_t   

////////////////////Telemetry
//[M1, M2, M3, M4, M5, M6] (0, A)
#define RC_ARM_MOTORCURRENTS_DATA_ID                                  8100      
#define RC_ARM_MOTORCURRENTS_DATA_COUNT                               6         
#define RC_ARM_MOTORCURRENTS_DATA_TYPE                                float     

//[J1, J2, J3, J4, J5, J6] (0, Deg)
#define RC_ARM_JOINTANGLES_DATA_ID                                    8101      
#define RC_ARM_JOINTANGLES_DATA_COUNT                                 6         
#define RC_ARM_JOINTANGLES_DATA_TYPE                                  float     

//[J1, J2, J3, J4, J5, J6] (0, rpm)
#define RC_ARM_MOTORVELOCITIES_DATA_ID                                8102      
#define RC_ARM_MOTORVELOCITIES_DATA_COUNT                             6         
#define RC_ARM_MOTORVELOCITIES_DATA_TYPE                              float     

//[X, Y, Z, Y, P, R]
#define RC_ARM_IKCOORDINATES_DATA_ID                                  8103      
#define RC_ARM_IKCOORDINATES_DATA_COUNT                               6         
#define RC_ARM_IKCOORDINATES_DATA_TYPE                                float     

////////////////////Error
//[WatchDogStatus] (0-WD Not Triggered, 1-WD Triggered) 
#define RC_ARM_WATCHDOGSTATUS_DATA_ID                                 8200      
#define RC_ARM_WATCHDOGSTATUS_DATA_COUNT                              1         
#define RC_ARM_WATCHDOGSTATUS_DATA_TYPE                               uint8_t   

//[E1, E2, E3, E4, E5, E6] (0-Good, 1-Failure)
#define RC_ARM_ENCODERSTATUS_DATA_ID                                  8201      
#define RC_ARM_ENCODERSTATUS_DATA_COUNT                               1         
#define RC_ARM_ENCODERSTATUS_DATA_TYPE                                uint8_t   

//[Motor][Error Type][Error Specific]
#define RC_ARM_ODRIVEERROR_DATA_ID                                    8202      
#define RC_ARM_ODRIVEERROR_DATA_COUNT                                 3         
#define RC_ARM_ODRIVEERROR_DATA_TYPE                                  uint8_t   



///////////////////////////////////////////////////
////////////        SCIENCEACTUATION    ///////////         
///////////////////////////////////////////////////

////////////////////Commands
//[Power] (-1000, 1000) (m%)
#define RC_SCIENCEACTUATION_ZAXIS_DATA_ID                             9000      
#define RC_SCIENCEACTUATION_ZAXIS_DATA_COUNT                          1         
#define RC_SCIENCEACTUATION_ZAXIS_DATA_TYPE                           int16_t   

//[Power] (-1000, 1000) (m%)
#define RC_SCIENCEACTUATION_GENEVAOPENLOOP_DATA_ID                    9001      
#define RC_SCIENCEACTUATION_GENEVAOPENLOOP_DATA_COUNT                 1         
#define RC_SCIENCEACTUATION_GENEVAOPENLOOP_DATA_TYPE                  int16_t   

//[Chemical 1, Chemical 2, Chemical 3] (0, 1000) (m%)
#define RC_SCIENCEACTUATION_CHEMICALS_DATA_ID                         9002      
#define RC_SCIENCEACTUATION_CHEMICALS_DATA_COUNT                      3         
#define RC_SCIENCEACTUATION_CHEMICALS_DATA_TYPE                       uint16_t  

//[absolute position]
#define RC_SCIENCEACTUATION_GENEVATOPOSITION_DATA_ID                  9003      
#define RC_SCIENCEACTUATION_GENEVATOPOSITION_DATA_COUNT               1         
#define RC_SCIENCEACTUATION_GENEVATOPOSITION_DATA_TYPE                uint8_t   

//[relative position]
#define RC_SCIENCEACTUATION_GENEVAINCREMENTPOSITION_DATA_ID           9004      
#define RC_SCIENCEACTUATION_GENEVAINCREMENTPOSITION_DATA_COUNT        1         
#define RC_SCIENCEACTUATION_GENEVAINCREMENTPOSITION_DATA_TYPE         int8_t    

//[Z-axis Top, Z-axis Bottom, Geneva Set, Geneva Home] (0-Turn off Limit Switch Override, 1-Turn on Limit Switch Override) (bitmasked)
#define RC_SCIENCEACTUATION_LIMITSWITCHOVERRIDE_DATA_ID               9005      
#define RC_SCIENCEACTUATION_LIMITSWITCHOVERRIDE_DATA_COUNT            1         
#define RC_SCIENCEACTUATION_LIMITSWITCHOVERRIDE_DATA_TYPE             uint8_t   

//[Power] (-1000, 1000) (m%)
#define RC_SCIENCEACTUATION_MIXERVELOCITY_DATA_ID                     9006      
#define RC_SCIENCEACTUATION_MIXERVELOCITY_DATA_COUNT                  4         
#define RC_SCIENCEACTUATION_MIXERVELOCITY_DATA_TYPE                   int16_t   

////////////////////Telemetry
//[absolute position]
#define RC_SCIENCEACTUATION_GENEVACURRENTPOSITION_DATA_ID             9100      
#define RC_SCIENCEACTUATION_GENEVACURRENTPOSITION_DATA_COUNT          1         
#define RC_SCIENCEACTUATION_GENEVACURRENTPOSITION_DATA_TYPE           uint8_t   

//[Z-axis Top, Z-axis Bottom, Geneva Set, Geneva Home] (bitmasked)
#define RC_SCIENCEACTUATION_LIMITSWITCHTRIGGERED_DATA_ID              9101      
#define RC_SCIENCEACTUATION_LIMITSWITCHTRIGGERED_DATA_COUNT           1         
#define RC_SCIENCEACTUATION_LIMITSWITCHTRIGGERED_DATA_TYPE            uint8_t   

////////////////////Error


///////////////////////////////////////////////////
////////////        SCIENCESENSORS      ///////////         
///////////////////////////////////////////////////

////////////////////Commands
//[(LED On = 1/LED Off = 0)]
#define RC_SCIENCESENSORS_UVLEDCONTROL_DATA_ID                        10000     
#define RC_SCIENCESENSORS_UVLEDCONTROL_DATA_COUNT                     1         
#define RC_SCIENCESENSORS_UVLEDCONTROL_DATA_TYPE                      uint8_t   

//
#define RC_SCIENCESENSORS_RUNSPECTROMETER_DATA_ID                     10001     
#define RC_SCIENCESENSORS_RUNSPECTROMETER_DATA_COUNT                  1         
#define RC_SCIENCESENSORS_RUNSPECTROMETER_DATA_TYPE                   uint8_t   

////////////////////Telemetry
//Sends half of the spectrum read
#define RC_SCIENCESENSORS_SPECTROMETERDATA_DATA_ID                    10100     
#define RC_SCIENCESENSORS_SPECTROMETERDATA_DATA_COUNT                 144       
#define RC_SCIENCESENSORS_SPECTROMETERDATA_DATA_TYPE                  uint16_t  

//[Gass concentration %, Temperature (C)]
#define RC_SCIENCESENSORS_METHANE_DATA_ID                             10101     
#define RC_SCIENCESENSORS_METHANE_DATA_COUNT                          2         
#define RC_SCIENCESENSORS_METHANE_DATA_TYPE                           float     

//[CO2 Concentration (ppm)]
#define RC_SCIENCESENSORS_CO2_DATA_ID                                 10102     
#define RC_SCIENCESENSORS_CO2_DATA_COUNT                              1         
#define RC_SCIENCESENSORS_CO2_DATA_TYPE                               uint16_t  

//[partial pressure, (mBar), temperature (C), concentration (ppm), barometric pressue (mBar)]
#define RC_SCIENCESENSORS_O2_DATA_ID                                  10103     
#define RC_SCIENCESENSORS_O2_DATA_COUNT                               4         
#define RC_SCIENCESENSORS_O2_DATA_TYPE                                float     

//
#define RC_SCIENCESENSORS_NO_DATA_ID                                  10104     
#define RC_SCIENCESENSORS_NO_DATA_COUNT                               1         
#define RC_SCIENCESENSORS_NO_DATA_TYPE                                float     

//[ N2O volume (ppm)]
#define RC_SCIENCESENSORS_N20_DATA_ID                                 10105     
#define RC_SCIENCESENSORS_N20_DATA_COUNT                              1         
#define RC_SCIENCESENSORS_N20_DATA_TYPE                               uint16_t  

////////////////////Error


///////////////////////////////////////////////////
////////////        AUTONOMY            ///////////         
///////////////////////////////////////////////////

////////////////////Commands
//
#define RC_AUTONOMY_STARTAUTONOMY_DATA_ID                             11000     
#define RC_AUTONOMY_STARTAUTONOMY_DATA_COUNT                          1         
#define RC_AUTONOMY_STARTAUTONOMY_DATA_TYPE                           uint8_t   

//
#define RC_AUTONOMY_DISABLEAUTONOMY_DATA_ID                           11001     
#define RC_AUTONOMY_DISABLEAUTONOMY_DATA_COUNT                        1         
#define RC_AUTONOMY_DISABLEAUTONOMY_DATA_TYPE                         uint8_t   

//[Lat, Lon]
#define RC_AUTONOMY_ADDWAYPOINTS_DATA_ID                              11002     
#define RC_AUTONOMY_ADDWAYPOINTS_DATA_COUNT                           2         
#define RC_AUTONOMY_ADDWAYPOINTS_DATA_TYPE                            double    

//
#define RC_AUTONOMY_CLEARWAYPOINTS_DATA_ID                            11003     
#define RC_AUTONOMY_CLEARWAYPOINTS_DATA_COUNT                         1         
#define RC_AUTONOMY_CLEARWAYPOINTS_DATA_TYPE                          uint8_t   

////////////////////Telemetry
//Enum (Idle, Navigating, SearchPattern, Approaching Marker)
#define RC_AUTONOMY_CURRENTSTATE_DATA_ID                              11100     
#define RC_AUTONOMY_CURRENTSTATE_DATA_COUNT                           1         
#define RC_AUTONOMY_CURRENTSTATE_DATA_TYPE                            uint8_t   

//
#define RC_AUTONOMY_REACHEDMARKER_DATA_ID                             11101     
#define RC_AUTONOMY_REACHEDMARKER_DATA_COUNT                          1         
#define RC_AUTONOMY_REACHEDMARKER_DATA_TYPE                           uint8_t   

////////////////////Error
//String version of most current error log
#define RC_AUTONOMY_CURRENTLOG_DATA_ID                                11200     
#define RC_AUTONOMY_CURRENTLOG_DATA_COUNT                             255       
#define RC_AUTONOMY_CURRENTLOG_DATA_TYPE                              char      



///////////////////////////////////////////////////
////////////        CAMERA1             ///////////         
///////////////////////////////////////////////////

////////////////////Commands
////////////////////Telemetry
////////////////////Error


///////////////////////////////////////////////////
////////////        CAMERA2             ///////////         
///////////////////////////////////////////////////

////////////////////Commands
////////////////////Telemetry
////////////////////Error


