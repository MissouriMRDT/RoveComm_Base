#ifndef RoveEthernetUdp_h
#define RoveEthernetUdp_h

#include <stdint.h>
#include <stddef.h>

#include "RoveCommManifest.h"
#include "RoveCommPacket.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RoveCommEthernetUdp
{
  public:
    void begin(const int board_ip_octet);
    struct rovecomm_packet read();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void begin  (const uint8_t ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4);

    void write  (const int      data_id, const int     data_count, const int      data);
    void write  (const uint16_t data_id, const uint8_t data_count, const uint8_t  data);
    void write  (const uint16_t data_id, const uint8_t data_count, const uint16_t data);
    void write  (const uint16_t data_id, const uint8_t data_count, const uint32_t data);
    void write  (const uint16_t data_id, const uint8_t data_count, const int8_t   data);
    void write  (const uint16_t data_id, const uint8_t data_count, const int16_t  data);
    void write  (const uint16_t data_id, const uint8_t data_count, const int32_t  data);


    void write  (const int      data_id, const int     data_count, const int      *data);
    void write  (const uint16_t data_id, const uint8_t data_count, const uint8_t  *data);
    void write  (const uint16_t data_id, const uint8_t data_count, const uint16_t *data);
    void write  (const uint16_t data_id, const uint8_t data_count, const uint32_t *data);
    void write  (const uint16_t data_id, const uint8_t data_count, const int8_t   *data);
    void write  (const uint16_t data_id, const uint8_t data_count, const int16_t  *data);
    void write  (const uint16_t data_id, const uint8_t data_count, const int32_t  *data);


    void writeTo(const uint16_t data_id,    const uint8_t data_count, const int  data,
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const uint8_t  data,
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const uint16_t data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const uint32_t data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const int8_t   data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const int16_t  data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const int32_t  data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);


    void writeTo(const uint16_t data_id,    const uint8_t data_count, const int  *data,
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const uint8_t  *data,
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const uint16_t *data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const uint32_t *data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const int8_t   *data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const int16_t  *data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);

    void writeTo(const uint16_t data_id,    const uint8_t data_count, const int32_t  *data, 
                 const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);
  
  private:
    void _write(  const uint8_t  data_type_length, const roveware::data_type_t data_type, 
                  const uint16_t data_id,    const uint8_t data_count, const void* data);

    void _writeTo(const uint8_t  data_type_length, const roveware::data_type_t data_type,
                  const uint16_t data_id,    const uint8_t data_count, const void* data,
                  const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port);
};

#endif // RoveEthernetUdp_h