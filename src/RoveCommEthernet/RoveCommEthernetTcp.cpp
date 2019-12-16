#include "RoveCommEthernetTcp.h"
#include "RoveCommPacket.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include          <SPI.h>         // Energia/master/hardware/lm4f/libraries/SPI
#include          <Energia.h>
#include          <Ethernet.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetTcp::begin(uint8_t server_ip_octet, const int port)
{
  byte server_ip[4] = {192, 168, 1, server_ip_octet};
  this->begin(server_ip, port);
}

void RoveCommEthernetTcp::begin(byte server_ip[4], const int port)
{ 
  //Set IP
  Ethernet.enableActivityLed();
  Ethernet.enableLinkLed(); 

  //Set up Ethernet
  Ethernet.begin(   0, server_ip);

  //Set up server with correct port, and start listening for clients
  Server = EthernetServer(port);
  Server.begin();

  //grab available client
  EthernetClient Client = Server.available();

  //flush the buffers for the available client
  if (Client == true)
    {
    Client.flush();
    }

  delay(1);
}

/////////////////////////////////////////////////////////////////////////////////
struct rovecomm_packet RoveCommEthernetTcp::read() 
{ 

  //Create new RoveCommPacket
  struct rovecomm_packet rovecomm_packet = { 0 };

  //individual components of header
  uint16_t data_id    =  0;
  roveware::data_type_t data_type;
  uint8_t data_count =  0;

  //check if there is a message from client
  EthernetClient Client = Server.available();

  //if there is a message from the client, parse it
  if(Client == true)
    {
    //array of bytes that represent the max size of packet
    uint8_t packet[ROVECOMM_PACKET_HEADER_SIZE + sizeof(int) * ROVECOMM_PACKET_MAX_DATA_COUNT];
    
    //read in the packet while there is data available
    uint8_t last_byte = Client.read();
    for(uint8_t i = 0; last_byte != -1 && i < (ROVECOMM_PACKET_HEADER_SIZE + sizeof(int) * ROVECOMM_PACKET_MAX_DATA_COUNT); i++)
      {
      packet[i] = last_byte;
      last_byte = Client.read();
      }

    rovecomm_packet = roveware::unpackPacket(packet); 
    }
  //if there is no message, just return that there is no data to read
  else
    {
    rovecomm_packet.data_id = ROVECOMM_NO_DATA_DATA_ID;
    rovecomm_packet.data_count = 1;
    rovecomm_packet.data[1] = {0};
    }
  
	
  //return the packet
  return rovecomm_packet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommEthernetUdp::_writeReliable(const uint8_t data_type_length, const roveware::data_type_t data_type, const uint16_t data_id, const uint8_t data_count, const void* data)
{ 
  //Creat packed udp packet
  struct roveware::_packet _packet = roveware::packPacket(data_id, data_count, data_type, data);
  
  //write to all available clients
  server.write( _packet.bytes, (ROVECOMM_PACKET_HEADER_SIZE + (data_type_length * data_count))); 
}

//Overloaded writeReliable////////////////////////////////////////////////////////////////////////////////////////////////////
//Single-value write
//handles the data->pointer conversion for user
void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int32_t data )
{                  int32_t data_p[1];
                   data_p[0] = data;
                   this->_writeReliable( 4,  roveware::INT32_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint32_t data )
{                  uint32_t data_p[1];
                   data_p[0] = data;
                   this->_writeReliable( 4, roveware::UINT32_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int16_t data )
{                  int16_t data_p[1];
                   data_p[0] = data;
                   this->_writeReliable( 2,  roveware::INT16_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint16_t data )
{                  uint16_t data_p[1];
                   data_p[0] = data;
                   this->_writeReliable( 2, roveware::UINT16_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommEthernetUdp::writeReliable(         const uint16_t data_id, const uint8_t data_count, const   int8_t data )
{                  int8_t data_p[1];
                   data_p[0] = data;
                   this->_writeReliable( 1,   roveware::INT8_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  uint8_t data )
{                  uint8_t data_p[1];
                   data_p[0] = data;
                   this->_writeReliable( 1,  roveware::UINT8_T, data_id,               data_count,        (void*) data_p ); }
//Array-Entry write///////////////////////////////////
//void RoveCommEthernetUdp::write(        const  int      data_id, const  int    data_count, const  int     *data ) 
//{                  this->_write( 4,  roveware::INT32_T, data_id,               data_count,        (void*) data ); }
//
void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int32_t *data )
{                  this->_writeReliable( 4,  roveware::INT32_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint32_t *data )
{                  this->_writeReliable( 4, roveware::UINT32_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  int16_t *data )
{                  this->_writeReliable( 2,  roveware::INT16_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const uint16_t *data )
{                  this->_writeReliable( 2, roveware::UINT16_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::writeReliable(         const uint16_t data_id, const uint8_t data_count, const   int8_t *data )
{                  this->_writeReliable( 1,   roveware::INT8_T, data_id,               data_count,        (void*) data ); }

void RoveCommEthernetUdp::writeReliable(        const uint16_t  data_id, const uint8_t data_count, const  uint8_t *data )
{                  this->_writeReliable( 1,  roveware::UINT8_T, data_id,               data_count,        (void*) data ); }