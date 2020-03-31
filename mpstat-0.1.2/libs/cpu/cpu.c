#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "cpu.h"

void init_cpus(int cpu_ct, char **cpuids, float last[][4], float cpustats[][4]) {

    char *results[cpu_ct];
    float current[cpu_ct][10];

    get_stats(cpuids, results);

    int i = 0;
    for (i = 0; i<cpu_ct; i++) {

        sscanf(results[i]+strlen(cpuids[i])+1, 
                "%f %f %f %f %f %f %f %f %f %f", 
                &current[i][0], &current[i][1], 
                &current[i][2], &current[i][3], 
                &current[i][4], &current[i][5], 
                &current[i][6], &current[i][7], 
                &current[i][8], &current[i][9]);

        float user = current[i][0] - last[i][0];
        float nice = current[i][1] - last[i][1];
        float system = current[i][2] - last[i][2];
        float idle = current[i][3] - last[i][3];

        float sum = user + nice + system + idle;
        
        cpustats[i][0] = (user/sum)*100;
        cpustats[i][1] = (nice/sum)*100; 
        cpustats[i][2] = (system/sum)*100; 
        cpustats[i][3] = (idle/sum)*100;

        last[i][0] = current[i][0]; 
        last[i][1] = current[i][1]; 
        last[i][2] = current[i][2]; 
        last[i][3] = current[i][3]; 

        free(results[i]);
    }
}

