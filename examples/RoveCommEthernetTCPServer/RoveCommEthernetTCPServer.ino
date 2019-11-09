#include <SPI.h>
#include <Ethernet.h>

//the IP address for this board:
byte ip[] = { 192, 168, 1, 99 };

// Rovecomm standard of port 11000
EthernetServer server = EthernetServer(11000);
bool alreadyConnected = false; // whether or not the client was connected previously

void setup()
{
    // initialize the ethernet device
    Serial.begin(115200);

    Ethernet.begin(0, ip);

    // start listening for clients
    server.begin();
    
    Serial.print("Chat server address:");
    Serial.println(Ethernet.localIP());
}

void loop()
{
  EthernetClient client = server.available();

  
  if (client == true)
    {
    //flush the buffer and send confirmation message if connected for first time
    if (!alreadyConnected) 
        {
        client.flush();

        Serial.println("We have a new client");
        client.println("You are connected!");
        alreadyConnected = true;
        }

    if (client.available() > 0) 
        {
        char input = client.read();
        server.write(input);
        Serial.write(input);
        }
    }
}