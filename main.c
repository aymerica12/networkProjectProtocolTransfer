#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{

    printf("Hello world!\n");
    return 0;
}


int getaddrinfo(const char *node,     // e.g. "www.example.com" or IP, hostname to connect
                const char *service,  // e.g. "http" or port number
                const struct addrinfo *hints,
                struct addrinfo **res);


void ipv4ToBinary(){

    struct sockaddr_in sa; // IPv4
    inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); // IPv4

}

void ipv6ToBinary(){
    struct sockaddr_in6 sa6; // IPv6
    inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6
}

void binaryToIpv4(){
    // IPv4:
    char ip4[INET_ADDRSTRLEN];  // space to hold the IPv4 string
    struct sockaddr_in sa;      // pretend this is loaded with something

    inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

    printf("The IPv4 address is: %s\n", ip4);

}
void binaryToIpv6(){
    // IPv6:
    char ip6[INET6_ADDRSTRLEN]; // space to hold the IPv6 string
    struct sockaddr_in6 sa6;    // pretend this is loaded with something

    inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);

    printf("The address is: %s\n", ip6);
}
