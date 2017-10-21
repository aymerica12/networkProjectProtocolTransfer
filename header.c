#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "ip.h"
#include "udp.h"
#include <stdlib.h>

typedef struct pktip {
    UCHAR  hlen : 4, version : 4;
    UCHAR  tos;
    USHORT tot_len;
    USHORT id;
    USHORT offset : 13, flags : 3;
    UCHAR  ttl;
    UCHAR  protocole;
    USHORT somme;
    ULONG  ip_source;
    ULONG  ip_dest;
} PKTIP;

typedef struct pktudp{
    USHORT port_source;
    USHORT port_dest;
    USHORT tot_len;
    USHORT somme;
}PKTUDP;
