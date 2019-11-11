#ifndef RoveEthernetTcp_h
#define RoveEthernetTcp_h

#include <stdint.h>
#include <stddef.h>
#include <Energia.h>
#include <Ethernet.h>

#include "RoveCommManifest.h"
#include "RoveCommPacket.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RoveCommEthernetTcp
{
  public:
    EthernetServer server;

    struct rovecomm_packet read();

    /////begin/////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Overloaded begin
	//Default ip address = 192.168.1.XXX
	void begin(const int board_ip_octet);
	void begin(const uint8_t ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4);

	/////writeReliable////////////////////////////////////////////////////////////////////////
	//Single-value writeReliable
	//Overloaded for each data type
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint8_t  data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint16_t data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint32_t data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int8_t   data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int16_t  data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int32_t  data);

    //Array entry writeReliable
	//Overloaded for each data type
    void writeReliable(const uint16_t data_id, const int     data_count, const int      *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint8_t  *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint16_t *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const uint32_t *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int8_t   *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int16_t  *data);
    void writeReliable(const uint16_t data_id, const uint8_t data_count, const int32_t  *data);
  
  private:
    //Called by overloaded writeReliable functions
    void _writeReliable(  const uint8_t  data_type_length, const roveware::data_type_t data_type, 
                          const uint16_t data_id,    const uint8_t data_count, const void* data);
};

#endif // RoveCommEthernetTcp_h