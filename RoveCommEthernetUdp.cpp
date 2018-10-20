#include "RoveCommEthernetUdp.h"
#include "RoveCommPacket.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include          <SPI.h>         // Energia/master/hardware/lm4f/libraries/SPI
#include          <Energia.h>
#include          <Ethernet.h>
#include          <EthernetUdp.h> // EthernetClass Ethernet; => Energia alloc instance on Ethernet.cpp
EthernetUDP        EthernetUdp; 
IPAddress RoveComm_EthernetUdpSubscriberIps[ROVECOMM_ETHERNET_UDP_MAX_SUBSCRIBERS] = { INADDR_NONE };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetUdp::begin(const int board_ip_octet) 
{
  this->begin(ROVECOMM_SUBNET_IP_FIRST_OCTET, ROVECOMM_SUBNET_IP_SECOND_OCTET, ROVECOMM_SUBNET_IP_THIRD_OCTET, (uint8_t)board_ip_octet);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoveCommEthernetUdp::begin(const uint8_t ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4)
{ 
  IPAddress LocalIp(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);

  Ethernet.enableActivityLed();
  Ethernet.enableLinkLed(); 
  Ethernet.begin(   0, LocalIp);
  EthernetUdp.begin(ROVECOMM_ETHERNET_UDP_PORT); 
  delay(1);
}

/////////////////////////////////////////////////////////////////////////////////
struct rovecomm_packet RoveCommEthernetUdp::read() 
{ 
  struct rovecomm_packet rovecomm_packet = { 0 };

               uint16_t data_id    =  0;
  roveware::data_type_t data_type;
                uint8_t data_count =  0;
   
  int packet_size = EthernetUdp.parsePacket();
  if (packet_size > 0)
  {       
    uint8_t udp_packet[ packet_size];

    EthernetUdp.read(udp_packet, packet_size);
    IPAddress ReadFromIp = EthernetUdp.remoteIP();

    rovecomm_packet = roveware::unpackUdpPacket(udp_packet); 
    
    if (rovecomm_packet.data_id == ROVECOMM_SUBSCRIBE_REQUEST_DATA_ID)
    {
      for (int i=0; i < ROVECOMM_ETHERNET_UDP_MAX_SUBSCRIBERS; i++) 
      {
        if (RoveComm_EthernetUdpSubscriberIps[i] == ReadFromIp) 
        {
          break;                                              // already subscribed
        } else if (RoveComm_EthernetUdpSubscriberIps[i] == INADDR_NONE) 
        {
          RoveComm_EthernetUdpSubscriberIps[i]  = ReadFromIp; // add subscriber
          break;
        }
      }
        
    } else if (rovecomm_packet.data_id == ROVECOMM_UNSUBSCRIBE_REQUEST_DATA_ID)
    {
      for (int i=0; i < ROVECOMM_ETHERNET_UDP_MAX_SUBSCRIBERS; i++)
      {
        if (RoveComm_EthernetUdpSubscriberIps[i] == ReadFromIp)
        {
          RoveComm_EthernetUdpSubscriberIps[i]  = INADDR_NONE; // remove subscriber
        }
      }
    }  
  }
  return rovecomm_packet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetUdp::_write(const uint8_t data_type_length, const roveware::data_type_t data_type, const uint16_t data_id, const uint8_t data_count, const void* data)
{ 
  struct roveware::udp_packet udp_packet = roveware::packUdpPacket(data_id, data_count, data_type, data);
  
  for (int i=0; i < ROVECOMM_ETHERNET_UDP_MAX_SUBSCRIBERS; i++)
  {
    if (RoveComm_EthernetUdpSubscriberIps[i] != INADDR_NONE)
    {       
      EthernetUdp.beginPacket(RoveComm_EthernetUdpSubscriberIps[i], ROVECOMM_ETHERNET_UDP_PORT);
      EthernetUdp.write(      udp_packet.bytes, (ROVECOMM_ETHERNET_UDP_PACKET_HEADER_SIZE + (data_type_length * data_count)));
      EthernetUdp.endPacket();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetUdp::_writeTo(const uint8_t data_type_length, const roveware::data_type_t data_type, const uint16_t data_id, const uint8_t data_count, const void* data,
                                   const uint8_t ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port) 
{ 
  struct roveware::udp_packet udp_packet = roveware::packUdpPacket(data_id, data_count, data_type, data);
  
  IPAddress WriteToIp(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);

  EthernetUdp.beginPacket(WriteToIp, port);
  EthernetUdp.write(      udp_packet.bytes, (ROVECOMM_ETHERNET_UDP_PACKET_HEADER_SIZE + (data_type_length * data_count)));
  EthernetUdp.endPacket(); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetUdp::write(        const  int      data_id, const  int    data_count, const  int     data )
{                  this->_write( 4,  roveware::INT32_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::write(        const uint16_t  data_id, const uint8_t data_count, const  int32_t data )
{                  this->_write( 4,  roveware::INT32_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::write(        const uint16_t  data_id, const uint8_t data_count, const uint32_t data )
{                  this->_write( 4, roveware::UINT32_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::write(        const uint16_t  data_id, const uint8_t data_count, const  int16_t data )
{                  this->_write( 2,  roveware::INT16_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::write(        const uint16_t  data_id, const uint8_t data_count, const uint16_t data )
{                  this->_write( 2, roveware::UINT16_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::write(         const uint16_t data_id, const uint8_t data_count, const   int8_t data )
{                  this->_write( 1,   roveware::INT8_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::write(        const uint16_t  data_id, const uint8_t data_count, const  uint8_t data )
{                  this->_write( 1,  roveware::UINT8_T, data_id,               data_count,        (void*) data ); }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetUdp::writeTo(         const uint16_t data_id,    const uint8_t data_count, const int32_t data,
                                           const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port )
{                  this->_writeTo( 4,  roveware::INT32_T, data_id,                  data_count,       (void*) data,
                                                          ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4, port ); }

void RoveCommEthernetUdp::writeTo(         const uint16_t data_id,    const uint8_t data_count, const uint32_t data,
                                           const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t  ip_octet_3, const uint8_t ip_octet_4, const uint16_t port )
{                  this->_writeTo( 4, roveware::UINT32_T, data_id,                  data_count,        (void*) data,
                                                          ip_octet_1, ip_octet_2,   ip_octet_3,ip_octet_4, port ); }

void RoveCommEthernetUdp::writeTo(         const uint16_t data_id,    const uint8_t data_count, const int16_t data,
                                           const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port )
{                  this->_writeTo( 2,  roveware::INT16_T, data_id,                 data_count,        (void*) data,
                                                          ip_octet_1, ip_octet_2,  ip_octet_3,  ip_octet_4,   port ); }

void RoveCommEthernetUdp::writeTo(         const uint16_t data_id,    const uint8_t data_count, const uint16_t data,
                                           const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t  ip_octet_3, const uint8_t ip_octet_4, const uint16_t port )
{                  this->_writeTo( 2, roveware::UINT16_T, data_id,                  data_count,        (void*) data,
                                                          ip_octet_1, ip_octet_2,   ip_octet_3, ip_octet_4,    port ); }

void RoveCommEthernetUdp::writeTo(         const uint16_t data_id,    const uint8_t data_count, const int8_t  data, 
                                           const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port )
{                  this->_writeTo( 1,  roveware::INT8_T,  data_id,                  data_count,       (void*) data, 
                                                          ip_octet_1, ip_octet_2,   ip_octet_3, ip_octet_4,   port ); }

void RoveCommEthernetUdp::writeTo(         const uint16_t data_id,    const uint8_t data_count, const uint8_t data,
                                           const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const uint16_t port )
{                  this->_writeTo( 1,  roveware::UINT8_T, data_id,                  data_count,       (void*) data,
                                                          ip_octet_1, ip_octet_2,   ip_octet_3, ip_octet_4,   port ); }