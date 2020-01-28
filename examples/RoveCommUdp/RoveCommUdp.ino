//Example usage of RoveComm.write for sending Telemetry
//Example of array and single-valued telemetry using BMSBoard as an example
//Andrew Van Horn
//2019-01-29

#include "RoveComm.h"

RoveCommEthernet RoveComm;
rovecomm_packet packet;

int16_t speed[6] = {-500, 200, 740, -720, 10, -182};
void setup() {
  Serial.begin(9600);
  RoveComm.begin(RC_DRIVEBOARD_FOURTHOCTET, RC_ROVECOMM_ETHERNET_DRIVE_LIGHTING_BOARD_PORT);
  delay(100);
  Serial.println("Started");

}

void loop() {
  delay(100);
  packet = RoveComm.read();
  Serial.println(packet.data_id);
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
  //Send mock telemetry for drive speeds
  RoveComm.write(RC_DRIVEBOARD_DRIVE_SPEED_DATAID, RC_DRIVEBOARD_DRIVE_SPEED_DATACOUNT, speed);
}

