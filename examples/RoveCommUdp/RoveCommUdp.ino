#include "RoveComm.h"


//byte dest_ip[] = { 192, 168, 1, 69 };//destination board ip
//int dest_port = 11002;
byte server[] = { 192, 168, 1, 135 }; // Server board ip
int server_port = 11006;

RoveCommEthernet RoveComm;
rovecomm_packet packet;

void setup()
{
   Serial.begin(9600);
   Serial.println("Starting");

   RoveComm.begin(server[3], server_port);
   Serial.println("Started server");
   delay(1000);
}

void loop()
{
    packet = RoveComm.read();
    
    switch(packet.data_id)
  {
    case RC_DRIVEBOARD_DRIVEINDIVIDUAL_DATAID:
      Serial.println("We received an individual wheel drive command");
      break;
    case RC_DRIVEBOARD_DRIVELEFTRIGHT_DATAID:
      Serial.println("We received a left/right drive command");
      break;
    default:
      Serial.println("Unexpected data id: ");
      Serial.println(packet.data_id);
      break;
  }
    delay(1000);

   int16_t data[5] = {0, 0, 0, 0, 0};
   RoveComm.writeReliable(10100, 5, data);
   Serial.println("Writing");
   
}