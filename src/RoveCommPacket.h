#ifndef ROVECOMM_PACKET_H
#define ROVECOMM_PACKET_H

#include <stdint.h>
#include <stddef.h>
#include "RoveCommManifest.h"

#if defined(ENERGIA)
#include <Ethernet.h>
#elif defined(ARDUINO) && (ARDUINO>100)
#include <NativeEthernet.h>
#endif

//////////////////////////////////////////////////////
#define ROVECOMM_ETHERNET_UDP_MAX_SUBSCRIBERS      10
#define ROVECOMM_PACKET_MAX_DATA_COUNT        65535
#define ROVECOMM_PACKET_HEADER_SIZE    6
#define ROVECOMM_VERSION    25

//////////////////////////////////////////////////////
//Carrys RoveComm packet data
//Used to return RoveComm::read() values as a struct
struct rovecomm_packet
{
  uint16_t data_id;
  uint16_t data_count;
  uint8_t data_type;
  #if defined(ENERGIA)
  char data[ROVECOMM_PACKET_MAX_DATA_COUNT/3*sizeof(uint8_t)]; //Tiva can only support 21,000 uint8_t at once due to memory issues
  #elif defined(ARDUINO) && (ARDUINO>100)
  char data[ROVECOMM_PACKET_MAX_DATA_COUNT/2*sizeof(uint8_t)];  //Teensy can only support 32,000 uint8_t at once due to memory issues
  #endif
};  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace roveware
{
  //DataType RoveComm encoding
  enum data_type_t { INT8_T=0, UINT8_T=1, INT16_T=2, UINT16_T=3, INT32_T=4, UINT32_T=5, FLOAT=6, DOUBLE=7, CHAR=8};

  ////////////////////////////////////////////////
  // The RoveComm udp packet header is 6 bytes long:
  // uint8_t  rovecomm_version
  // uint16_t data_id   
  // uint16_t  data_count
  // uint8_t  data_type

  //Carrys Udp packet data
  struct _packet
  {
    #if defined(ENERGIA)
    uint8_t bytes[ROVECOMM_PACKET_HEADER_SIZE + sizeof(uint8_t) * ROVECOMM_PACKET_MAX_DATA_COUNT/3];  //Tiva can only support 21,000 uint8_t at once due to memory issues
    #elif defined(ARDUINO) && (ARDUINO>100)
    uint8_t bytes[ROVECOMM_PACKET_HEADER_SIZE + sizeof(uint8_t) * ROVECOMM_PACKET_MAX_DATA_COUNT/2];  //Teensy can only support 32,000 uint8_t at once due to memory issues
    #endif
  };

  struct _packet        packPacket(const uint16_t data_id, const uint16_t data_count, const data_type_t data_type, const void* data);

  //for UDP packets, of known size
  struct rovecomm_packet unpackPacket(uint8_t  _packet[]);
  //for TCP, where we read streams of data, with size determined by parsing header
  struct rovecomm_packet unpackPacket(EthernetClient client);

}// end namespace/////////////////////////////////////////////////////////////////////////////////////////////////

#endif // ROVECOMM_PACKET_H