#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"

#define CPU_PREFIX "cpu"

void get_identifiers(char **cpuid) {

    FILE *cpuinfofile;
    int i = 0;
    int count = strlen(*cpuid);

    if (count == 1) {
	    cpuid[0] = malloc(strlen(CPU_PREFIX) + 1);
	    if (cpuid[0] != NULL) {
		    memset(cpuid[i], '\0', strlen(CPU_PREFIX) + 1);
		    memcpy(cpuid[i], CPU_PREFIX, strlen(CPU_PREFIX));
        }
        return;
    }

    cpuinfofile = fopen("/proc/cpuinfo","r");
    if (cpuinfofile == NULL ) {
        printf("could not find /proc/cpuinfo!!!\n");
    } else {
        char buffer[BUFFER_SIZE + 1];
        while (!feof(cpuinfofile)) {
            memset(buffer, '\0', BUFFER_SIZE + 1);
            fgets(buffer, BUFFER_SIZE, cpuinfofile);
            if ((strncmp(PROCESSOR, buffer, strlen(PROCESSOR)) == 0)) {
                char *id = strstr(buffer, ":");
                if (id != NULL) {
                    cpuid[i] = malloc(strlen(CPU_PREFIX) + strlen(id) + 1);
                    if (cpuid[i] != NULL) {
                        memset(cpuid[i], '\0', strlen(CPU_PREFIX) + strlen(id) + 1);
                        memcpy(cpuid[i], CPU_PREFIX, strlen(CPU_PREFIX));
                        memcpy(cpuid[i] + strlen(CPU_PREFIX), id+2, strlen(id)-3);
                    }
                }
                i++;
            }
        }
        fclose(cpuinfofile);
    }
}

