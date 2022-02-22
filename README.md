# RoveComm
The UDP and TCP packet protocol used by MRDT modular microcontrollers

## Dependencies
The current implementation of RoveComm is for the Tiva C Microcontrollers. The ethernet libraries used are from the Energia project.
It also currently supports the Teensy 4.1 Microcontroller. The ethernet libraries are NativeEthernet and NativeEthernetUdp from the Arduino add-on Teensyduino.

## Packet Structure
The RoveComm udp packet header is 5 bytes long:
* uint8_t rovecomm_version
* uint16_t data_id
* uint16_t  data_count   
* uint8_t  data_type

The packet then countains a data_count number of data elements. The size of each element depends on the data type.

Due to memory limitations, the Tiva can only support 21,845 uint8_ts, 10,922 uint16_ts, 5461 uint32_ts, 5461 floats, or 2730 doubles at once.

Due to memory limitations, the Teensy can only support 32,767 uint8_ts, 16,383 uint16_ts, 8,191 uint32_ts, 8,191 floats, or 4,095 doubles at once.

## Use
Examples of how to implement RoveComm on the Tiva C Microcontroller and Teensy 4.1 are [here](https://github.com/MissouriMRDT/RoveComm/tree/dev/examples).
