# make file for godura gxmessagebox

CFLAGS = -Wall -g -O2 
CC = gcc $(CFLAGS)

GTKOPTIONS = `pkg-config --cflags gtk4`

INCLUDES = ./

MESSAGELIB = gxmessagebox

# shared libs
LIBSHARED1 = -c -fPIC
LIBSHARED2 = -shared -o

# static libs
LIBSTATIC1 = ar -cr
LIBSTATIC2 = ranlib

all:

static:
	$(CC) -c $(MESSAGELIB).c -I$(INCLUDES) $(GTKOPTIONS) 
	$(LIBSTATIC1) lib$(MESSAGELIB).a $(MESSAGELIB).o 
	$(LIBSTATIC2) lib$(MESSAGELIB).a 

shared:
	$(CC) $(LIBSHARED1) $(MESSAGELIB).c -I$(INCLUDES) $(GTKOPTIONS)
	$(CC) $(LIBSHARED2) lib$(MESSAGELIB).so $(MESSAGELIB).o

clean:
	rm -f *.o core *.so *.a
