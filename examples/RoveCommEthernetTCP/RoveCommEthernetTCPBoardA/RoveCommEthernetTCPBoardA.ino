#include "RoveComm.h"


//byte dest_ip[] = { 192, 168, 1, 69 };//destination board ip
//int dest_port = 11002;
byte server[] = { 192, 168, 1, 135 }; // Server board ip
int server_port = 11006;

RoveCommEthernetTCP RoveCommTCP;
rovecomm_packet packet;
int16_t start = 0;

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
    
    Serial.println("Printing dataid:");
    if(packet.data_id != ROVECOMM_NO_DATA_DATA_ID)
        {
        Serial.println("New packet!");
        Serial.println(packet.data_id);
        for(int i = 0; i < packet.data_count; i++)
            {
            Serial.println(packet.data[i]);
            }
        }
    
   int16_t data[5] = {start, start, start, start, start};
   RoveCommTCP.writeReliable(10100, 5, data);
   Serial.println("Writing");
   delay(10000);
}