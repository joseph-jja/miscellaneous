
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_LINE_LEN 100
#define CPU_STR 12

void get_inter (unsigned inters[], int number_cpus) {
	
	FILE *pFile;
	unsigned i = 1 ,k, j =0, l=0, m=0;
	
    int buffer_size = (number_cpus * CPU_STR) + MIN_LINE_LEN;

    for (j=0; j< number_cpus; j++) {
        inters[j] = 0;
    }
	
	pFile=fopen("/proc/interrupts", "r");
	if (pFile == NULL) {
		printf("error file not found\n");
	} else {
		char *buffer, *tempbuffer;
		buffer = (char*)calloc(buffer_size + 1, sizeof(char));
		tempbuffer = (char*)calloc(12, sizeof(unsigned));
				
		if (buffer != NULL && tempbuffer != NULL) { 
            // throw away frst line
            fgets(buffer, buffer_size, pFile);
		    while (!feof(pFile)) {
                fgets(buffer, buffer_size, pFile);
			    if(strncmp(buffer,"NMI: ",5) == 0) {		
			        break;
			    }
                char *idx = strstr(buffer, ":");
                if (idx != NULL) {
                    int p = strlen(idx + 1);
                    j = 1;
                    while (j < p && idx[j] == ' ') {
                        j++;
                    }
                    k = 0;
                    int x = 0, cpu_idx = 0;
                    memset(tempbuffer, '\0', 12);
                    while (j < p && cpu_idx < number_cpus) {
                        if (idx[j] != ' ') {
                            k = 1;
                            tempbuffer[x] = idx[j];
                            x++; 
                        } else {
                            k = 0;
                            if (x > 0) {
                                unsigned num = strtoul(tempbuffer, NULL,0);
                                inters[cpu_idx] += num;
                                memset(tempbuffer, '\0', 12);
                                cpu_idx++;
                            }
                            x = 0;
                        }
                        j++;
                    }
                }
		   }
		   free(tempbuffer);
		   free(buffer); 
		}
		fclose(pFile);
	}
} 




