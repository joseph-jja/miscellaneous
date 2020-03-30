
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h" 

#define CPU_ID "cpu"

char **get_stats(char **cpuids) {

   FILE *cpustatfile;
   int cpu_idx = 0;

   int count = strlen(*cpuids);
   char *lines[count];

    cpustatfile = fopen("/proc/stat","r");
    if (cpustatfile == NULL ) {
        printf("could not find /proc/cpustat!!!\n");
    } else {
        char buffer[BUFFER_SIZE + 1];
        while (!feof(cpustatfile)) {
            // read a line
            memset(buffer, '\0', BUFFER_SIZE + 1);
            fgets(buffer, BUFFER_SIZE, cpustatfile);
            if (cpu_idx < count && (strncmp(cpuids[cpu_idx], buffer, strlen(cpuids[cpu_idx])) == 0)) {
                printf("%s", buffer);
                cpu_idx++;
            }
        }
        fclose(cpustatfile);
    }
    return NULL;
}
