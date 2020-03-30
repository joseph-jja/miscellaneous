
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>

#include "cpu.h" 

#define CPU_ID "cpu"

void get_stats(char **cpuids, char **lines) {

   double ticks = (double)sysconf( _SC_CLK_TCK );

   FILE *cpustatfile;
   int cpu_idx = 0;
   int count = strlen(*cpuids);

   cpustatfile = fopen("/proc/stat","r");
   if (cpustatfile == NULL) {
       printf("could not find /proc/cpustat!!!\n");
   } else {
       char buffer[BUFFER_SIZE + 1];
       while (!feof(cpustatfile)) {
           // read a line
           memset(buffer, '\0', BUFFER_SIZE + 1);
           fgets(buffer, BUFFER_SIZE, cpustatfile);
           if (cpu_idx < count && (strncmp(cpuids[cpu_idx], buffer, strlen(cpuids[cpu_idx])) == 0)) {
               lines[cpu_idx] = strdup(buffer);
               cpu_idx++;
           }
       }
       fclose(cpustatfile);
   }
}
