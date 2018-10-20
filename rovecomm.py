import socket
import struct

#############################################
ROVECOMM_2019_UDP_PORT               = 11000

ROVECOMM_2019_SUBSCRIBE_REQUEST_ID   = 1
ROVECOMM_2019_UNSUBSCRIBE_REQUEST_ID = 2

############################################################
# RoveComm Header:
#   uint16_t data_id   
#   uint8_t  data_count
#   uint8_t  data_type

ROVECOMM_2019_STRUCT_HEADER_FORMAT = ">HBB"

INT8_T   = 0
UINT8_T  = 1
INT16_T  = 2
UINT16_T = 3
INT32_T  = 4
UINT32_T = 5

#############################################################################################

def packPacket(data_id, data_type, data_list):

    header = struct.pack(ROVECOMM_2019_STRUCT_HEADER_FORMAT, data_id, len(data_list), data_type)

    if data_type == INT32_T:
        data_type_format = "i"
    elif data_type == UINT32_T:
        data_type_format = "I"
    elif data_type ==  INT16_T:
        data_type_format = "h"
    elif data_type == UINT16_T:
        data_type_format = "H"
    elif data_type == UINT32_T:
        data_type_format = "H"
    elif data_type == INT8_T:
        data_type_format = "b"
    elif data_type == UINT32_T:
        data_type_format = "B"
    else:
        return bytes()
        
    data_bytes = bytes()
    for data_value in data_list:
        data_bytes += struct.pack(data_type_format, data_value)
            
    return header + data_bytes
      
#############################################################################################

def unpackPacket(ethernet_udp_packet):

    header_size = struct.calcsize(ROVECOMM_2019_STRUCT_HEADER_FORMAT)
    data_id, data_count, data_type = struct.unpack(ROVECOMM_2019_STRUCT_HEADER_FORMAT, ethernet_udp_packet[0:header_size])
    data = ethernet_udp_packet[header_size:]

    if data_type == INT32_T:
        data_type_format = "i"
        data_type_size   =  4
    elif data_type == UINT32_T:
        data_type_format = "I"
        data_type_size   =  4
    elif data_type ==  INT16_T:
        data_type_format = "h"
        data_type_size   =  2
    elif data_type == UINT16_T:
        data_type_format = "H"
        data_type_size   =  2
    elif data_type == UINT32_T:
        data_type_format = "H"
    elif data_type == INT8_T:
        data_type_format = "b"
        data_type_size   =  1
    elif data_type == UINT32_T:
        data_type_format = "B"
        data_type_size   =  1
    else:
        return 0, []
    
    data_list = []
    for i in range(data_count):
        data_list.append(struct.unpack(data_type_format, ethernet_udp_packet[( header_size + i*data_type_size) : (header_size + (i+1)*data_type_size)])[0])

    return data_id, data_list

