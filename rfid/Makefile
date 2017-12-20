# programs
CC		?= gcc
CFLAGS	?= -g -O2 -Wall -Wmissing-prototypes -Wstrict-prototypes \
		   -Wpointer-arith -Wunused  -I .
LDLIBS	+= -lm

# add /usr/local to the search path if something is in there ...
ifneq ($(wildcard /usr/local/include/*.h),)
  CFLAGS  += -I/usr/local/include
endif

# dependency files
tmpdep		= tmp/$(subst /,_,$*).tmp
depfile		= tmp/$(subst /,_,$*).dep
depfiles	= tmp/*.dep

TARGETS	:= main
HEADERS	:= EV.h REL.h ABS.h MSC.h LED.h SND.h REP.h KEY.h BTN.h BUS.h SW.h

all: build

build: $(TARGETS)
	rm -rf tmp

$(HEADERS): name.sh
	sh name.sh $* > $@

main: main.o input.o cli.o

input.o: input.c $(HEADERS)

%.o: %.c
	mkdir -p $(dir $@) $(dir $(depfile))
	$(CC) $(CFLAGS) -Wp,-MD,$(tmpdep) -c -o $@ $<
	sed -e "s|.*\.o:|$@:|" < $(tmpdep) > $(depfile) && rm -f $(tmpdep)

clean:
	-rm -f *.o $(depfiles)
	-rm -f $(TARGETS) $(HEADERS) *~ xpm/*~ *.bak
	-rm -rf tmp

-include $(depfiles)