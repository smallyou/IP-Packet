///
///  IPv4.h
///  IP Packet Reader
///
///  Created by Justin Sostre on 9/21/18.
///  Copyright © 2018 Justin Sostre. All rights reserved.
///
///                                  IPv4 Packet Header Design
///                                            Bits
///        |0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31|
/// B  0   |-vers-|--IHL--|---------TOS---------|--------------------TLength---------------------|
/// Y  4   |----------------ID------------------|--Flags-|-----------Fragment-OffSet-------------|
/// T  8   |------TTL-----|-------Protocol------|------------------Checksum----------------------|
/// E  12  |------------------------------Source-Address-----------------------------------------|
/// S  16  |-----------------------------Destination-Address-------------------------------------|
///    20  |---------------------------------Options---------------------------------------------|

#ifndef IPv4_h
#define IPv4_h

#include <stdio.h>
#include <stdlib.h>

/// IPv4_Packet - struct that 
typedef struct {
    unsigned int version: 4, IHL: 4,
                 TOS: 8, total_length: 16, ID: 16,
                 Flags: 3, fragment_off: 13,
                 TTL: 8, protocol: 8, checksum: 16;
    unsigned int source_address[4], destination_addres[4];
} IPv4_Packet;

/// print_IPv4_packet - prints the IPv4 packet
/// param packet - pointer to the packet being printed.
void print_IPv4_packet(IPv4_Packet *packet);

/// create_IPv4_packet_file - parses the packet data into a IPv4_Packet struct
/// param packet - pointer to the packet struct
/// param file - pointer to the file
/// param ihl - the internet header length
void create_IPv4_packet(IPv4_Packet *packet, FILE *file, int8_t version);

/// create_IPv4_packets - creates IPv4 packets with randomized values
/// param amount - the amount of packets to create
/// param file - pointer to the file being written with the file
void create_IPv4_packets(int amount, FILE *file);

#endif /* IPv4_h */
