#ifndef RoveCommEthernetTCP_h
#define RoveCommEthernetTCP_h

#include <stdint.h>
#include <stddef.h>
#include <Energia.h>
#include <Ethernet.h>

#include "RoveCommManifest.h"
#include "RoveCommPacket.h"
#include "RoveCommEthernetTCPServer.h"
#include "RoveCommEthernetTCPClient.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RoveCommEthernetTCP
{
  public:
    RoveCommEthernetTCPServer* TCPServer;

    struct rovecomm_packet read();

    RoveCommEthernetTCP();

    /////begin/////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Overloaded begin
	//Default ip address = 192.168.1.XXX
    //This TCP server will be configured with an IP and port from the RoveComm manifest and allow other boards and base-station
    //to securely communicate with it
	void begin(uint8_t server_ip_octet, const int port);
    void begin(byte server_ip[4], const int port);

    /////connect/////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Allows for creating a new connection to a target IP
    //Returns a RoveComm TCP Client entity that has its own read() and write()
    RoveCommEthernetTCPClient* connect(byte dest_ip[4], const int port);

	/////writeReliable////////////////////////////////////////////////////////////////////////
	//Single-value writeReliable which ensures delivery
	//Overloaded for each data type
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint8_t  data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint16_t data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint32_t data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int8_t   data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int16_t  data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int32_t  data);

    //Array entry writeReliable which ensures delivery
	//Overloaded for each data type
    void writeReliable(const uint16_t data_id, const int     data_count, const int      *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint8_t  *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint16_t *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint32_t *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int8_t   *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int16_t  *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int32_t  *data);
};

#endif // RoveCommEthernetTCP_h