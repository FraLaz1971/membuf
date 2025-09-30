CC=gcc -g -O2
CFLAGS=-I.
LD=gcc
LDFLAGS=-L.
LIBS=
OEXT=.o
EEXT=
RM=rm -f
.PHONY: all clean

all: mainmb$(EEXT) memstr$(EEXT)

membuf$(OEXT): membuf.c membuf.h
	$(CC) -c $<

mainmb$(OEXT): mainmb.c membuf.h
	$(CC) -c $<

mainmb$(EEXT): mainmb.o membuf.o
	$(LD) $^ -o $@

memstr$(OEXT): memstr.c membuf.h
	$(CC) -c $<

memstr$(EEXT): memstr.o membuf.o
	$(LD) $^ -o $@

clean:
	$(RM) *.o mainmb$(EEXT) memstr$(EEXT)
