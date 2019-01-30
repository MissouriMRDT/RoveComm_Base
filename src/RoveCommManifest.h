#ifndef RoveCommManifest_h
#define RoveCommManifest_h

#include <stdint.h>
#include "RoveCommPacket.h"

#define RC_ROVECOMM_ETHERNET_UDP_PORT      	 1100 // todo Skelton Port Masking

//IP Addresses
#define RC_ROVECOMM_SUBNET_IP_FIRST_OCTET     192
#define RC_ROVECOMM_SUBNET_IP_SECOND_OCTET    168
#define RC_ROVECOMM_SUBNET_IP_THIRD_OCTET       1
        
#define RC_ROCKETROVER900_FOURTHOCTET          82
#define RC_ROCKETBASE900_FOURTHOCTET           83
#define RC_ROCKETROVE58_FOURTHOCTET            84
#define RC_ROCKETBASE58_FOURTHOCTET            85
#define RC_ROCKETROVER24_FOURTHOCTET           86
#define RC_ROCKETROVERSPARE_FOURTHOCTET        87
        
#define RC_DRIVEBOARD_FOURTHOCTET              130
#define RC_ARMBOARD_FOURTHOCTET                131
#define RC_POWERBOARD_FOURTHOCTET              132
#define RC_BMSBOARD_FOURTHOCTET                133
#define RC_DRIVEBOARD_FOURTHOCTET              134
#define RC_LIGHTINGSHIMBLEBOARD_FOURTHOCTET    135
#define RC_NAVCAMERABOARD_FOURTHOCTET          136
#define RC_SRAACTUATIONBOARD_FOURTHOCTET       137
#define RC_SRASENSORSBOARD_FOURTHOCTET         138
#define RC_AUTONOMY_FOURTHOCTET                139
#define RC_SHIMBLENAVBOARD_FOURTHOCTET         140
        
#define RC_GRANDSTREAM1_FOURTHOCTET            227
#define RC_GRANDSTREAM2_FOURTHOCTET            226

/*RoveCommDataIDs: (0, 65535)
 *AABCC
 *AA-Board Number
 *B -Command Type
 *CC-Command Number
 */ 
 
//Board numbers
#define _DRIVEBOARD_BOARDNUMBER      01*1000
#define _BMSBOARD_BOARDNUMBER        02*1000
#define _POWERBOARD_BOARDNUMBER      03*1000
#define _CAMERABOARD_BOARDNUMBER     04*1000    
#define _NAVBOARD_BOARDNUMBER        05*1000    
#define _SHIMBLEBOARD_BOARDNUMBER    06*1000    
#define _LIGHTINGBOARD_BOARDNUMBER   07*1000    
#define _ARMBOARD_BOARDNUMBER        08*1000    
#define _SRAACTUATION_BOARDNUMBER    09*1000    
#define _SRASENSORS_BOARDNUMBER      10*1000    
#define _OPEN_BOARDNUMBER            11*1000   

//Command Types
#define _TYPE_COMMAND     0*100
#define _TYPE_TELEMETRY   1*100


///////////////////////////////////////////////////
//             RoveComm System Id's              //
///////////////////////////////////////////////////
#define RC_ROVECOMM_PING_DATA_ID					1
#define RC_ROVECOMM_PING_REPLY_DATA_ID				2
#define RC_ROVECOMM_SUBSCRIBE_REQUEST_DATA_ID		3
#define	RC_ROVECOMM_UNSUBSCRIBE_REQUEST_DATA_ID 	4
#define	ROVECOMM_INVALID_VERSION_DATA_ID			5		

///////////////////////////////////////////////////
//                DriveBoard                     //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_DRIVEBOARD_DRIVELEFTRIGHT_DATAID            	00+_TYPE_COMMAND+_DRIVEBOARD_BOARDNUMBER
#define RC_DRIVEBOARD_DRIVELEFTRIGHT_DATATYPE          	int16_t			// (-1000, 1000)-->(-100%, 100%)
#define RC_DRIVEBOARD_DRIVELEFTRIGHT_DATACOUNT        	2				//[LeftSpeed, RightSpeed]
#define RC_DRIVEBOARD_DRIVELEFTRIGHT_HEADER				RC_DRIVEBOARD_DRIVELEFTRIGHT_DATAID,RC_DRIVEBOARD_DRIVELEFTRIGHT_DATACOUNT
#define RC_DRIVEBOARD_DRIVELEFTRIGHT_DRIVEMAXFORWARD   	1000
#define RC_DRIVEBOARD_DRIVELEFTRIGHT_DRIVEMAXREVERSE   	-1000
#define RC_DRIVEBOARD_DRIVELEFTRIGHT_DRIVEZERO         	0
#define RC_DRIVEBOARD_DRIVELEFTRIGHT_LEFTSPEEDENTRY    	0
#define RC_DRIVEBOARD_DRIVELEFTRIGHT_RIGHTSPEEDENTRY    1
        
