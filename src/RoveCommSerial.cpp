#include "RoveCommSerial.h"
#include "RoveCommPacket.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include          <SPI.h>         // Energia/master/hardware/lm4f/libraries/SPI
#include          <Energia.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommSerial::begin(HardwareSerial &S_Tx, HardwareSerial &S_Rx, int baud)
{
  _Ser_Tx = S_Tx;
  _Ser_Rx = S_Rx;

  _Ser_Tx.begin(baud);
  _Ser_Rx.begin(baud);
  
  delay(10);
}


/////////////////////////////////////////////////////////////////////////////////
struct rovecomm_packet RoveCommSerial::read() 
{ 
  //Create new RoveCommPacket
  Serial.println("In read");
  struct rovecomm_packet rovecomm_packet = { 0 };
  if(_Ser_Rx.available())
  {    
    Serial.println("I'm in");
    //Todo: Why don't we pass these directly into the rovecomm_packet we just made?
    uint16_t data_id    =  0;
    roveware::data_type_t data_type;
    uint8_t data_count =  0;
          
	//Create array to take packet
    uint8_t _packet[255];
    
	//Read packet
	int i = 0;
	while(_Ser_Rx.available())
	{
	  _packet[i] = _Ser_Rx.read();
	  Serial.println(_packet[i]);
	  i++;
	}
    
	//Unpack RoveComm Packet
    rovecomm_packet = roveware::unpackUdpPacket(_packet); 
	//return the packet
	return rovecomm_packet;
  }
  Serial.println("Ser Not Avail");
  return rovecomm_packet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoveCommSerial::_write(const uint8_t data_type_length, const roveware::data_type_t data_type, const uint16_t data_id, const uint8_t data_count, const void* data)
{ 
  //Creat packed udp packet
  struct roveware::_packet _packet = roveware::packUdpPacket(data_id, data_count, data_type, data);
  
  int packet_length = ROVECOMM_PACKET_HEADER_SIZE + data_type_length * data_count;
  _Ser_Tx.write(_packet.bytes, packet_length);
}

//Overloaded write////////////////////////////////////////////////////////////////////////////////////////////////////
//Single-value write
//handles the data->pointer conversion for user
//void RoveCommSerial::write(        const  uint16_t      data_id, const  int    data_count, const  int     data ) 
//{                  int data_p[1];
//                   data_p[0] = data;
//                   this->_write( 4,  roveware::INT32_T, data_id,               data_count,        (void*) data_p ); }
//
void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const  int32_t data )
{                  int32_t data_p[1];
                   data_p[0] = data;
                   this->_write( 4,  roveware::INT32_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const uint32_t data )
{                  uint32_t data_p[1];
                   data_p[0] = data;
                   this->_write( 4, roveware::UINT32_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const  int16_t data )
{                  int16_t data_p[1];
                   data_p[0] = data;
                   this->_write( 2,  roveware::INT16_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const uint16_t data )
{                  uint16_t data_p[1];
                   data_p[0] = data;
                   this->_write( 2, roveware::UINT16_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommSerial::write(         const uint16_t data_id, const uint8_t data_count, const   int8_t data )
{                  int8_t data_p[1];
                   data_p[0] = data;
                   this->_write( 1,   roveware::INT8_T, data_id,               data_count,        (void*) data_p ); }

void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const  uint8_t data )
{                  uint8_t data_p[1];
                   data_p[0] = data;
                   this->_write( 1,  roveware::UINT8_T, data_id,               data_count,        (void*) data_p ); }
//Array-Entry write///////////////////////////////////
//void RoveCommSerial::write(        const  int      data_id, const  int    data_count, const  int     *data ) 
//{                  this->_write( 4,  roveware::INT32_T, data_id,               data_count,        (void*) data ); }
//
void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const  int32_t *data )
{                  this->_write( 4,  roveware::INT32_T, data_id,               data_count,        (void*) data ); }

void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const uint32_t *data )
{                  this->_write( 4, roveware::UINT32_T, data_id,               data_count,        (void*) data ); }

void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const  int16_t *data )
{                  this->_write( 2,  roveware::INT16_T, data_id,               data_count,        (void*) data ); }

void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const uint16_t *data )
{                  this->_write( 2, roveware::UINT16_T, data_id,               data_count,        (void*) data ); }

void RoveCommSerial::write(         const uint16_t data_id, const uint8_t data_count, const   int8_t *data )
{                  this->_write( 1,   roveware::INT8_T, data_id,               data_count,        (void*) data ); }

void RoveCommSerial::write(        const uint16_t  data_id, const uint8_t data_count, const  uint8_t *data )
{                  this->_write( 1,  roveware::UINT8_T, data_id,               data_count,        (void*) data ); }