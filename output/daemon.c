#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

#include "output.h"

const char* socket_path = "/tmp/socket";

const char* chk = "CHECK\0";
const char* idl = "IDLE\0";
const char* sip = "SHOWIP\0";
const char* fla = "FAIL\0";
const char* acc = "ACCEPT\0";

int main(int argc, char *argv[])
{
  idle();

  struct sockaddr_un addr;
  char buf[100];
  int fd,cl,rc;

  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
  {
    perror("socket error");
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
  unlink(socket_path);

  if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("bind error");
    exit(-1);
  }

  if (listen(fd, 5) == -1) {
    perror("listen error");
    exit(-1);
  }

  while (1) {
    if ((cl = accept(fd, NULL, NULL)) == -1) {
      perror("accept error");
      continue;
    } else {
      printf("Connection Start\n");
    }

    while ((rc=read(cl,buf,sizeof(buf))) > 0)
    {
      printf("read %u bytes: %.*s\n", rc, rc, buf);
      if(strncmp(buf, chk, rc) == 0)
      {
        printf("write check msg\n");
        checking();
      }
      else if(strncmp(buf, idl, rc) == 0)
      {
        printf("write idle msg\n");
        idle();
      }
      else if(strncmp(buf, fla, rc) == 0)
      {
        printf("write fail msg\n");
        fail();
      }
      else if(strncmp(buf, acc, rc) == 0)
      {
        printf("write success msg\n");
        succeed();
      }
      else if (strncmp(buf, sip, rc) == 0)
      {
        printf("write showip msg\n");
        showip();
      }
    }

    if (rc == -1)
    {
      perror("read");
      exit(-1);
    }
    else if (rc == 0)
    {
      printf("Connection End\n");
      close(cl);
    }
  }
  close(fd);
  unlink(socket_path);
  return 0;
}

