//Example usage of RoveComm.write for sending Telemetry
//Example of array and single-valued telemetry using BMSBoard as an example
//Andrew Van Horn
//2019-01-29

#include "RoveComm.h"

RoveCommEthernetUdp RoveComm;
rovecomm_packet packet;

void setup() {
  Serial.begin(9600);
  RoveComm.begin(78);
  delay(10);

}

void loop() {
  delay(100);
  float data = 10.6;
  packet = RoveComm.read();
  Serial.println(packet.data_id);
  //uint8_t* array = (uint8_t*) packet.data;
  //Serial.println(array[0]);
  //Serial.println(array[1]);
  RoveComm.write(9000, 1, (uint8_t) 10);
  RoveComm.write(9000, 1, data);
  delay(1000);
}

