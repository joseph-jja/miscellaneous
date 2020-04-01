#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>

#include "functions.h"

void usage(void) {
  fprintf(stderr,"usage: %s [-V] [-n] [delay [count]]\n",PROGNAME);
  fprintf(stderr,"              -V prints version.\n");
  fprintf(stderr,"              -n causes the headers not to be reprinted regularly.\n");
  fprintf(stderr,"              delay is the delay between updates in seconds. \n");
  fprintf(stderr,"              count is the number of updates.\n");
  exit(EXIT_FAILURE);
}

void crash(char *filename) {
    perror(filename);
    exit(EXIT_FAILURE);
}

int winhi(void) {
    struct winsize win;
    int rows = 24;
 
    if (ioctl(1, TIOCGWINSZ, &win) != -1 && win.ws_row > 0)
      rows = win.ws_row;
 
    return rows;
}


void showheader(void) {
  printf("%-5s %6s %6s %4s %8s %3s %4s %4s %4s %3s %5s %3s %3s %3s %3s\n",
	 "cpuid","majf","minf","xcal","intr/ithr","csw","icsw","migr",
	 "smtx","srw","syscl","us","sy","wt","idl");
}


