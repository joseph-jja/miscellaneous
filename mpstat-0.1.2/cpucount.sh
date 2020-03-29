#! /bin/sh

CPU_NUMBER=`grep ^processor /proc/cpuinfo | wc -l `

echo "#define CPU_COUNT $CPU_NUMBER" > cpucount.h

echo "#define CPU_IDS char[$CPU_NUMBER]" >> cpucount.h

echo "void init_cpu_ids();" >> cpucount.h

echo "void init_cpu_ids()" > cpucount.c
grep processor /proc/cpuinfo | sed 's/ //g' | awk -F\: '{print "\tCPU_IDS["$2"] = \42cpu"$2"\42;"}' >> cpucount.c
echo "}" >> cpucount.c


