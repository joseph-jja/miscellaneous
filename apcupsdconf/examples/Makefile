# Generated automatically from Makefile.in by configure.
#
# Makefile for apcupsd examples directory
#

srcdir = .

INSTALL_PROGRAM = @INSTALL_PROGRAM@
# Generic install program.
INSTALL = @INSTALL@


# Some makes apparently use .PHONY as the default goal if it is before `all'.
.PHONY: all

SHELL = /bin/sh
MAKE = make

hid-ups: hid-ups.c
	cc  hid-ups.c -o hid-ups

client:  client.c
	cc client.c ../lib/libapc.a -o client
	cp client gui/

newslave: newslave.c
	cc newslave.c ../lib/libapc.a -o newslave

clean:
	rm -f core core.* 1 2 3 *.o hid-ups client readfifo

distclean:
	rm -f safe.apccontrol
