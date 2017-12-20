#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>

#include "cli.h"
#include "input.h"

static void show_events(int nr, int timeout, int verbose);
static void list_devices(void);

int main(int argc, char *argv[])
{
	if(argc == 0)
	{
		list_devices();
		return 0;
	}

	int devnr = atoi(argv[1]);
	int verbose = 0;

	if (argc > 2)
		verbose = strncmp(argv[2], "v", 1) == 0;
	
	show_events(devnr, 10, verbose);
	return 0;
}

static void list_devices(void)
{
	int i, fd;

	for (i = 0; i < 32; i++) 
	{
		/* try to open */
		fd = device_open(i, 1);
		if (-1 == fd)
			return;
		device_info(fd);
		close(fd);
	}
}

static void show_events(int nr, int timeout, int verbose)
{
	struct input_event event;
	struct timeval tv;
	int fd, quit;
	fd_set set;
	char evt[255];
	memset(&evt, 0, 255);

	fd = device_open(nr, 1);
	if (-1 == fd)
		return;

	fprintf(stderr, "waiting for events\n");
	quit = 0;
	do {
		/* wait for input */
		FD_ZERO(&set);
		FD_SET(fd, &set);
		tv.tv_sec = timeout;
		tv.tv_usec = 0;
		switch (select(fd + 1, &set, NULL, NULL, &tv))
		{
		case -1:
			perror("select");
			quit = 1;
			break;
		case 0:
			fprintf(stderr, "waiting...\n");
			continue;
		default:
			if (FD_ISSET(fd, &set)) /* read input */
			{
				switch (read(fd, &event, sizeof(event)))
				{
				case -1:
					perror("read");
					quit = 1;
					break;
				case 0:
					fprintf(stderr, "EOF\n");
					quit = 1;
					break;
				default:
					if (print_event(&event, verbose, evt) == 1)
					{
						fprintf(stderr, "sending %s\n", evt);
						sendToSrv(evt);
						memset(&evt, 0, 255);
					}
					break;
				}
			}
			break;
		}
	} while (quit == 0);
	close(fd);
}
