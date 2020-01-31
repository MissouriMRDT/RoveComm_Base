#ifndef RoveCommEthernet_h
#define RoveCommEthernet_h

#include <stdint.h>
#include <stddef.h>
#include <Energia.h>
#include <Ethernet.h>

#include "RoveCommManifest.h"
#include "RoveCommPacket.h"
#include "../RoveCommEthernetTCP/RoveCommEthernetTCPServer.h"
#include "../RoveCommEthernetTCP/RoveCommEthernetTCPClient.h"
#include "../RoveCommEthernetUDP/RoveCommEthernetUdp.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RoveCommEthernet
{
  private:
    
  public:
    RoveCommEthernetTCPServer TCPServer;
    RoveCommEthernetUdp       UDP;

    struct rovecomm_packet read();

};

#endif // RoveCommEthernet_h