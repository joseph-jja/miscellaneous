
SHELL_CMD = /bin/sh ./whichnode.sh
CC = gcc

CFLAGS = -Wall -g `/usr/bin/ncurses5-config --libs` `/usr/bin/ncurses5-config --cflags` -DCLOCK_FONT_WIDTH=11 -DCLOCK_FONT_HEIGHT=15

CFILES = clock.c numbers/numbers.c
TARGET = clock

all:
	$(SHELL_CMD)
	$(CC) $(CFILES) -o $(TARGET) $(CFLAGS)
