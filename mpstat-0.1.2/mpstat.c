/* Started to convert the vmstat program to a mpstat like program for use with 
SMP Linux. Although not complete the output data is correct. Added cpuid and 
multiple cpu handling.*/
/* removed dependance ont the procps package */
/* June 11, 1999 added function to get per processor interupts */
/* June 18, 1999 combined intr and ithr see FAQ.txt */
/* Feb 23, 2001 ump fixes, fixes for kernel 2.4 */
/* April xx 2020 refactor */

#include "mpstat.h"
#include "libs/interrupts.h"
#include "libs/cpu/cpu.h"

int main (int, char **);

/***************************************************************
                             Main 
***************************************************************/

int
main (int argc, char *argv[])
{

  const char format[] = "%s %6u %6u %4u %9u %3u %4u %4u %4u %3u %5u %3.0f %3.0f %3.0f %3.0f\n";
  unsigned int height = 22;	/* window height, reset later if needed. */
  unsigned long int args[2] = { 0, 0 };
  unsigned int moreheaders = TRUE;
  unsigned int tog = 0;		/* toggle switch for cleaner code */
  /* SMP tog switches */
  unsigned int i, hz;
  unsigned int running[MAX_NR_CPUS], blocked[MAX_NR_CPUS];	/* running and blocked processes */
  unsigned int memfree = 0;	/* dummy var set to zero for space holder */
  unsigned int inter[2], ticks[2], ctxt;
  unsigned int per = 0, pero2;
  unsigned long num = 0;
  unsigned int cpu_wait[MAX_NR_CPUS], cpu_inter[MAX_NR_CPUS];
  static int num_cpus;
  unsigned int cpu_useage[MAX_NR_CPUS], cpu_nicage[MAX_NR_CPUS], cpu_sysage[MAX_NR_CPUS];
  unsigned long cpu_idlage[MAX_NR_CPUS];
  int ret_stat;
  int ii;
  unsigned int duser[MAX_NR_CPUS], dsystem[MAX_NR_CPUS], didle[MAX_NR_CPUS], divid[MAX_NR_CPUS], divo22[MAX_NR_CPUS];
  int *cpuid;

  cpuid = (int *) calloc (sizeof (MAX_NR_CPUS + 1), sizeof (TWOBITE));
  if (cpuid == NULL) {
    printf ("could not allocate memory exiting \n");
    exit (-1);
  }

  setlinebuf (stdout);
  argc = 0;			/* redefined as number of integer arguments */
  for (argv++; *argv; argv++) {
    if ('-' == (**argv)) {
      switch (*(++(*argv))) {
      case 'V':
	printf ("%s\n%s\n%s\n", PROGNAME, VERSION, REQUIRES);
	exit (0);
      case 'n':
	/* print only one header */
	moreheaders = FALSE;
	break;
      default:
	/* no other aguments defined yet. */
	usage ();
      }
    }
    else {
      if (!sscanf (*argv, "%lu", args + argc++))
	usage ();
    }
  }
  switch (argc) {
  case 0:			/* no numeric args */
    per = 1;
    num = 0;
    break;
  case 1:
    per = (unsigned) args[0];
    num = ULONG_MAX;
    break;
  case 2:
    per = (unsigned) args[0];
    num = args[1];
    break;
  default:
    usage ();
    break;
  }
  /* here we get the number of cpus and also get the cpu id 
   * the number of cpu's is returned by the function while the 
   * the cpu id is passed by reference */
  num_cpus = get_count ();
  if (num_cpus == 0) {
    printf ("NO CPUS DETECTED!!!! FATAL ERROR EXITING!!!\n");
    exit (-1);
  }
  else if (num_cpus > MAX_NR_CPUS) {
    printf ("***************WARNING!!!***************\n");
    printf ("This version of mpstat only accepts %d cpu's and may segfault \n", MAX_NR_CPUS);
    printf ("or show improper information.\n");
    exit (-1);
  }

  char *cpu_ids[num_cpus];
  get_identifiers (cpu_ids, num_cpus);

  float last[num_cpus][4], cpu_stats[num_cpus][4];

  if (moreheaders) {
    int tmp = winhi () - 3;
    height = (((tmp > 0) ? tmp : 22) / num_cpus);
  }

  pero2 = (per / 2);

  showheader ();
  getfaults(running,blocked, num_cpus, cpuid);
  get_inter (cpu_inter, num_cpus);
  get_cpu_percent (num_cpus, cpu_ids, last, cpu_stats, inter, ticks, &ctxt);
  hz = sysconf (_SC_CLK_TCK);	/* get ticks/s from system */
  // code here needs to be cleaned up here

  for (ii = 0; ii < num_cpus; ii++) {
    duser[0] = cpu_stats[ii][0] + cpu_stats[ii][2];
       dsystem[0] = cpu_stats[ii][1];
       didle[0] = ((long)cpu_stats[ii][3])%UINT_MAX;
       divid[0] = (duser[0] + dsystem[0] + didle[0]);
       divo22[0] = divid[0]/2;
       cpu_wait[0]=0;

    printf (format, cpu_ids[ii], running[ii], blocked[ii], memfree, cpu_inter[ii], 
          (ctxt*hz+divo22[0])/divid[0],
	    memfree, memfree, memfree, memfree, memfree, cpu_stats[ii][0], cpu_stats[ii][1], cpu_stats[ii][2], cpu_stats[ii][3]);
  }

  for (i = 1; i < num; i++) {	/* \\\\\\\\\\\\\\\\\\\\ main loop ////////////////// */
    sleep (per);

    if (moreheaders && ((i % height) == 0))
      showheader ();
    tog = !tog;
    getfaults(running,blocked, num_cpus, cpuid);
    get_inter (cpu_inter, num_cpus);
    get_cpu_percent (num_cpus, cpu_ids, last, cpu_stats, inter, ticks, &ctxt);

    for (ii = 0; ii < num_cpus; ii++) {
    duser[0] = cpu_stats[ii][0] + cpu_stats[ii][2];
       dsystem[0] = cpu_stats[ii][1];
       didle[0] = ((long)cpu_stats[ii][3])%UINT_MAX;
       divid[0] = (duser[0] + dsystem[0] + didle[0]);
       divo22[0] = divid[0]/2;
       cpu_wait[0]=0;

      printf (format, cpu_ids[ii], running[ii], blocked[ii],memfree,
	      cpu_inter[ii], (ctxt*hz+divo22[0])/divid[0],
	      memfree, memfree, memfree, memfree, memfree, cpu_stats[ii][0], cpu_stats[ii][1], cpu_stats[ii][2], cpu_stats[ii][3]);

    }
  }
  free (cpuid);
  exit (EXIT_SUCCESS);
}

