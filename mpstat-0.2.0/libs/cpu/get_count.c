
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"

int
get_count ()
{

  FILE *cpuinfofile;
  int cpu_count = 0;

  cpuinfofile = fopen ("/proc/cpuinfo", "r");
  if (cpuinfofile == NULL) {
    printf ("could not find /proc/cpuinfo!!!\n");
  } else {
    char buffer[BUFFER_SIZE + 1];
    while (!feof (cpuinfofile)) {
      memset (buffer, '\0', BUFFER_SIZE + 1);
      fgets (buffer, BUFFER_SIZE, cpuinfofile);
      if ((strncmp (PROCESSOR, buffer, strlen (PROCESSOR)) == 0)) {
	cpu_count++;
      }
    }
    fclose (cpuinfofile);
  }
  return cpu_count;
}
