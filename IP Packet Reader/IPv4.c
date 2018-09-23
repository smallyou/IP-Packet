//
//  IPv4.c
//  IP Packet Reader
//
//  Created by Justin Sostre on 9/21/18.
//  Copyright © 2018 Justin Sostre. All rights reserved.
//


#include "IPv4.h"

#define IHL(ihl) (0x0F & ihl)
#define FLAGS(byte) (0xE0 & byte) // (0x8000 & byte)
#define FRAG_OFFSET(byte) (printf("%i", 3));


// address_parser - parses the address into a integer array
// param address - pointer to the address location
// param buffer - the buffer with the binary to the packet
// param i - the starting index for the buffer
static void address_parser(unsigned int *address, unsigned char *buffer, int i) {
    int index = 0;
    for (int j = i; j < i+4; j++) {
        address[index] = buffer[j];
        index++;
    }
}


void create_IPv4_packet_file(IPv4_Packet *packet, FILE *file, int8_t ihl) {
    packet->version = 4;
    packet->IHL = IHL(ihl); // figure out the length of the header for iPv4.
    
    unsigned char buffer[packet->IHL * 4];
    fread(buffer, sizeof(char), packet->IHL * 4, file);
    
    packet->TOS = buffer[0];
    packet->TLength = (buffer[1] << 8) | buffer[2]; // total length of the packet including its payload.
    packet->ID = (buffer[3] << 8) | buffer[4];
    
    // flags for fragmentation
    packet->Flags = FLAGS(buffer[5]);
    packet->fragment_off = (0x0E & buffer[5])<<8 | buffer[6];
    
    packet->TTL = buffer[7]; // time to live
    packet->protocol = buffer[8]; // protocol
    packet->checksum = (buffer[9] << 8) | buffer[10];
    
    address_parser(packet->source_address, buffer, 11);
    address_parser(packet->destination_addres, buffer, 15);
}

