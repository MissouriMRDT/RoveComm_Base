
#include "RoveCommManifest.h"
#include "RoveCommEthernetUdp.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoveCommEthernetUdp RoveComm;

void setup() 
{
  RoveComm.begin( ROVECOMM_TESTBOARD_IP_OCTET );
}

void loop()
{
  int testboard_telemetry [5] = { analogRead(todo), analogReadtodo), analogRead(todo), analogRead(todo), analogRead(todo) };

  RoveComm.write(ROVECOMM_TESTBOARD_TELEMETRY_2000_DATA_ID, 5, testboard_telemetry);

  struct rovecomm_packet Red = RoveComm.read();

  Serial.print( "data_id: " );
  Serial.println( Red.data_id );

  Serial.print( "data_count: " );
  Serial.println( Red.data_count );

  for(int i=0; i < Red.data_count; i++)
  { 
    Serial.print( "Red.data[" ); Serial.print( i ); Serial.print( "] : " );
    Serial.println(Red.data[i]);
  }

  Serial.println( "\n" );
  delay(1000);
}