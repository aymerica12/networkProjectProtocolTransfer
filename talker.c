/*
** talker.c -- a datagram "client" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "header.c"
#include <netdb.h>

#define MAX_MESSAGE 512
#define IP_SOURCE "127.0.0.1"
#define IP_DEST "127.0.0.1"
#define PORT_SOURCE 5050
#define PORT_DEST 5050
#define SERVERPORT "5050"    // the port users will be connecting to
USHORT checksum(void * lpData, size_t size);

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    if (argc != 2) {
        fprintf(stderr,"usage: talker hostname message\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_UDP;


    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    printf("struct p : %d",hints->ai_family);
    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {

        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {

            perror("talker: socket");
            continue;
        }

        break;
    }



    if (p == NULL) {
        fprintf(stderr, "talker: failed to create socket\n");
        return 2;
    }

    printf("Socket is ready, going to build our packet!");

    DWORD sockopt = TRUE;

    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, (char *)&sockopt, sizeof(sockopt)) == SOCKET_ERROR){
        fprintf(stderr, "Function setsockopt failed !.\n");
        return 2;
    }

    printf("setsockopt work !");

    char message[MAX_MESSAGE] = "Bonjour.", * buf;
    USHORT message_len, udp_len, ip_len;

    message_len  = (USHORT)(strlen(message) + 1);
    udp_len      = (USHORT)(sizeof(UDPHEADER) + message_len);
    ip_len       = (USHORT)(sizeof(IPHEADER) + udp_len);

    buf = malloc(ip_len);

    if (buf == NULL){
        fprintf(stderr, "La fonction malloc a echoue.\n");
        return 2;
    }

    SOCKADDR_IN dest;
    IPHEADER ip;
    UDPHEADER udp;

    ip.version    = 4;
    ip.hlen       = 5; /* sizeof(ip) / 4 */
    ip.tos        = 0;
    ip.tot_len    = htons(ip_len);
    ip.id         = htons(1);
    ip.flags      = 0;
    ip.offset     = 0;
    ip.ttl        = 100;
    ip.protocole  = IPPROTO_UDP;
    ip.somme      = 0;
    ip.ip_source  = inet_addr(IP_SOURCE);
    ip.ip_dest    = inet_addr(IP_DEST);

    ip.somme      = checksum(&ip, sizeof(ip));

    udp.port_source  = htons(PORT_SOURCE);
    udp.port_dest    = htons(PORT_DEST);
    udp.tot_len      = htons(udp_len);
    udp.somme        = 0;

    memcpy(buf, &ip, sizeof(ip));
    memcpy(buf + sizeof(ip), &udp, sizeof(udp));
    memcpy(buf + sizeof(ip) + sizeof(udp), message, message_len);

    ZeroMemory(&dest, sizeof(dest));
    dest.sin_family       = AF_INET;
    dest.sin_addr.s_addr  = inet_addr(IP_DEST);
    dest.sin_port         = htons(PORT_DEST);

    if (sendto(s, buf, ip_len, 0, (SOCKADDR *)&dest, sizeof(dest)) == SOCKET_ERROR){
        fprintf(stderr, "La fonction sendto a echoue.\n");
        return 2;
    }
    else
        printf("Message envoye !\n");

    free(buf);

    freeaddrinfo(servinfo);

    printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
    close(sockfd);

    return 0;
}
USHORT checksum(void * lpData, size_t size)
{
    USHORT * t = lpData;
    DWORD somme = 0;
    size_t i, n = size / sizeof(USHORT);

    for(i = 0; i < n; i++)
        somme += t[i];

    if (size % 2)
    {
        UCHAR * u = lpData;
        somme += u[size - 1];
    }

    while (HIWORD(somme))
        somme = HIWORD(somme) + LOWORD(somme);

    return LOWORD(~somme);
}
