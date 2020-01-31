#include "RoveComm.h"


//byte dest_ip[] = { 192, 168, 1, 69 };//destination board ip
//int dest_port = 11002;
byte server[] = { 192, 168, 1, 136 }; // Server board ip
int server_port = 11005;

RoveCommEthernet RoveComm;
//RoveCommEthernetUdp       RoveCommUDP;
rovecomm_packet packet;
rovecomm_packet udp_packet;


void setup()
{
   Serial.begin(9600);
   Serial.println("Starting");
   //RoveComm.begin(server[3], server_port);
   RoveComm.TCPServer.begin(server[3], server_port);
   RoveComm.UDP.begin();
   Serial.println("Started server");
   delay(1000);
}

void loop()
{
    packet = RoveComm.TCPServer.read();
    udp_packet = RoveComm.UDP.read();
    
    switch(packet.data_id)
        {
        case ROVECOMM_NO_DATA_DATA_ID:
            Serial.println("No New packet!");
            break;
        case RC_DRIVEBOARD_DRIVELEFTRIGHT_DATAID:
            Serial.println("Received drive packet");
            break;
        }
   
   float data[3] = {1.2,2.3,3.4};
   RoveComm.TCPServer.writeReliable((uint16_t) 10100, (uint8_t) 3, data);
   Serial.println("Writing");
   delay(2000);
}