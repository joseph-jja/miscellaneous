#! /bin/sh

grep ^processor /proc/cpuinfo | wc -l | awk '{ print "#define CPU_COUNT "$1 }' > cpucount.h