#define RC_DRIVEBOARD_SPEEDRAMPVALUEs_DATAID            01+_TYPE_COMMAND+_DRIVEBOARD_BOARDNUMBER
#define RC_DRIVEBOARD_SPEEDRAMPVALUEs_DATATYPE          uint16_t		//ms to full speed
#define RC_DRIVEBOARD_SPEEDRAMPVALUEs_DATACOUNT        	1
#define RC_DRIVEBOARD_SPEEDRAMPVALUEs_HEADER			RC_DRIVEBOARD_SPEEDRAMPVALUEs_DATAID,RC_DRIVEBOARD_SPEEDRAMPVALUEs_DATACOUNT

//Telemetry////////////////////////////////////////////////////////////////////////////////////////////
#define RC_DRIVEBOARD_WACHDOGTRIGGERED_DATAID           00+_TYPE_CTELEMETRY+_DRIVEBOARD_BOARDNUMBER
#define RC_DRIVEBOARD_WACHDOGTRIGGERED_DATATYPE			uint8_t
#define RC_DRIVEBOARD_WACHDOGTRIGGERED_DATACOUNT       	1
#define RC_DRIVEBOARD_WACHDOGTRIGGERED_HEADER			RC_DRIVEBOARD_WACHDOGTRIGGERED_DATAID,RC_DRIVEBOARD_WACHDOGTRIGGERED_DATACOUNT
#define RC_DRIVEBOARD_WACHDOGTRIGGERED_TRIGGERED		1
#define RC_DRIVEBOARD_WACHDOGTRIGGERED_NOTTRIGGERED		0

///////////////////////////////////////////////////
//                BMSBoard                       //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_BMSBOARD_SWESTOPs_DATAID            	00+_TYPE_COMMAND+_BMSBOARD_BOARDNUMBER
#define RC_BMSBOARD_SWESTOPs_DATATYPE          	uint8_t		//ms delay before re-activation, 0 to stay off until reboot
#define RC_BMSBOARD_SWESTOPs_DATACOUNT        	1		
#define RC_BMSBOARD_SWESTOPs_HEADER				RC_BMSBOARD_SWESTOPs_DATAID,RC_BMSBOARD_SWESTOPs_DATACOUNT		

#define RC_BMSBOARD_FANEN_DATAID            	01+_TYPE_COMMAND+_BMSBOARD_BOARDNUMBER
#define RC_BMSBOARD_FANEN_DATATYPE          	uint8_t
#define RC_BMSBOARD_FANEN_DATACOUNT        		1		//[Fan1, Fan2, Fan3, Fan4, 0000]
#define RC_BMSBOARD_FANEN_HEADER				RC_BMSBOARD_FANEN_DATAID,RC_BMSBOARD_FANEN_DATACOUNT	
#define RC_BMSBOARD_FANEN_ENABLED   			1
#define RC_BMSBOARD_FANEN_DISABLED         		0
#define RC_BMSBOARD_FANEN_FAN1BIT		   		0
#define RC_BMSBOARD_FANEN_FAN2BIT		   		1
#define RC_BMSBOARD_FANEN_FAN3BIT		   		2
#define RC_BMSBOARD_FANEN_FAN4BIT		   		3

//Telemetry//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_BMSBOARD_MAINIMEASmA_DATAID          00+_TYPE_TELEMETRY+_BMSBOARD_BOARDNUMBER
#define RC_BMSBOARD_MAINIMEASmA_DATATYPE        uint16_t	//main current output mA
#define RC_BMSBOARD_MAINIMEASmA_DATACOUNT      	1
#define RC_BMSBOARD_MAINIMEASmA_HEADER			RC_BMSBOARD_MAINIMEASmA_DATAID,RC_BMSBOARD_MAINIMEASmA_DATACOUNT				

