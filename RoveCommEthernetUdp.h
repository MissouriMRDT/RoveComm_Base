#ifndef RoveEthernetUdp_h
#define RoveEthernetUdp_h

#include <stdint.h>
#include <stddef.h>

#include "RoveCommProtocol.h"

class RoveCommEthernetUdp
{
	
  public:
    void begin(uint8_t ip_octet_1, uint8_t ip_octet_2, uint8_t ip_octet_3, uint8_t ip_octet_4);
    
    void write  (uint16_t  data_id, int data_count,  const uint8_t  data);
    void write  (uint16_t  data_id, int data_count,  const uint16_t data);
    void write  (uint16_t  data_id, int data_count,  const uint32_t data);
    void write  (uint16_t  data_id, int data_count,  const int8_t   data);
    void write  (uint16_t  data_id, int data_count,  const int16_t  data);
    void write  (uint16_t  data_id, int data_count,  const int32_t  data);
    
    void writeTo(uint16_t  data_id, int data_count,  const uint8_t  data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port);
    void writeTo(uint16_t  data_id, int data_count,  const uint16_t data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port);
    void writeTo(uint16_t  data_id, int data_count,  const uint32_t data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port);
    void writeTo(uint16_t  data_id, int data_count,  const int8_t   data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port);
    void writeTo(uint16_t  data_id, int data_count,  const int16_t  data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port);
    void writeTo(uint16_t  data_id, int data_count,  const int32_t  data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port);
  
    struct rovecomm_packet read();
  
  private:
	void _write  (uint16_t  data_id, data_type data_type, uint8_t data_type_length, uint8_t data_count, void* data);
	void _writeTo(uint16_t  data_id, data_type data_type, uint8_t data_type_length, uint8_t data_count, void* data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port);
};

#endif // RoveEthernetUdp_h