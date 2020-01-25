#include "RoveComm.h"


//byte dest_ip[] = { 192, 168, 1, 69 };//destination board ip
//int dest_port = 11002;
byte server[] = { 192, 168, 1, 99 }; // Server board ip
int server_port = 11001;

RoveCommEthernetTCP RoveCommTCP;
rovecomm_packet packet;

void setup()
{
   Serial.begin(9600);
   Serial.println("Starting");
   RoveCommTCP.begin(server[3], server_port);
   Serial.println("Started server");
   delay(1000);
}

void loop()
{
    packet = RoveCommTCP.read();
    if(packet.data_id != ROVECOMM_NO_DATA_DATA_ID)
        {
        Serial.println("New packet!");
        Serial.println(packet.data_id);
        for(int i = 0; i < packet.data_count; i++)
            {
            Serial.println(packet.data[i]);
            }
        }
    float data[2] = {10.6, 9.89};
    Serial.println("Sending packet");
    RoveCommTCP.writeReliable(9000, 2, data);
    delay(1000);
}