#define RC_BMSBOARD_VMEASmV_DATAID            	01+_TYPE_TELEMETRY+_BMSBOARD_BOARDNUMBER
#define RC_BMSBOARD_VMEASmV_DATATYPE          	uint16_t	//[Pack_Out, C1-G, C2-1, C3-2, C4-3, C5-4, C6-5, C7-6, C8-7]
#define RC_BMSBOARD_VMEASmV_DATACOUNT        	9	
#define RC_BMSBOARD_VMEASmV_HEADER				RC_BMSBOARD_VMEASmV_DATAID,RC_BMSBOARD_VMEASmV_DATACOUNT
#define RC_BMSBOARD_VMEASmV_PACKENTRY			0			
#define RC_BMSBOARD_VMEASmV_C1GENTRY			1
#define RC_BMSBOARD_VMEASmV_C21ENTRY			2
#define RC_BMSBOARD_VMEASmV_C32ENTRY			3
#define RC_BMSBOARD_VMEASmV_C43ENTRY			4
#define RC_BMSBOARD_VMEASmV_C54ENTRY			5
#define RC_BMSBOARD_VMEASmV_C65ENTRY			6
#define RC_BMSBOARD_VMEASmV_C76ENTRY			7
#define RC_BMSBOARD_VMEASmV_C87ENTRY			8

#define RC_BMSBOARD_TEMPMEASmDEGC_DATAID        02+_TYPE_TELEMETRY+_BMSBOARD_BOARDNUMBER
#define RC_BMSBOARD_TEMPMEASmDEGC_DATATYPE      uint16_t	//Temperature Reading in mDeg Celcius
#define RC_BMSBOARD_TEMPMEASmDEGC_DATACOUNT     1
#define RC_BMSBOARD_TEMPMEASmDEGC_HEADER		RC_BMSBOARD_TEMPMEASmDEGC_DATAID,RC_TEMPMEASmDEGC_MAINIMEASmA_DATACOUNT				

///////////////////////////////////////////////////
//                PowerBoard                     //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_POWERBOARD_BUSENABLE_DATAID          00+_TYPE_COMMAND+_POWERBOARD_BOARDNUMBER
#define RC_POWERBOARD_BUSENABLE_DATATYPE        uint8_t		//[Act, Log, Comm, 0 0000], [M1, M2, M3, M4, M5, M6, M7, Aux]
#define RC_POWERBOARD_BUSENABLE_DATACOUNT       2		
#define RC_POWERBOARD_BUSENABLE_HEADER			RC_POWERBOARD_BUSENABLE_DATAID,RC_POWERBOARD_BUSENABLE_DATACOUNT		
#define RC_POWERBOARD_BUSENABLE_ENABLE			1
#define RC_POWERBOARD_BUSENABLE_DISABLE         0
#define RC_POWERBOARD_BUSENABLE_ACTBIT		   	0
#define RC_POWERBOARD_BUSENABLE_LOGBIT		   	1
#define RC_POWERBOARD_BUSENABLE_COMMBIT		   	2
#define RC_POWERBOARD_BUSENABLE_M1BIT		   	0
#define RC_POWERBOARD_BUSENABLE_M2BIT		   	1
#define RC_POWERBOARD_BUSENABLE_M3BIT		   	2
#define RC_POWERBOARD_BUSENABLE_M4BIT		   	3
#define RC_POWERBOARD_BUSENABLE_M5BIT		   	4
#define RC_POWERBOARD_BUSENABLE_M6BIT		   	5
#define RC_POWERBOARD_BUSENABLE_M7BIT		   	6
#define RC_POWERBOARD_BUSENABLE_AUXBIT		   	7
#define RC_POWERBOARD_BUSENABLE_ALCENTRY		0
#define RC_POWERBOARD_BUSENABLE_MOTORSENTRY		1

