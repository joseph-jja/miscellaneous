# make file for godura

CC = gcc

prefix = /usr/local
exec_prefix = /usr/local
bindir = /usr/local/bin

INSTALL = /usr/bin/install -c

MAKE_COMMAND = 

all:
	cd src ; make

clean:
	cd src ; make clean

distclean:
	make clean
	cd src; rm -rf Makefile 
	cd src/gxtext ; rm -rf Makefile
	cd src/gxsearch ; rm -rf Makefile
	cd src/gxmessagebox ; rm -rf Makefile
	cd src/gxsocket ; rm -rf Makefile
	rm -rf config.cache config.log config.h
	rm -rf Makefile 

install:
	${INSTALL} src/godura ${exec_prefix}/bin
