# make file for godura

CC = gcc 
CFLAGS = -Wall -g -O2

TARGET = godura

# library names
SEARCHLIB = gxsearch
TEXTLIB = gxtext
MESSAGEBOXLIB = gxmessagebox
SOCKETLIB = gxsocket

GNOMELIBS = `pkg-config --cflags gtk4`
GNOMEFLAGS = `pkg-config --cflags gtk4 --libs`

INCLUDES = -I./gxsearch -I./ -I./gxtext -I./gxmessagebox -I./gxsocket

LIBS = -L./gxsearch -L./gxtext -L./ -L./gxmessagebox -L./gxsocket

FILES = godura_edit.c godura_file.c godura_help.c godura_search.c godura_misc.c godura_undo_redo.c godura_prefs.c 
OBJECTS = godura_edit.o godura_file.o godura_help.o godura_search.o godura_misc.o godura_undo_redo.o godura_prefs.o 
CFILES = $(TARGET).c 

# shared libs
LIBUTIL1 = -c -fPIC
LIBUTIL2 = -shared -o

# static libs
LIBSTATIC1 = ar -cr
LIBSTATIC2 = ranlib

# misc
SPECTOOL = godura_spec

INSTALLDIR = /usr/local/bin

all:
# static lib for the ok, yes, no dialog boxes
	cd gxmessagebox ; make static
# static lib for the composite text widget
	cd gxtext ; make static
# static lib for the search message box
	cd gxsearch ; make static
# static lib for the socket lib
	cd gxsocket ; make static
# godura static lib
# we want to echo out the commands 
	for II in $(FILES) ; do \
		echo $(CC) -c $$II $(INCLUDES) $(GNOMELIBS) ; \
		$(CC) -c $$II $(INCLUDES) $(GNOMELIBS) ; \
	done
	$(LIBSTATIC1) lib$(TARGET).a $(OBJECTS) 
	$(LIBSTATIC2) lib$(TARGET).a
# godura itself 
	#$(CC) -o $(TARGET) $(CFILES) $(INCLUDES) -l$(TARGET) $(GNOMEFLAGS) -l$(SEARCHLIB) -l$(TEXTLIB) -l$(MESSAGEBOXLIB) -l$(SOCKETLIB) $(GNOMELIBS) $(LIBS)
	$(CC) -o $(TARGET) $(CFILES) $(INCLUDES) -l$(TARGET) $(GNOMEFLAGS) -l$(SEARCHLIB) -l$(TEXTLIB) -l$(MESSAGEBOXLIB) -l$(SOCKETLIB) $(GNOMELIBS) $(LIBS)

clean:
	rm -f *.o core godura *.so *.a 
	rm -f $(SEARCHLIB)/*.o $(SEARCHLIB)/*.so $(SEARCHLIB)/*.a
	rm -f $(TEXTLIB)/*.o $(TEXTLIB)/*.so $(TEXTLIB)/*.a
	rm -f $(MESSAGEBOXLIB)/*.o $(MESSAGEBOXLIB)/*.so $(MESSAGEBOXLIB)/*.a
	rm -f $(SOCKETLIB)/*.o $(SOCKETLIB)/*.so $(SOCKETLIB)/*.a
