#include "RoveCommSerial.h"

RoveCommSerial RoveCommSerial;
void setup() {
  Serial.begin(9600);
  Serial.println("Init");
RoveCommSerial.begin(Serial3, Serial4, 9600);
Serial3.begin(9600);
Serial4.begin(9600);
delay(10);
}

void loop() {
delay(100);
uint16_t data = 3;
Serial.println("Writing");
RoveCommSerial.write(10, 1, data);
for(int i = 0; i<100; i++)
{
  Serial.println(i);
}
Serial.println("Reading");
rovecomm_packet Packet = RoveCommSerial.read();
Serial.println("Packt Rx");
delay(100);
for(int i = 0; i<10; i++)
{
  Serial.print(i);
  Serial.print(":");
  Serial.println(Packet.data[i]);
}
Serial.println("Out");
while(Serial4.available())
 {
  Serial.println(Serial4.read());
 }
delay(100);

while(1);
}