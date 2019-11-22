
CC = gcc

CFLAGS = -Wall -g `/usr/bin/ncurses5-config --libs` `/usr/bin/ncurses5-config --cflags`

CFILES = clock.c numbers/numbers.c
TARGET = clock

all:
	$(CC) $(CFILES) -o $(TARGET) $(CFLAGS)
