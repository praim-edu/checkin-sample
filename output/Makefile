CC      = gcc
INCLUDE = -I/usr/local/include
CFLAGS  = -Wall $(INCLUDE) -Winline -pipe

LDFLAGS = -L/usr/local/lib
LDLIBS  = -lwiringPi -lwiringPiDev -lpthread -lm

all:
	@echo "[Build]"
	$(CC) $(CFLAGS) $(LDFLAGS) output.c daemon.c myip.c $(LDLIBS) -o output

help:
	@echo "make all"

clean:
	@echo "[Clean]"
	@rm -f *.o
	@rm -f output
