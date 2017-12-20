#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h> 
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "cli.h"

char *socket_path = "/tmp/smartcardsrv";

int sendToSrv(char *msg) 
{
    struct sockaddr_un addr;
    int fd;

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        return ENOTCONN;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
    
    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        perror("connect error");
        return ENOTCONN;
    }

    if (write(fd, msg, strlen(msg)) < 0)
        perror("write error");

    close(fd);
    return 0;
}
