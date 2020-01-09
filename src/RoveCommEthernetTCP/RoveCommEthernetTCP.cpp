#include "RoveCommEthernetTCP.h"
#include "RoveCommPacket.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include          <SPI.h>         // Energia/master/hardware/lm4f/libraries/SPI
#include          <Energia.h>
#include          <Ethernet.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RoveCommEthernetTCP::RoveCommEthernetTCP()
{
    return;
}

void RoveCommEthernetTCP::begin(uint8_t server_ip_octet, const int port)
{
  byte server_ip[4] = {192, 168, 1, server_ip_octet};
  this->begin(server_ip, port);
}

void RoveCommEthernetTCP::begin(byte server_ip[4], const int port)
{ 
  //Set IP
  Ethernet.enableActivityLed();
  Ethernet.enableLinkLed(); 

  //Set up Ethernet
  Ethernet.begin(   0, server_ip);

  TCPServer = new RoveCommEthernetTCPServer();

  TCPServer->begin(port);
}

/////////////////////////////////////////////////////////////////////////////////
struct rovecomm_packet RoveCommEthernetTCP::read() 
{ 	
  //return the packet
  return TCPServer->read();
}

RoveCommEthernetTCPClient* RoveCommEthernetTCP::connect(byte dest_ip[4], const int port)
{
    RoveCommEthernetTCPClient* client;
    client->begin(dest_ip, port);
    return client;
}

//Overloaded writeReliable////////////////////////////////////////////////////////////////////////////////////////////////////
//Single-value write
//handles the data->pointer conversion for user
void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int32_t data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint32_t data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int16_t data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint16_t data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(         const uint16_t data_id, const uint8_t data_count, const   int8_t data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  uint8_t data )
{                  TCPServer->writeReliable(data_id, data_count, data); }
//Array-Entry write///////////////////////////////////
void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int32_t *data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint32_t *data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int16_t *data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint16_t *data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(         const uint16_t data_id, const uint8_t data_count, const   int8_t *data )
{                  TCPServer->writeReliable(data_id, data_count, data); }

void RoveCommEthernetTCP::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  uint8_t *data )
{                  TCPServer->writeReliable(data_id, data_count, data); }
