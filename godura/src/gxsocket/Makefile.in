# make file for godura gxsocket

CFLAGS = -Wall -g -O2 
CC = gcc $(FCLFLAGS)

GTKOPTIONS = `pkg-config gtk+-2.0 --cflags `

INCLUDES = ./

SOCKLIB = gxsocket

# shared libs
LIBSHARED1 = -c -fPIC
LIBSHARED2 = -shared -o

# static libs
LIBSTATIC1 = ar -cr
LIBSTATIC2 = ranlib

all:

static:
	$(CC) -c $(SOCKLIB).c -I$(INCLUDES) $(GTKOPTIONS) $(GTKFLAGS)
	$(LIBSTATIC1) lib$(SOCKLIB).a $(SOCKLIB).o 
	$(LIBSTATIC2) lib$(SOCKLIB).a 

shared:
	$(CC) $(LIBSHARED1) $(SOCKLIb).c -I$(INCLUDES) $(GTKOPTIONS)
	$(CC) $(LIBSHARED2) lib$(SOCKLIB).so $(SOCKLIB).o

clean:
	rm -f *.o core *.so *.a
