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

struct RoveCommClient 
{
    RoveCommEthernetTCPClient client;
    IPAddress dest_ip;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RoveCommEthernetTCP
{
  public:
    RoveCommEthernetTCPServer TCPServer;
    RoveCommClient Clients[10];

    struct rovecomm_packet read();


    /////begin/////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Overloaded begin
	//Default ip address = 192.168.1.XXX
    //This TCP server will be configured with an IP and port from the RoveComm manifest and allow other boards and base-station
    //to securely communicate with it
	void begin(uint8_t server_ip_octet, const int port);
    void begin(const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const int port);

    /////connect/////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Allows for creating a new connection to a target IP
    //checks for whether we have already connected to the dest_ip and port, or otherwise grabs an available ethernet
    //client and connects it to the dest_ip and port
    void connect(const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const int port);

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

    ////writeReliableTo////////////////////////////////////////////////////////////////////////
	//Single-value writeReliableTo which ensures delivery
	//Overloaded for each data type
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const uint8_t  data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const uint16_t data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const uint32_t data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const int8_t   data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const int16_t  data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const int32_t  data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);

    //Array entry writeReliableTo which ensures delivery
	//Overloaded for each data type
    void writeReliableTo(const uint16_t data_id,    const int     data_count, const int      *data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const uint8_t  *data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const uint16_t *data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const uint32_t *data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const int8_t   *data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const int16_t  *data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
    void writeReliableTo(const uint16_t data_id,    const uint8_t data_count, const int32_t  *data,
                         const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3,
                         const uint8_t ip_octet_4,  const uint16_t port);
  private:
    const uint8_t MAX_NUM_TCP_CLIENTS = 10;
    uint8_t num_clients = 0;
};

#endif // RoveCommEthernetTCP_h