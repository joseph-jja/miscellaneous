
CC = gcc

CFLAGS = -Wall -g `/usr/bin/ncurses5-config --libs`

CFILES = clock.c
TARGET = clock

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILES)
