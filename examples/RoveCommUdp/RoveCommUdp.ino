//Example of receiving and writing rovecomm data for a mock driveboard

#include "RoveComm.h"

RoveCommEthernet RoveComm;
rovecomm_packet packet;

int16_t motor_speed[6] = {-500, 200, 740, -720, 10, -182};

//timekeeping variables
uint32_t last_update_time;

void setup() 
{
  Serial.begin(9600);

  //Set up rovecomm with the correct IP and the TCP server
  RoveComm.begin(RC_DRIVEBOARD_FOURTHOCTET, RC_ROVECOMM_ETHERNET_DRIVE_LIGHTING_BOARD_PORT);
  delay(100);

  Serial.println("Started: ");
  
  //update timekeeping
  last_update_time = millis();
}

void loop() 
{
  packet = RoveComm.read();

  Serial.println("Data id: ");
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

  //Write some mock drive speeds back every 100 milliseconds, it is important that any
  //telemetry is NOT rate limited (using delays) as this will prevent
  //packets from arriving in a timely manner 
  if(millis()-last_update_time >= ROVECOMM_UPDATE_RATE)
  {
      RoveComm.write(RC_DRIVEBOARD_DRIVE_SPEED_DATAID, RC_DRIVEBOARD_DRIVE_SPEED_DATACOUNT, motor_speed);
      last_update_time = millis();
  }
}