#######################################################################################################################################################
class RoveComm2019EthernetUdp:
    def __init__(self, ip_port=ROVECOMM_2019_UDP_PORT):
    
        self.rovecomm_subscribers = []
        self.EthernetUdpSocket = socket.socket(type = socket.SOCK_DGRAM)
        self.EthernetUdpSocket.bind(("", ip_port))
        
    ######################################################################################################################################################################                
    def writeTo(self, data_id, data_type, data_list, ip_address, ip_port=ROVECOMM_2019_UDP_PORT): #RC2: add data_type, data_count
    
        rovecomm_packet = packPacket(data_id, data_type, data_list)
        self.EthernetUdpSocket.sendto(rovecomm_packet, (ip_address, ip_port))

    ######################################################################################################################################################################      
    def write(self, data_id, data_type, data_list): #RC2: add data_type, data_count

        rovecomm_packet = packPacket(data_id, data_type, data_list)
        for rovecomm_subscriber_ip_address in self.rovecomm_subscribers:
            self.EthernetUdpSocket.sendto(rovecomm_packet, (rovecomm_subscriber_ip_address))
             
    ############################################################################################
    
    def read(self):
    
        # MAX_PACKET_SIZE = HEADER_SIZE + sizeof(uint32_t) * MAX_DATA_COUNT = 4 + 4 * 255 = 1024
        ethernet_udp_packet, recvfrom_ip_address = self.EthernetUdpSocket.recvfrom(1024) 

        data_id, data_list = unpackPacket(ethernet_udp_packet)
    
        if(data_id == ROVECOMM_2019_SUBSCRIBE_REQUEST_ID):
            if(self.rovecomm_subscribers.count(recvfrom_ip_address) == 0):
                self.rovecomm_subscribers.append(recvfrom_ip_address)
                
        elif(data_id == ROVECOMM_2019_UNSUBSCRIBE_REQUEST_ID):
            if(self.rovecomm_subscribers.count(recvfrom_ip_address) > 0):
                self.rovecomm_subscribers.remove(recvfrom_ip_address)
        
        return data_id, data_list

    #################################################################################

    def readFroms(self):
    
        ethernet_udp_packet, recvfrom_ip_address = self.EthernetUdpSocket.recvfrom(1024)

        data_id, data_list = unpackPacket(ethernet_udp_packet)
    
        if(data_id == ROVECOMM_2019_SUBSCRIBE_REQUEST_ID):
            if(self.rovecomm_subscribers.count(recvfrom_ip_address) == 0):
                self.rovecomm_subscribers.append(recvfrom_ip_address)
                
        elif(data_id == ROVECOMM_2019_UNSUBSCRIBE_REQUEST_ID):
            if(self.rovecomm_subscribers.count(recvfrom_ip_address) > 0):
                self.rovecomm_subscribers.remove(recvfrom_ip_address)
        
        return data_id, data_list, recvfrom_ip_address






#############################################################################################################################
# Eli/Andrew Todo => Move this into an actual test file that imports the roveComm module, do full testing with multiple Tivas

###########
import time

####################################
print('Test RoveComm2019EthernetUdp')

########################################
RoveComm2019 = RoveComm2019EthernetUdp()

for i in range(10):

    ############################################################################################################################################
    RoveComm2019.writeTo(data_id=1002, data_type=INT32_T, data_list=[123456789, 1, 2, 3, 4, 5, 6, 7, 8, 9], ip_address='127.0.0.1') # write ints

    data_id, read_data_list = RoveComm2019.read()

    print("data_id", data_id)
    print(read_data_list)

    time.sleep(1)

##############################################################################################################################
#RoveComm2019.write(data_id=1000, data_list=[0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF]) # write ints (INT32_T) to all subscribers

#read_data_list = RoveComm2019.read()
#for data in read_data_list:
 # print(type(data), data)

##################################################################################################################################################
#RoveComm2019.writeTo(data_id=1003, data_list=[0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF], ip_address='127.0.0.1', port=?, data_type=rovecomm.INT32_T,)

#read_data_list = RoveComm2019.read()
#for data in read_data_list:
#  print(type(data), data)
  
#########################################################################################################
# Permutations

#RoveComm2019.write(  1004, [0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF])
#RoveComm2019.writeTo(1005, [0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF], '127.0.0.1', )
#RoveComm2019.writeTo(1006, [0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF], '127.0.0.1', 502, rovecomm.INT32_T )
#RoveComm2019.writeTo(1007, [0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF], '127.0.0.1', 502, rovecomm.UINT32_T)
#RoveComm2019.writeTo(1008, [0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF], '127.0.0.1', 502, rovecomm.INT16_T )
#RoveComm2019.writeTo(1009, [0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF], '127.0.0.1', 502, rovecomm.UINT16_T)
#RoveComm2019.writeTo(1010, [0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF], '127.0.0.1', 502, rovecomm.INT8_T  )
#RoveComm2019.writeTo(1011, [0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF], '127.0.0.1', 502, rovecomm.UINT8_T )

#for i in range( 8 ):
#    data_list, read_from_ip_address = RoveComm2019.readFrom()
#    for data in data_list:
 #     print(type(data), data, read_from_ip_address)

#####################################################
# Ask Eli to provide callback and data router support