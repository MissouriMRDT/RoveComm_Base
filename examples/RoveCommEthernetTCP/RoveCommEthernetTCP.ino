#include "RoveComm.h"


byte ip[] = { 192, 168, 1, 69 };
byte server[] = { 192, 168, 1, 99 }; // Server board ip

RoveCommEthernetTCP RoveCommTCP;
String target;

void setup()
{
    RoveCommTCP.begin(server, 11001);
}

void loop()
{
    struct rovecomm_packet rovecomm_packet;
    rovecomm_packet = RoveCommTCP.read();
    if(rovecomm_packet.data_id != 0)
    {
        Serial.println(rovecomm_packet.data_id);
    }
}