//Telemetry//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_POWERBOARD_IMEASmA_DATAID            00+_TYPE_TELEMETRY+_POWERBOARD_BOARDNUMBER
#define RC_POWERBOARD_IMEASmA_DATATYPE          uint16_t	//[Act, Log, Comm, M1, M2, M3, M4, M5, M6, M7, Aux]
#define RC_POWERBOARD_IMEASmA_DATACOUNT         11	
#define RC_POWERBOARD_IMEASmA_HEADER			RC_POWERBOARD_IMEASmA_DATAID,RC_POWERBOARD_IMEASmA_DATACOUNT				
#define RC_POWERBOARD_IMEASmA_ACTENTRY			0
#define RC_POWERBOARD_IMEASmA_LOGENTRY			1
#define RC_POWERBOARD_IMEASmA_COMMENTRY			2
#define RC_POWERBOARD_IMEASmA_M1ENTRY			3
#define RC_POWERBOARD_IMEASmA_M2ENTRY			4
#define RC_POWERBOARD_IMEASmA_M3ENTRY			5
#define RC_POWERBOARD_IMEASmA_M4ENTRY			6
#define RC_POWERBOARD_IMEASmA_M5ENTRY			7
#define RC_POWERBOARD_IMEASmA_M6ENTRY			8
#define RC_POWERBOARD_IMEASmA_M7ENTRY			9
#define RC_POWERBOARD_IMEASmA_AUXENTRY			10

#define RC_POWERBOARD_BUSENABLED_DATAID			01+_TYPE_TELEMETRY+_POWERBOARD_BOARDNUMBER
#define RC_POWERBOARD_BUSENABLED_DATATYPE       uint8_t	//[Act, Log, Comm, 0 0000], [M1, M2, M3, M4, M5, M6, M7, Aux]
#define RC_POWERBOARD_BUSENABLED_DATACOUNT      2
#define RC_POWERBOARD_BUSENABLED_HEADER			RC_POWERBOARD_BUSENABLED_DATAID,RC_POWERBOARD_BUSENABLED_DATACOUNT			
#define RC_POWERBOARD_BUSENABLE_ENABLED   		1
#define RC_POWERBOARD_BUSENABLE_DISABLED        0		
#define RC_POWERBOARD_BUSENABLED_ACTBIT		   	0
#define RC_POWERBOARD_BUSENABLED_LOGBIT		   	1
#define RC_POWERBOARD_BUSENABLED_COMMBIT		2
#define RC_POWERBOARD_BUSENABLED_M1BIT		   	0
#define RC_POWERBOARD_BUSENABLED_M2BIT		   	1
#define RC_POWERBOARD_BUSENABLED_M3BIT		   	2
#define RC_POWERBOARD_BUSENABLED_M4BIT		   	3
#define RC_POWERBOARD_BUSENABLED_M5BIT		   	4
#define RC_POWERBOARD_BUSENABLED_M6BIT		   	5
#define RC_POWERBOARD_BUSENABLED_M7BIT		   	6
#define RC_POWERBOARD_BUSENABLED_AUXBIT		   	7
#define RC_POWERBOARD_BUSENABLED_ALCENTRY		0
#define RC_POWERBOARD_BUSENABLED_MOTORSENTRY	1

///////////////////////////////////////////////////
//                CameraBoard                    //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_CAMERABOARD_CAMMUX_DATAID            	00+_TYPE_COMMAND+_CAMERABOARD_BOARDNUMBER
#define RC_CAMERABOARD_CAMMUX_DATATYPE          	uint8_t
#define RC_CAMERABOARD_CAMMUX_DATACOUNT        		1		//(0-3) (Cam0-Cam3)
#define RC_CAMERABOARD_CAMMUX_HEADER				RC_CAMERABOARD_CAMMUX_DATAID,RC_CAMERABOARD_CAMMUX_DATACOUNT	
#define RC_CAMERABOARD_CAMMUX_ENABLED   			1
#define RC_CAMERABOARD_CAMMUX_DISABLED         		0

//Telemetry//////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////
//                NavigationBoard                //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_NAVBOARD_CALIBRATEIMU_DATAID            	00+_TYPE_COMMAND+_NAVBOARD_BOARDNUMBER
#define RC_NAVBOARD_CALIBRATEIMU_DATATYPE          	uint8_t		//calibration time ms
#define RC_NAVBOARD_CALIBRATEIMU_DATACOUNT        	1		
#define RC_NAVBOARD_CALIBRATEIMU_HEADER				RC_NAVBOARD_CALIBRATEIMU_DATAID,RC_NAVBOARD_CALIBRATEIMU_DATACOUNT		

//Telemetry//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_NAVBOARD_GPSLATLON_DATAID        	00+_TYPE_TELEMETRY+_NAVBOARD_BOARDNUMBER
#define RC_NAVBOARD_GPSLATLON_DATATYPE      	int32_t	//Latitude longitude in udeg
#define RC_NAVBOARD_GPSLATLON_DATACOUNT			2	//[lat][lon]
#define RC_NAVBOARD_GPSLATLON_HEADER			RCNAVBOARD_GPSLATLON_DATAID,RC_NAVBOARD_GPSLATLON_DATACOUNT				
#define RC_NAVBOARD_GPSLATLON_LATENTRY			0
#define RC_NAVBOARD_GPSLATLON_LONENTRY			1

