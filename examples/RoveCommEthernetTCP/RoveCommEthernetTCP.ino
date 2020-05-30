#include <SPI.h>
#include <Ethernet.h>
#include "RoveComm.h"
//the IP address for this board:
IPAddress ip(192, 168, 1, 135);


//rovecomm and packet instances
RoveCommEthernet RoveComm;
rovecomm_packet packet; 

void setup()
{
    // initialize the ethernet device
    Serial.begin(9600);
    RoveComm.begin(135, 11006);
    delay(1000);

}

void loop()
{
  packet = RoveComm.read();
  Serial.println(packet.data_id);
  if(packet.data_id != ROVECOMM_NO_DATA_DATA_ID)
  {
      //cast the data to the expected data type
      uint16_t* data = (uint16_t*)packet.data;
      
      //now print out all of the data
      for(int i = 0; i < packet.data_count; i++)
      {
        Serial.println(data[i]);
      }
  }
  //write some sample data back
  RoveComm.writeReliable(9600, 1, (uint8_t)2);
  delay(1000);
} 