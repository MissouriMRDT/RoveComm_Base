#ifndef ROVECOMM_PACKET_H
#define ROVECOMM_PACKET_H

#include <stdint.h>
#include <stddef.h>

//////////////////////////////////////////////////////
#define ROVECOMM_ETHERNET_UDP_MAX_SUBSCRIBERS      10
#define ROVECOMM_ETHERNET_UDP_MAX_DATA_COUNT      255
#define ROVECOMM_ETHERNET_UDP_PACKET_HEADER_SIZE    4

//////////////////////////////////////////////////////
struct rovecomm_packet
{
  uint16_t data_id;
   uint8_t data_count;
       int data[ROVECOMM_ETHERNET_UDP_MAX_DATA_COUNT];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace roveware
{
  enum data_type_t { INT8_T, UINT8_T, INT16_T, UINT16_T, INT32_T, UINT32_T };

  ////////////////////////////////////////////////
  // The RoveComm udp packet header is 4 bytes long:
  // uint16_t data_id   
  // uint8_t  data_type
  // uint8_t  data_count

  struct udp_packet
  {
    uint8_t bytes[ROVECOMM_ETHERNET_UDP_PACKET_HEADER_SIZE + sizeof(int) * ROVECOMM_ETHERNET_UDP_MAX_DATA_COUNT];
  };

  struct udp_packet        packUdpPacket(const uint16_t data_id, const uint8_t data_count, const data_type_t data_type, const void* data);
  struct rovecomm_packet unpackUdpPacket(const uint8_t  udp_packet[]);
}// end namespace/////////////////////////////////////////////////////////////////////////////////////////////////

#endif // ROVECOMM_PACKET_H