
#include <stdio.h>
#include <string.h>

void get_inter (unsigned *inters, int number_cpus) {
	
	FILE *pFile;
	unsigned i = 1 ,k, j =0, l=0, m=0;
	unsigned *cpu;
	
	cpu = (unsigned *)calloc(number_cpus + 1, sizeof(unsigned));
	*inters = 0;

        int buffer_size = (number_cpus * 11) + 35;
	
	if (((pFile=fopen("/proc/interrupts", "r")) == NULL)
		|| (cpu == NULL)) {
		printf("error file not found\n");
	} else {
		char *buffer, *tempbuffer;
		buffer = (char*)calloc(buffer_size,sizeof(unsigned));
		tempbuffer = (char*)calloc(12,sizeof(unsigned));
				
		if (buffer != NULL && tempbuffer != NULL) { 
           fgets(buffer, 4+(number_cpus*11)+30, pFile);
		   while (!feof(pFile)) {
			fgets(buffer,4+(number_cpus*11)+30,pFile);
			if(strncmp(buffer,"NMI: ",5) == 0) {		
			   break;
			}
#ifdef __SMP__
			for (j = 1; j<=number_cpus; j++) {
#endif
			   for (i=6+l; i<=16+l;i++) {
				   tempbuffer[m] = buffer[i];
				   m++;
			   }
			   k = strtoul(tempbuffer, NULL,0);
			   cpu[j] = cpu[j] + k;
			   m=0;
#ifdef __SMP__
			   l=l+11;
		    }	
			l=0;
#endif
		   }
		   free(tempbuffer);
		   free(buffer); 
		}
		fclose(pFile);
	}
	/* set value of pointer to value of array */
#ifdef __SMP__
	for (i = 1; i<= number_cpus; i++) {
		*inters = cpu[i];
		inters++;
	}
#else
		*inters = cpu[0];
#endif
	free(cpu);
} 




