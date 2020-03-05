//Example of receiving and writing rovecomm data for a mock driveboard

#include "RoveComm.h"


//byte dest_ip[] = { 192, 168, 1, 69 };//destination board ip
//int dest_port = 11002;
byte server[] = { 192, 168, 1, 135 }; // Server board ip
int server_port = 11006;

RoveCommEthernetTCPServer RoveComm;
rovecomm_packet packet;

int16_t motor_speed[6] = {-500, 200, 740, -720, 10, -182};

void setup() 
{
  Serial.begin(9600);
  RoveComm.begin(RC_DRIVEBOARD_FOURTHOCTET, RC_ROVECOMM_ETHERNET_DRIVE_LIGHTING_BOARD_PORT);
  delay(100);
  Serial.println("Started: ");
}

void loop() 
{
  delay(100);
  packet = RoveComm.read();
  Serial.println(packet.data_id);
  switch(packet.data_id)
  {
    case RC_DRIVEBOARD_DRIVEINDIVIDUAL_DATAID:
      Serial.println("We received an individual wheel drive command");
      break;
    case RC_DRIVEBOARD_DRIVELEFTRIGHT_DATAID:
      //cast the packet to the correct data type
      int16_t* speeds = (int16_t*)packet.data;
      Serial.println("We received a left/right drive command:");
      //Serial.println(printf("Left: %d", speeds[0]));
      //Serial.println(printf("Right: %d", speeds[1]));

      //set the motor speeds to the commanded speeds in RoveComm
      motor_speed[0] = speeds[0];
      motor_speed[1] = speeds[0];
      motor_speed[2] = speeds[0];
      motor_speed[3] = speeds[1];
      motor_speed[4] = speeds[1];
      motor_speed[5] = speeds[1];
      break;
    default:
      Serial.println("Unexpected data id: ");
      Serial.println(packet.data_id);
      break;
  }

  //Code to drive motors goes here


  //Send mock telemetry for drive speeds
  RoveComm.write(RC_DRIVEBOARD_DRIVE_SPEED_DATAID, RC_DRIVEBOARD_DRIVE_SPEED_DATACOUNT, motor_speed);
}

   int16_t data[5] = {0, 0, 0, 0, 0};
   RoveComm.writeReliable(10100, 5, data);
   Serial.println("Writing");
   
}