#define RC_NAVBOARD_IMUPYR_DATAID          		01+_TYPE_TELEMETRY+_NAVBOARD_BOARDNUMBER
#define RC_NAVBOARD_IMUPYR_DATATYPE        		int16_t	//PYR in deg-1
#define RC_NAVBOARD_IMUPYR_DATACOUNT			3		//[pitch][yaw][roll]
#define RC_NAVBOARD_IMUPYR_HEADER				RC_NAVBOARD_IMUPYR_DATAID,RC_NAVBOARD_IMUPYR_DATACOUNT				
#define RC_NAVBOARD_IMUPYR_PITCHENTRY			0
#define RC_NAVBOARD_IMUPYR_YAWENTRY				1
#define RC_NAVBOARD_IMUPYR_ROLLENTRY			2

///////////////////////////////////////////////////
//                ShimbleBoard                   //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_SHIMBLEBOARD_SERVOINC_DATAID         00+_TYPE_TELEMETRY+_SHIMBLEBOARD_BOARDNUMBER
#define RC_SHIMBLEBOARD_SERVOINC_DATATYPE       int16_t	//Degrees
#define RC_SHIMBLEBOARD_SERVOINC_DATACOUNT		8		//[S1][S2][S3][S4][S5][S6][S7][S8]
#define RC_SHIMBLEBOARD_SERVOINC_HEADER			RC_SHIMBLEBOARD_SERVOINC_DATAID,RC_SHIMBLEBOARD_SERVOINC_DATACOUNT				
#define RC_SHIMBLEBOARD_SERVOINC_S1ENTRY		0
#define RC_SHIMBLEBOARD_SERVOINC_S2ENTRY		1
#define RC_SHIMBLEBOARD_SERVOINC_S3ENTRY		2
#define RC_SHIMBLEBOARD_SERVOINC_S4ENTRY		3
#define RC_SHIMBLEBOARD_SERVOINC_S5ENTRY		4
#define RC_SHIMBLEBOARD_SERVOINC_S6ENTRY		5
#define RC_SHIMBLEBOARD_SERVOINC_S7ENTRY		6
#define RC_SHIMBLEBOARD_SERVOINC_S8ENTRY		7

#define RC_SHIMBLEBOARD_SERVOTOPOS_DATAID       01+_TYPE_TELEMETRY+_SHIMBLEBOARD_BOARDNUMBER
#define RC_SHIMBLEBOARD_SERVOTOPOS_DATATYPE     int16_t	//Degrees
#define RC_SHIMBLEBOARD_SERVOTOPOS_DATACOUNT	8		//[S1][S2][S3][S4][S5][S6][S7][S8]
#define RC_SHIMBLEBOARD_SERVOTOPOS_HEADER		RC_SHIMBLEBOARD_SERVOTOPOS_DATAID,RC_SHIMBLEBOARD_SERVOTOPOS_DATACOUNT				
#define RC_SHIMBLEBOARD_SERVOTOPOS_S1ENTRY		0
#define RC_SHIMBLEBOARD_SERVOTOPOS_S2ENTRY		1
#define RC_SHIMBLEBOARD_SERVOTOPOS_S3ENTRY		2
#define RC_SHIMBLEBOARD_SERVOTOPOS_S4ENTRY		3
#define RC_SHIMBLEBOARD_SERVOTOPOS_S5ENTRY		4
#define RC_SHIMBLEBOARD_SERVOTOPOS_S6ENTRY		5
#define RC_SHIMBLEBOARD_SERVOTOPOS_S7ENTRY		6
#define RC_SHIMBLEBOARD_SERVOTOPOS_S8ENTRY		7

#define RC_SHIMBLEBOARD_SERVOTOSETPOS_DATAID    02+_TYPE_TELEMETRY+_SHIMBLEBOARD_BOARDNUMBER
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_DATATYPE  uint8_t	//set position
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_DATACOUNT	8		//[S1][S2][S3][S4][S5][S6][S7][S8]
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_HEADER	RC_SHIMBLEBOARD_SERVOTOSETPOS_DATAID,RC_SHIMBLEBOARD_SERVOTOSETPOS_DATACOUNT				
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_S1ENTRY	0
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_S2ENTRY	1
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_S3ENTRY	2
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_S4ENTRY	3
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_S5ENTRY	4
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_S6ENTRY	5
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_S7ENTRY	6
#define RC_SHIMBLEBOARD_SERVOTOSETPOS_S8ENTRY	7

