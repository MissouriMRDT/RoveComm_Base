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

#include <stdint.h>
#include <stddef.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "RoveCommProtocol.h"

uint8_t[] packPacket(uint16_t  data_id, data_type data_type, size_t  data_count, const uint8_t* data);
  struct rovecomm_packet unpackPacket(const uint8_t* udp_packet);
  
namespace RoveWare
{
  void packUdpPacket(uint16_t  data_id, data_type data_type, size_t  data_count, const uint8_t* data) 
  {
    rovecomm_udp_packet[0] = data_id    >>      8;
    rovecomm_udp_packet[1] = data_id    &  0x00FF;
    rovecomm_udp_packet[2] = data_type  &  0x00FF;//Todo: Why??? Test if makes no difference
    rovecomm_udp_packet[3] = data_count &  0x00FF;
	
	int data_array[data_count];
	
	for( i = 0; i < data_count; i+=1)
	{
	  if(data_type == INT8_T)   {data_array[i] = (int) data[i];}
	  if(data_type == UINT8_T)  {data_array[i] = (int) data[i];}
	}
	
	for( i = 0; i < data_count; i+=2)
	{
	  if(data_type == INT16_T)  {data_array[i] = (int) (data[i]+(data[i+1]<< 8));}
	  if(data_type == UINT16_T) {data_array[i] = (int) (data[i]+(data[i+1]<< 8));}
	}
	
	for( i = 0; i < data_count; i+=4)
	{
	  if(data_type == INT32_T)  {data_array[i] = (int) (data[i]+(data[i+1]<< 8)+(data[i+2]<< 16)+(data[i+3]<< 24));}
	  if(data_type == UINT32_T) {data_array[i] = (int) (data[i]+(data[i+1]<< 8)+(data[i+2]<< 16)+(data[i+3]<< 24);)
	}
	
    struct rovecomm_packet rovecomm_packet = {data_id, data_count, data_array};
	return rovecomm_packet;
  }
  
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // todo   
  // todo 
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void unpackPacket(const uint8_t* rovecomm_packet, uint8_t* rovecomm_version, uint16_t* data_id, size_t* data_size, uint8_t* data) 
  {   
    *rovecomm_version  = rovecomm_packet[0];  
    SEQ_NUM_DEPRECATED = rovecomm_packet[1];                              //todo
    SEQ_NUM_DEPRECATED = rovecomm_packet[2] | (SEQ_NUM_DEPRECATED << 8); //todo 
    FLAGS_DEPRECATED   = rovecomm_packet[3];                              //todo
    *data_id           = 0;  
    *data_id           = rovecomm_packet[4];
    *data_id           = rovecomm_packet[5] | (*data_id            << 8);
    *data_size         = 0; 
    *data_size         = rovecomm_packet[6];
    *data_size         = rovecomm_packet[7] | (*data_size          << 8);
    memcpy(data, &(rovecomm_packet[8]), *data_size);    
  }
}

