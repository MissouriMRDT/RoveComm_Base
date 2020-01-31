#include "RoveCommEthernet.h"
#include "RoveCommPacket.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
#include          <SPI.h>         // Energia/master/hardware/lm4f/libraries/SPI
#include          <Energia.h>
#include          <Ethernet.h>

/////////////////////////////////////////////////////////////////////////////////
struct rovecomm_packet RoveCommEthernet::read() 
{ 
  //check for any incoming UDP packets
  rovecomm_packet = UDP.read();
  if(rovecomm_packet.data_id != 0)
  {
    return rovecomm_packet;
  }
  //check for any incoming TCP packets
  rovecomm_packet = TCPServer.read();
  if(rovecomm_packet.data_id != 0)
  {
    return rovecomm_packet;
  }

  //otherwise just return no data
  rovecomm_packet.data_id = ROVECOMM_NO_DATA_DATA_ID;
  rovecomm_packet.data_count = 0;
  return rovecomm_packet;
}