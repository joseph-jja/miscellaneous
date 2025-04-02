# make file for godura gxsearch

CFLAGS = -Wall -g -O2 
CC = gcc $(FCLFLAGS)

GTKOPTIONS = `pkg-config --cflags gtk4`

INCLUDES = ./

SEARCHLIB = gxsearch

# shared libs
LIBSHARED1 = -c -fPIC
LIBSHARED2 = -shared -o

# static libs
LIBSTATIC1 = ar -cr
LIBSTATIC2 = ranlib

all:

static:
	$(CC) -c $(SEARCHLIB).c -I$(INCLUDES) $(GTKOPTIONS) $(GTKFLAGS)
	$(LIBSTATIC1) lib$(SEARCHLIB).a $(SEARCHLIB).o 
	$(LIBSTATIC2) lib$(SEARCHLIB).a 

shared:
	$(CC) $(LIBSHARED1) $(SEARCHLIB).c -I$(INCLUDES) $(GTKOPTIONS)
	$(CC) $(LIBSHARED2) lib$(SEARCHLIB).so $(SEARCHLIB).o

clean:
	rm -f *.o core *.so *.a
