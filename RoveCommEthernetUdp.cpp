 /*
  RoveCommEthernetUdp.h - Library for Wiring + Processing IDE's (Energia/Arduino) 
  
  Copyright (c) 2018 Missouri S&T Mars Rover Design Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "RoveCommEthernetUdp.h"
#include "RoveCommProtocol.h"

////////////////////////////////////////////////////////////////////////////
// If => Texas Instruments Ethernet (Tiva C 129)
//
// Board Manager installs to => C:\Users\<YourUser>\AppData\Local\Energia15
//
// #include <Energia.h>
// #include <SPI.h>
// #include <Ethernet.h>    
// #include <EthernetUdp.h>

#include <Energia.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h> // EthernetClass Ethernet; => instance already in Ethernet.cpp

EthernetUDP EthernetUdp; 

const IPAddress NULL_IP(0, 0, 0, 0);

IPAddress RoveCommEthernetUdpSubscribers[ROVECOMM_ETHERNET_UDP_SUBSCRIBERS] = {NULL_IP};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// todo   
// todo 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoveCommEthernetUdp::begin(uint8_t ip_octet_1, uint8_t ip_octet_2, uint8_t ip_octet_3, uint8_t ip_octet_4) 
{ 
  IPAddress LocalIp(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);

  Ethernet.enableActivityLed();
  Ethernet.enableLinkLed(); 
  
  Ethernet.begin(0, LocalIp);    
  EthernetUdp.begin(ROVECOMM_ETHERNET_UDP_PORT); 
  delay(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveComm::write(uint16_t  data_id, int data_count,  const uint8_t   data){_write(data_id, UINT8_T,  1,  (uint8_t) data_count, (void*) data)}
void RoveComm::write(uint16_t  data_id, int data_count,  const int8_t    data){_write(data_id, INT8_T,   1,  (uint8_t) data_count, (void*) data)}
void RoveComm::write(uint16_t  data_id, int data_count,  const uint16_t  data){_write(data_id, UINT16_T, 2, (uint8_t) data_count, (void*) data)}
void RoveComm::write(uint16_t  data_id, int data_count,  const int16_t   data){_write(data_id, INT16_T,  2, (uint8_t) data_count, (void*) data)}
void RoveComm::write(uint16_t  data_id, int data_count,  const uint32_t  data){_write(data_id, UINT32_T, 4, (uint8_t) data_count, (void*) data)}
void RoveComm::write(uint16_t  data_id, int data_count,  const int32_t   data){_write(data_id, INT32_T,  4, (uint8_t) data_count, (void*) data)}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveComm::writeTo(uint16_t  data_id, int data_count,  const uint8_t   data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)
{_writeTo(data_id, UINT8_T, 1,  (uint8_t) data_count, (void*) data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)}

void RoveComm::writeTo(uint16_t  data_id, int data_count,  const int8_t    data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)
{_writeTo(data_id, INT8_T,  1,  (uint8_t) data_count, (void*) data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)}

void RoveComm::writeTo(uint16_t  data_id, int data_count,  const uint16_t  data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)
{_writeTo(data_id, UINT16_T, 2, (uint8_t) data_count, (void*) data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)}

void RoveComm::writeTo(uint16_t  data_id, int data_count,  const int16_t   data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)
{_writeTo(data_id, INT16_T, 2,  (uint8_t) data_count, (void*) data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)}

void RoveComm::writeTo(uint16_t  data_id, int data_count,  const uint32_t  data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)
{_writeTo(data_id, UINT32_T, 4, (uint8_t) data_count, (void*) data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)}

void RoveComm::writeTo(uint16_t  data_id, int data_count,  const int32_t   data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)
{_writeTo(data_id, INT32_T, 4,  (uint8_t) data_count, (void*) data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port)}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetUdp::_write(uint16_t  data_id, data_type  data_type, uint8_t data_type_length, uint8_t data_count, const void* data) 
{ 
  uint8_t udp_packet[] = RoveWare::packUdpPacket(data_id, data_type, data_count, data);
  
  size_t data_size = data_type_length * data_count;
  
  int  i;
  for (i=0; i < ROVECOMM_ETHERNET_UDP_SUBSCRIBERS; i++) 
  {
    if (!(RoveCommEthernetUdpSubscribers[i] == NULL_IP)) 
    {       
      EthernetUdp.beginPacket(RoveCommEthernetUdpSubscribers[i], ROVECOMM_ETHERNET_UDP_PORT);
      EthernetUdp.write(udp_packet, ROVECOMM_PACKET_HEADER_SIZE + data_size);
      EthernetUdp.endPacket();
    }
  }   
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetUdp::writeTo(uint16_t  data_id, data_type  data_type, uint8_t data_type_length, uint8_t data_count,  const void* data, uint8_t  ip_octet_1, uint8_t  ip_octet_2, uint8_t  ip_octet_3, uint8_t  ip_octet_4, uint16_t port) 
{ 
  uint8_t udp_packet[] = RoveWare::packUdpPacket(data_id, data_type, data_count, data);
  
  size_t data_size = data_type_length * data_count;
  
  IPAddress RemoteIp(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4); 
  
  EthernetUdp.beginPacket(RemoteIp, port);
  EthernetUdp.write(udp_packet, ROVECOMM_PACKET_HEADER_SIZE + data_size);
  EthernetUdp.endPacket(); 
}

//////////////////////////////////////////////////
struct rovecomm_packet RoveCommEthernetUdp::read() 
{ 
  uint16_t data_id   = 0; 
  data_type data_type;
  uint8_t data_count = 0;
   
  int packet_size = EthernetUdp.parsePacket();  
  if (packet_size > 0)
  {       
    uint8_t udp_packet[packet_size];    
    EthernetUdp.read(udp_packet, packet_size);     
    IPAddress RemoteIp = EthernetUdp.remoteIP();
    
    struct rovecomm_packet rovecomm_packet = RoveWare::unpackPacket(udp_packet); 
    
    if  (rovecomm_packet.data_id == ROVECOMM_SUBSCRIBE_REQUEST)
    {
      int  i;
      for (i=0; i < ROVECOMM_ETHERNET_UDP_SUBSCRIBERS; i++) 
      {
        if (RoveCommEthernetUdpSubscribers[i] == RemoteIp) 
        {
          break; // already subscribed         
        } else if (RoveCommEthernetUdpSubscribers[i] == NULL_IP) 
        {
          RoveCommEthernetUdpSubscribers[i] = RemoteIp; // add subscriber
          break;
        }
      }
        
    } else if (rovecomm_packet.data_id == ROVECOMM_UNSUBSCRIBE_REQUEST) 
    {
      int  i;
      for (i=0; i < ROVECOMM_ETHERNET_UDP_SUBSCRIBERS; i++) 
      {
        if (RoveCommEthernetUdpSubscribers[i] == RemoteIp) 
        {
          RoveCommEthernetUdpSubscribers[i] = NULL_IP; // remove subscriber
          break;        
        }
      }
    } 
  }
  return rovecomm_packet;
  //ToDo: Packup and return struct
}
