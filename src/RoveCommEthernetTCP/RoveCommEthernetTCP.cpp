#include "RoveCommEthernetTCP.h"
#include "RoveCommPacket.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include          <SPI.h>         // Energia/master/hardware/lm4f/libraries/SPI
#include          <Energia.h>
#include          <Ethernet.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetTCP::begin(uint8_t server_ip_octet, const int port)
{
  TCPServer.begin(server_ip_octet, port);
}

void RoveCommEthernetTCP::begin(const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const int port)
{ 
  byte server_ip[4] = {ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4};
  TCPServer.begin(server_ip, port);
}

/////////////////////////////////////////////////////////////////////////////////
struct rovecomm_packet RoveCommEthernetTCP::read() 
{ 	
  return TCPServer.read();
}

/////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetTCP::connect(const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4, const int port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      return;
    }
  }
  Clients[num_clients].dest_ip = dest_ip;
  Clients[num_clients].client.begin(dest_ip, port);
  num_clients++;
  return;
}

/////////////////////////////////////////////////////////////////////////////////
bool RoveCommEthernetTCP::connected(const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      return Clients[i].client.connected();
    }
  }
  return false;
}

//Overloaded writeReliable////////////////////////////////////////////////////////////////////////////////////////////////////
//Single-value write
//handles the data->pointer conversion for user
void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int32_t data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint32_t data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int16_t data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint16_t data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(         const uint16_t data_id, const uint8_t data_count, const   int8_t data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  uint8_t data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  float   data )
{                  TCPServer.writeReliable(data_id, data_count, data); }
//Array-Entry write///////////////////////////////////
void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int32_t *data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint32_t *data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int16_t *data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint16_t *data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(         const uint16_t data_id, const uint8_t data_count, const   int8_t *data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  uint8_t *data )
{                  TCPServer.writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  float   *data )
{                  TCPServer.writeReliable(data_id, data_count, data); }
//Overloaded writeReliableTo////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetTCP::writeReliableTo(    const uint16_t data_id,    const uint8_t data_count, const uint8_t  data,
                                              const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{ 
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(    const uint16_t data_id,    const uint8_t data_count, const uint16_t data,
                                              const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(    const uint16_t data_id,    const uint8_t data_count, const uint32_t data,
                                              const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(    const uint16_t data_id,    const uint8_t data_count, const int8_t   data,
                                              const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(    const uint16_t data_id,    const uint8_t data_count, const int16_t  data,
                                              const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(    const uint16_t data_id,    const uint8_t data_count, const int32_t  data,
                                              const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(    const uint16_t data_id,    const uint8_t data_count, const float  data,
                                              const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};
//Array-Entry write///////////////////////////////////
void RoveCommEthernetTCP::writeReliableTo(   const uint16_t data_id,    const int     data_count, const int      *data,
                        const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(   const uint16_t data_id,    const uint8_t data_count, const uint8_t  *data,
                        const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(   const uint16_t data_id,    const uint8_t data_count, const uint16_t *data,
                        const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(   const uint16_t data_id,    const uint8_t data_count, const uint32_t *data,
                        const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(   const uint16_t data_id,    const uint8_t data_count, const int8_t   *data,
                        const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(   const uint16_t data_id,    const uint8_t data_count, const int16_t  *data,
                        const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(   const uint16_t data_id,    const uint8_t data_count, const int32_t  *data,
                        const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};

void RoveCommEthernetTCP::writeReliableTo(   const uint16_t data_id,    const uint8_t data_count, const float  *data,
                        const uint8_t  ip_octet_1, const uint8_t ip_octet_2, const uint8_t ip_octet_3, const uint8_t ip_octet_4,  const uint16_t port)
{
  IPAddress dest_ip(ip_octet_1, ip_octet_2, ip_octet_3, ip_octet_4);
  for(int i = 0; i < num_clients; i++)
  {
    if(Clients[i].dest_ip == dest_ip)
    {
      Clients[i].client.writeReliable(data_id, data_count, data);
    }
  }
};
