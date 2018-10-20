#ifndef RoveCommManifest_h
#define RoveCommManifest_h

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////////////////////
//             Port, IP Addresses                                                            //
///////////////////////////////////////////////////////////////////////////////////////////////

const uint8_t ROVECOMM_ETHERNET_UDP_PORT      = 11000; // todo Skelton Port Masking

const uint8_t ROVECOMM_SUBNET_IP_FIRST_OCTET  =   192; // Rover Network Subnet IP address octet
const uint8_t ROVECOMM_SUBNET_IP_SECOND_OCTET =   168; // Rover Network Subnet IP address octet
const uint8_t ROVECOMM_SUBNET_IP_THIRD_OCTET  =     1; // Rover Network Subnet IP address octet

const  int    ROVECOMM_TESTBOARD_IP_OCTET     =   100; // This Board IP address octet

///////////////////////////////////////////////////
//             RoveComm System Id's              //
///////////////////////////////////////////////////

const int ROVECOMM_SUBSCRIBE_REQUEST_DATA_ID   = 1;
const int ROVECOMM_UNSUBSCRIBE_REQUEST_DATA_ID = 2;

///////////////////////////////////////////////////////////
//             RoveComm TestBoard Id's                   //
///////////////////////////////////////////////////////////

const int ROVECOMM_TESTBOARD_COMMAND_1000_DATA_ID   = 1000;
const int ROVECOMM_TESTBOARD_COMMAND_1001_DATA_ID   = 1001;

const int ROVECOMM_TESTBOARD_TELEMETRY_2000_DATA_ID = 2000;
const int ROVECOMM_TESTBOARD_TELEMETRY_2001_DATA_ID = 2001;

#endif // RoveCommManifest_h