
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <zlib.h>
#include <netdb.h>
// The packet length
#define PCKT_LEN 8192
/* Extra #includes */
/* Your code will be inserted here */

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
};

pkt_status_code pkt_set_type(pkt_t *pkt, const ptypes_t type) {
    if (type != PTYPE_DATA && type != PTYPE_ACK) {
        return E_TYPE;
    } else {
        pkt->header.type = type;
        return PKT_OK;
    }
}
uint32_t pkt_gen_crc1(const pkt_t *pkt) {
        unsigned long sum;

        for(sum=0; nwords>0; nwords--)
                sum += *buf++;

        sum = (sum >> 16) + (sum &0xffff);
        sum += (sum >> 16);
        return (unsigned short)(~sum);
}
int main(int argc, char *argv[]){
    int sd;
    // No data/payload just datagram
    char buffer[PCKT_LEN];
    // Our own headers' structures
    struct ipheader *ip = (struct ipheader *) buffer;
    struct udpheader *udp = (struct udpheader *) (buffer + sizeof(struct ipheader));
    // Source and destination addresses: IP and port
    struct sockaddr_in sin, din;
    int one = 1;
    const int *val = &one;

    memset(buffer, 0, PCKT_LEN);

    if(argc != 5)
    {
        printf("- Invalid parameters!!!\n");
        printf("- Usage %s <source hostname/IP> <source port> <target hostname/IP> <target port>\n", argv[0]);
        exit(-1);
    }
    // Create a raw socket with UDP protocol
    sd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sd < 0)
    {
        perror("socket() error");
        // If something wrong just exit
        exit(-1);
    }
    else
        printf("socket() - Using SOCK_RAW socket and UDP protocol is OK.\n");
    }
    // The source is redundant, may be used later if needed
    // The address family
    sin.sin_family = AF_INET;
    din.sin_family = AF_INET;
    // Port numbers
    sin.sin_port = htons(atoi(argv[2]));
    din.sin_port = htons(atoi(argv[4]));
    // IP addresses
    sin.sin_addr.s_addr = inet_addr(argv[1]);
    din.sin_addr.s_addr = inet_addr(argv[3]);