//Telemetry//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_SHIMBLEBOARD_SERVOPOS_DATAID       	00+_TYPE_TELEMETRY+_SHIMBLEBOARD_BOARDNUMBER
#define RC_SHIMBLEBOARD_SERVOPOS_DATATYPE     	int16_t	//Degrees
#define RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT		8		//[S1][S2][S3][S4][S5][S6][S7][S8]
#define RC_SHIMBLEBOARD_SERVOPOS_HEADER			RC_SHIMBLEBOARD_SERVOPOS_DATAID,RC_SHIMBLEBOARD_SERVOPOS_DATACOUNT				
#define RC_SHIMBLEBOARD_SERVOPOS_S1ENTRY		0
#define RC_SHIMBLEBOARD_SERVOPOS_S2ENTRY		1
#define RC_SHIMBLEBOARD_SERVOPOS_S3ENTRY		2
#define RC_SHIMBLEBOARD_SERVOPOS_S4ENTRY		3
#define RC_SHIMBLEBOARD_SERVOPOS_S5ENTRY		4
#define RC_SHIMBLEBOARD_SERVOPOS_S6ENTRY		5
#define RC_SHIMBLEBOARD_SERVOPOS_S7ENTRY		6
#define RC_SHIMBLEBOARD_SERVOPOS_S8ENTRY		7

///////////////////////////////////////////////////
//                LightingBoard                  //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////
#define RC_LIGHTINGBOARD_SETLEDINTENS_DATAID            	00+_TYPE_COMMAND+_LIGHTINGBOARD_BOARDNUMBER
#define RC_LIGHTINGBOARD_SETLEDINTENS_DATATYPE          	uint16_t		//0-1000 %-1
#define RC_LIGHTINGBOARD_SETLEDINTENS_DATACOUNT        		1		
#define RC_LIGHTINGBOARD_SETLEDINTENS_HEADER				RC_LIGHTINGBOARD_SETLEDINTENS_DATAID,RC_LIGHTINGBOARD_SETLEDINTENS_DATACOUNT		
#define RC_LIGHTINGBOARD_SETLEDINTENS_LEFTHEADLIGHTENTRY	0
#define RC_LIGHTINGBOARD_SETLEDINTENS_RIGHTHEADLIGHTENTRY	1

#define RC_LIGHTINGBOARD_SETRGB_DATAID            			10+_TYPE_COMMAND+_LIGHTINGBOARD_BOARDNUMBER
#define RC_LIGHTINGBOARD_SETRGB_DATATYPE          			uint8_t		//0-255 rgb value
#define RC_LIGHTINGBOARD_SETRGB_DATACOUNT        			3			//[red][green][blue]
#define RC_LIGHTINGBOARD_SETRGB_HEADER						RC_LIGHTINGBOARD_SETRGB_DATAID,RC_LIGHTINGBOARD_SETRGB_DATACOUNT		
#define RC_LIGHTINGBOARD_SETRGB_REDENTRY					0
#define RC_LIGHTINGBOARD_SETRGB_GREENENTRY					1
#define RC_LIGHTINGBOARD_SETRGB_BLUEENTRY					1

#define RC_LIGHTINGBOARD_LEDCMND_DATAID            			20+_TYPE_COMMAND+_LIGHTINGBOARD_BOARDNUMBER
#define RC_LIGHTINGBOARD_LEDCMND_DATATYPE          			uint8_t		//command number
#define RC_LIGHTINGBOARD_LEDCMND_DATACOUNT        			1			
#define RC_LIGHTINGBOARD_LEDCMND_HEADER						RC_LIGHTINGBOARD_LEDCMND_DATAID,RC_LIGHTINGBOARD_LEDCMND_DATACOUNT		

//Telemetry//////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////
//                ArmBoard                       //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////

//Telemetry//////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////
//                SRAActuationBoard              //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////

//Telemetry//////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////
//                SRASensorsBoard                //
///////////////////////////////////////////////////
//Commands//////////////////////////////////////////////////////////////////////////////////////////////

//Telemetry//////////////////////////////////////////////////////////////////////////////////////////////



#endif // RoveCommManifest_h