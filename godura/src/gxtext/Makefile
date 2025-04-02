# make file for godura gxtext

CFLAGS = -Wall -g -O2 
CC = gcc $(CFLAGS)

GTKOPTIONS = `pkg-config --cflags gtk4`

INCLUDES = ./

TEXTLIB = gxtext

# shared libs
LIBSHARED1 = -c -fPIC
LIBSHARED2 = -shared -o

# static libs
LIBSTATIC1 = ar -cr
LIBSTATIC2 = ranlib

all:

static:
	$(CC) -c $(TEXTLIB).c -I$(INCLUDES) $(GTKOPTIONS) 
	$(LIBSTATIC1) lib$(TEXTLIB).a $(TEXTLIB).o 
	$(LIBSTATIC2) lib$(TEXTLIB).a 

shared:
	$(CC) $(LIBSHARED1) $(TEXTLIB).c -I$(INCLUDES) $(GTKOPTIONS)
	$(CC) $(LIBSHARED2) lib$(TEXTLIB).so $(TEXTLIB).o

clean:
	rm -f *.o core *.so *.a
