 /*
  RoveCommProtocol.h - Library for Wiring + Processing IDE's (Energia/Arduino) 
  
  Copyright (c) 2018 Missouri S&T Mars Rover Design Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef RoveCommProtocol_h
#define RoveCommProtocol_h

#include <stdint.h>
#include <stddef.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The RoveComm 1 Packet Header is 4 bytes long:
// uint16_t data_id   
// uint8_t  data_type
// uint8_t  data_count                
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct rovecomm_packet
{
  int   data_id;
  int   data_count;
  int[] data;
}

enum data_type{INT8_T,  UINT8_T, INT16_T, UINT16_T, INT32_T, UINT32_T}
	
namespace RoveWare
{
  const size_t   ROVECOMM_PACKET_HEADER_SIZE  =  4;  
  
  uint8_t[] packPacket(uint16_t  data_id, data_type data_type, size_t  data_count, const uint8_t* data);
  struct rovecomm_packet unpackPacket(const uint8_t* udp_packet);
}

#endif // RoveCommProtocol_h

