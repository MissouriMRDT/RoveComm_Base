#include <Ethernet.h>
#include <SPI.h>


byte ip[] = { 192, 168, 1, 69 };
byte server[] = { 192, 168, 1, 99 }; // Server board ip

EthernetClient client;
String target;

void setup()
{
    Ethernet.begin(0, ip);
    Serial.begin(115200);

    Serial.println("connecting...");
    Serial.println("Client server address:");
    Serial.println(Ethernet.localIP());

    // Rovecomm standard of port 11000
    if (client.connect(server, 11000)) 
        {
        Serial.println("Connected");
        } 
    else 
        {
        Serial.println("Connection failed");
        }
}

void loop()
{

    if (client.available()) 
        {
        char c = client.read();
        Serial.print(c);
        }

    // as long as there are bytes in the serial queue,
    // read them and send them out the socket if it's open:
    while (Serial.available() > 0) 
        {
        char inChar = Serial.read();
        if (client.connected()) 
            {
            client.print(inChar);
            }
        }

    // if the server's disconnected, stop the client:
    if (!client.connected()) 
        {
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();
        }

}