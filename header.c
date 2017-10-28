#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "ip.h"
#include "udp.h"
#include <stdlib.h>
#define MAX_WINDOW 5
#define MAX_PAYLOAD 
#define PTYPE_DATA 1
#define PTYPE_ACK 2
#define PTYPE_NACK 3

struct __attribute__((__packed__)) pkt {
    struct {
        uint8_t window : 5;
       uint8_t tr : 1;
       uint8_t type : 2;
        uint8_t seqnum;
        uint16_t length;
       uint32_t timestamp;
       uint32_t crc1;
    } header;
    char *payload;
    uint32_t crc2;
}pkt;

uint8_t pkt_get_window(iph *pkt) {
    return pkt->header.window;
}

uint8_t pkt_get_seqnum(iph *pkt) {
    return pkt->header.seqnum;
}

uint16_t pkt_get_length(iph *pkt) {
    return ntohs(pkt->header.length);
}

uint32_t pkt_get_timestamp(iph *pkt) {
    return pkt->header.timestamp;
}

uint32_t pkt_get_crc1(iph *pkt) {
    return pkt->header.crc1;
}

uint32_t pkt_get_crc2(iph *pkt) {
    return pkt->crc2;
}

uint8_t pkt_get_tr(iph *pkt) {
    return pkt->header.tr;
}

int pkt_set_windows(iph *pkt,uint8_t window ){
        if (window > MAX_WINDOW) {
        return -1;
    } else {
        pkt->header.window = window;
        return 0;
    }
}

int pkt_set_type(iph *pkt,uint8_t type ){
    if (type != PTYPE_DATA && type != PTYPE_ACK){
        return -1;
    } else{
        pkt->header.type = type;
        return 0;
    } 
}

int pkt_set_seqnum(iph *pkt, const uint8_t seqnum ){
        pkt->header.seqnum = seqnum;
        return 1;
}

int pkt_set_length(iph *pkt, uint16_t length){
    if (length > MAX_PAYLOAD) {
        return -1;
    } else {
        pkt->header.length = htons(length);
        return 0;
    }
}