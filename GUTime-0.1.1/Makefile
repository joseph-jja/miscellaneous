
CC = gcc -g
GNOMEFLAGS = `pkg-config --cflags libpanelapplet-2.0` `pkg-config --cflags gtk+-2.0` 
GNOMELIBS = `pkg-config --libs  libpanelapplet-2.0` `pkg-config --libs gtk+-2.0` 

CFILE = GUTime

INSTALLDIR = /usr/local/bin
GNOME_BONOBO_DIR = /usr/lib/bonobo/servers

all:
	$(CC) $(GNOMEFLAGS) -o $(CFILE).o -c $(CFILE).c
	$(CC) $(GNOMELIBS) -o $(CFILE) $(CFILE).o

install:
	install $(CFILE) $(INSTALLDIR)
	install $(CFILE).server $(GNOME_BONOBO_DIR)

clean:
	rm -f *.o core $(CFILE)
