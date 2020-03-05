#include <SPI.h>
#include <Ethernet.h>
#include "RoveComm.h"
//the IP address for this board:
IPAddress ip(192, 168, 1, 135);

// Rovecomm standard of port 11000
EthernetServer TServer = EthernetServer(11006);
RoveCommEthernet RoveComm;
rovecomm_packet packet; 

void setup()
{
    // initialize the ethernet device
    Serial.begin(9600);
    RoveComm.begin(135, &TServer);
    delay(1000);

}

void loop()
{
  packet = RoveComm.read();

  Serial.println(packet.data_id);
  RoveComm.writeReliable(9600, 1, (uint8_t)2);
  delay(1000);
} 
