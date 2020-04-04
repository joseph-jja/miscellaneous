
#define BUFFER_SIZE 2048
#define PROCESSOR "processor"

int get_count ();

void get_identifiers (char **, int);

void get_stats (char **, char **, unsigned *, unsigned *, unsigned *);

void get_cpu_percent (int, char **, float[][4], float[][4], unsigned *, unsigned *, unsigned *);
