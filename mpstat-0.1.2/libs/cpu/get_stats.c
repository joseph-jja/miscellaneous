
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>

#include "cpu.h"

#define CPU_ID "cpu"

void
get_stats (char **cpuids, char **lines, unsigned *itot, unsigned *i1, unsigned *ct)
{

  double ticks = (double) sysconf (_SC_CLK_TCK);

  FILE *cpustatfile;
  int cpu_idx = 0;
  int count = strlen (*cpuids);

  cpustatfile = fopen ("/proc/stat", "r");
  if (cpustatfile == NULL) {
    printf ("could not find /proc/cpustat!!!\n");
  }
  else {
    char buffer[BUFFER_SIZE + 1];
    while (!feof (cpustatfile)) {
      // read a line
      memset (buffer, '\0', BUFFER_SIZE + 1);
      fgets (buffer, BUFFER_SIZE, cpustatfile);
      if (cpu_idx < count && (strncmp (cpuids[cpu_idx], buffer, strlen (cpuids[cpu_idx])) == 0)) {
	lines[cpu_idx] = strdup (buffer);
	cpu_idx++;
      }
      else if (strncmp ("intr ", buffer, strlen ("intr ") == 0)) {
	sscanf (buffer, "intr %u %u", itot, i1);
      }
      else if (strncmp ("ctxt ", buffer, strlen ("ctxt ") == 0)) {
	sscanf (buffer, "ctxt %u", ct);
      }
    }
    fclose (cpustatfile);
  }
}
