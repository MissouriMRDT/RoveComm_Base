#include "RoveComm.h"


byte dest_ip[] = { 192, 168, 1, 99 };
IPAddress destIP(192, 168, 1, 99);
int dest_port = 11000;
byte server[] = { 192, 168, 1, 49 }; // Server board ip
int server_port = 11002;

RoveCommEthernetTCP RoveCommTCP;


void setup()
{
   Serial.begin(9600);
   Serial.println("Started");
   RoveCommTCP.begin(server[3], server_port);
   RoveCommTCP.connect(dest_ip[0],dest_ip[1],dest_ip[2],dest_ip[3], dest_port);
   Serial.println("Server Started");
}

void loop()
{
   RoveCommTCP.writeReliableTo((uint16_t)9000, (uint8_t)2, (uint8_t)69, dest_ip[0],dest_ip[1],dest_ip[2],dest_ip[3], dest_port);
   delay(25000);  
}