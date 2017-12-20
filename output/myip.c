#include <stdlib.h> // malloc free
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

/**
 * Get the the ip of a specific network
 * netName (eth0, en0 ecc... )
 */ 
void IPv4(char** address, char* netName)
{
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, netName, IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);

    char *res = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

    *address = (char *)malloc(strlen(res)+1);
    memset(*address, 0, strlen(res)+1);
    strncpy(*address, res, strlen(res));    
}

/*
// TEST
int main(void)
{
    char *addrEth;
    char *addrEn;

    IPv4(&addrEth, "eth0");
    IPv4(&addrEn, "en0");
    printf("%s - %s\n", addrEth, addrEn);

    free(addrEth);
    free(addrEn);
    return 0;
}
*/
