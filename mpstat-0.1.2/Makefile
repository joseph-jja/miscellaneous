# makefile for mpstat
# this file was hand generated ;-)

CC = gcc
OPTIMIZATIONS = -O3
CFLAGS =  -Wall -Wno-unused -g -Wl,-warn-common
SMPFLAGS = -D__SMP__
FLAGS_2_4 = -D__2_6__
INCLUDES = -I/usr/X11R6/include -I/usr/include/ncurses
TARGET = mpstat
FILES = functions.c mpstat.c
INSTALLDIR = /usr/bin/
SHELL_CMD = /bin/sh ./cpucount.sh

all:
	$(SHELL_CMD) 
	$(CC) $(OPTIMIZATIONS) $(INCLUDES) $(SMPFLAGS) $(CFLAGS) $(FILES) -o $(TARGET) 

linux24:
	$(CC) $(OPTIMIZATIONS) $(INCLUDES) $(SMPFLAGS) $(FLAGS_2_4) $(CFLAGS) $(FILES) -o $(TARGET) 
	
debug:
	$(CC) $(OPTIMIZATIONS) -lefence $(INCLUDES) $(SMPFLAGS) $(CFLAGS) $(FILES) -o $(TARGET) 
	
nosmp:
	$(CC) $(OPTIMIZATIONS) $(INCLUDES) $(CFLAGS) $(FILES) -o $(TARGET)

nosmp24:
	$(CC) $(OPTIMIZATIONS) $(INCLUDES) $(FLAGS_2_4) $(CFLAGS) $(FILES) -o $(TARGET)
	
install:
	install $(TARGET) $(INSTALLDIR)

clean:
	rm -f core mpstat *.o
