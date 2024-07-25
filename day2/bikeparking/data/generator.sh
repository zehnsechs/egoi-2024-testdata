#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh

use_solution jan.py

compile gen_list.py
compile gen_partition.py

MAXN=300000
MAXX=1000000000

samplegroup
limits minn=1 maxn=$MAXN maxx=$MAXX maxy=$MAXX maxsumx=$MAXX maxsumy=$MAXX equal=0
sample 1
sample 2
sample 3
sample 4
sample 5

group group1 16
limits minn=2 maxn=2 maxx=100 maxy=100 maxsumx=$MAXX maxsumy=$MAXX equal=0
tc 1
tc n2-zeroes gen_list n=2 minx=0 maxx=0 miny=0 maxy=0
tc n2-all-all-1 gen_list n=2 minx=0 maxx=100 miny=0 maxy=100
tc n2-all-all-2 gen_list n=2 minx=0 maxx=100 miny=0 maxy=100
tc n2-all-all-3 gen_list n=2 minx=0 maxx=100 miny=0 maxy=100
tc n2-all-all-4 gen_list n=2 minx=0 maxx=100 miny=0 maxy=100
tc n2-all-all-5 gen_list n=2 minx=0 maxx=100 miny=0 maxy=100
tc n2-lrg-all-1 gen_list n=2 minx=90 maxx=100 miny=0 maxy=100
tc n2-lrg-all-2 gen_list n=2 minx=90 maxx=100 miny=0 maxy=100
tc n2-lrg-all-3 gen_list n=2 minx=90 maxx=100 miny=0 maxy=100
tc n2-lrg-all-4 gen_list n=2 minx=90 maxx=100 miny=0 maxy=100
tc n2-lrg-all-5 gen_list n=2 minx=90 maxx=100 miny=0 maxy=100
tc n2-lrg-lrg-1 gen_list n=2 minx=90 maxx=100 miny=90 maxy=100
tc n2-lrg-lrg-2 gen_list n=2 minx=90 maxx=100 miny=90 maxy=100
tc n2-lrg-lrg-3 gen_list n=2 minx=90 maxx=100 miny=90 maxy=100
tc n2-lrg-lrg-4 gen_list n=2 minx=90 maxx=100 miny=90 maxy=100
tc n2-lrg-lrg-5 gen_list n=2 minx=90 maxx=100 miny=90 maxy=100
tc n2-left-left gen_partition n=2 sumx=100 xpart=left sumy=100 ypart=left
tc n2-left-right gen_partition n=2 sumx=100 xpart=left sumy=100 ypart=right
tc n2-right-left gen_partition n=2 sumx=100 xpart=right sumy=100 ypart=left
tc n2-right-right gen_partition n=2 sumx=100 xpart=right sumy=100 ypart=right

group group2 9
limits minn=1 maxn=$MAXN maxx=$MAXX maxy=$MAXX maxsumx=$MAXX maxsumy=$MAXX equal=1
tc 2
tc 5
tc n2-zeroes
tc n1-equal gen_list n=1 minx=100 maxx=100 miny=100 maxy=100
tc n2-equal gen_list n=2 minx=999 maxx=999 miny=999 maxy=999
tc n100-equal gen_list n=100 minx=100 maxx=100 miny=100 maxy=100
tc nmax-equal-0 gen_list n=$MAXN minx=0 maxx=0 miny=0 maxy=0
tc nmax-equal-1 gen_list n=$MAXN minx=1 maxx=1 miny=1 maxy=1
tc nmax-equal-3333 gen_list n=$MAXN minx=3333 maxx=3333 miny=3333 maxy=3333
tc n100-pb-pb-ymax gen_partition n=100 sumx=100 xpart=perfectly_balanced sumy=100 ypart=perfectly_balanced

group group3 19
limits minn=1 maxn=$MAXN maxx=1 maxy=1 maxsumx=$MAXX maxsumy=$MAXX equal=0
tc 2
tc 3
tc n2-zeroes
tc n10-1 gen_list n=10 minx=0 maxx=1 miny=0 maxy=1
tc n10-2 gen_list n=10 minx=0 maxx=1 miny=0 maxy=1
tc n10-3 gen_list n=10 minx=0 maxx=1 miny=0 maxy=1 seed=495506
tc n10-4 gen_list n=10 minx=0 maxx=1 miny=0 maxy=1 seed=756313
tc n10-5 gen_list n=10 minx=0 maxx=1 miny=0 maxy=1 seed=444988
tc nmax-1 gen_list n=$MAXN minx=0 maxx=1 miny=0 maxy=1
tc nmax-2 gen_list n=$MAXN minx=0 maxx=1 miny=0 maxy=1
tc nmax-3 gen_list n=$MAXN minx=0 maxx=1 miny=0 maxy=1
tc nmax-4 gen_list n=$MAXN minx=0 maxx=1 miny=0 maxy=1
tc nmax-pb-1 gen_partition n=$MAXN sumx=1000 xpart=perfectly_balanced sumy=1000 ypart=perfectly_balanced
tc nmax-pb-2 gen_partition n=$MAXN sumx=10000 xpart=perfectly_balanced sumy=10000 ypart=perfectly_balanced
tc nmax-pb-3 gen_partition n=$MAXN sumx=100000 xpart=perfectly_balanced sumy=100000 ypart=perfectly_balanced
tc nmax-equal-0
tc nmax-equal-1
tc n100-pb-pb-ymax

group group4 24
limits minn=1 maxn=100 maxx=100 maxy=100 maxsumx=$MAXX maxsumy=$MAXX equal=0
include_group group1
tc 1
tc 2
tc 3
tc 4
tc n1-equal
tc n100-equal
tc n10-1
tc n10-2
tc n10-3
tc n10-4
tc n10-5
tc n100-all-all-1 gen_list n=100 minx=0 maxx=100 miny=0 maxy=100
tc n100-all-all-2 gen_list n=100 minx=0 maxx=100 miny=0 maxy=100
tc n100-all-all-3 gen_list n=100 minx=0 maxx=100 miny=0 maxy=100
tc n100-all-all-4 gen_list n=100 minx=0 maxx=100 miny=0 maxy=100
tc n100-all-all-5 gen_list n=100 minx=0 maxx=100 miny=0 maxy=100
tc n100-all-all-6 gen_list n=100 minx=0 maxx=100 miny=0 maxy=100 seed=908559
tc n100-all-all-7 gen_list n=100 minx=0 maxx=100 miny=0 maxy=100 seed=619251
tc n100-lrg-all-1 gen_list n=100 minx=90 maxx=100 miny=0 maxy=100
tc n100-lrg-all-2 gen_list n=100 minx=90 maxx=100 miny=0 maxy=100
tc n100-lrg-all-3 gen_list n=100 minx=90 maxx=100 miny=0 maxy=100
tc n100-lrg-all-4 gen_list n=100 minx=90 maxx=100 miny=0 maxy=100
tc n100-lrg-all-5 gen_list n=100 minx=90 maxx=100 miny=0 maxy=100
tc n100-lrg-lrg-1 gen_list n=100 minx=90 maxx=100 miny=90 maxy=100
tc n100-lrg-lrg-2 gen_list n=100 minx=90 maxx=100 miny=90 maxy=100
tc n100-lrg-lrg-3 gen_list n=100 minx=90 maxx=100 miny=90 maxy=100
tc n100-lrg-lrg-4 gen_list n=100 minx=90 maxx=100 miny=90 maxy=100
tc n100-lrg-lrg-5 gen_list n=100 minx=90 maxx=100 miny=90 maxy=100
tc n100-left-left gen_partition n=100 sumx=100 xpart=left sumy=100 ypart=left
tc n100-left-right gen_partition n=100 sumx=100 xpart=left sumy=100 ypart=right
tc n100-right-left gen_partition n=100 sumx=100 xpart=right sumy=100 ypart=left
tc n100-right-right gen_partition n=100 sumx=100 xpart=right sumy=100 ypart=right
tc n10-ub-ub gen_partition n=10 sumx=100 xpart=unbalanced sumy=50 ypart=unbalanced
tc n10-ub-qb gen_partition n=10 sumx=100 xpart=unbalanced sumy=50 ypart=quite_balanced
tc n10-ub-pb gen_partition n=10 sumx=100 xpart=unbalanced sumy=50 ypart=perfectly_balanced
tc n10-qb-ub gen_partition n=10 sumx=100 xpart=quite_balanced sumy=50 ypart=unbalanced
tc n10-qb-qb gen_partition n=10 sumx=100 xpart=quite_balanced sumy=50 ypart=quite_balanced
tc n10-qb-pb gen_partition n=10 sumx=100 xpart=quite_balanced sumy=50 ypart=perfectly_balanced
tc n10-pb-ub gen_partition n=10 sumx=100 xpart=perfectly_balanced sumy=50 ypart=unbalanced
tc n10-pb-qb gen_partition n=10 sumx=100 xpart=perfectly_balanced sumy=50 ypart=quite_balanced
tc n10-pb-pb gen_partition n=10 sumx=100 xpart=perfectly_balanced sumy=50 ypart=perfectly_balanced
tc n100-ub-ub-ymax gen_partition n=100 sumx=100 xpart=unbalanced sumy=100 ypart=unbalanced
tc n100-ub-qb-ymax gen_partition n=100 sumx=100 xpart=unbalanced sumy=100 ypart=quite_balanced
tc n100-ub-pb-ymax gen_partition n=100 sumx=100 xpart=unbalanced sumy=100 ypart=perfectly_balanced
tc n100-qb-ub-ymax gen_partition n=100 sumx=100 xpart=quite_balanced sumy=100 ypart=unbalanced
tc n100-qb-qb-ymax gen_partition n=100 sumx=100 xpart=quite_balanced sumy=100 ypart=quite_balanced
tc n100-qb-pb-ymax gen_partition n=100 sumx=100 xpart=quite_balanced sumy=100 ypart=perfectly_balanced
tc n100-pb-ub-ymax gen_partition n=100 sumx=100 xpart=perfectly_balanced sumy=100 ypart=unbalanced
tc n100-pb-qb-ymax gen_partition n=100 sumx=100 xpart=perfectly_balanced sumy=100 ypart=quite_balanced
tc n100-pb-pb-ymax

group group5 32
limits minn=1 maxn=$MAXN maxx=$MAXX maxy=$MAXX maxsumx=$MAXX maxsumy=$MAXX equal=0
include_group sample
include_group group1
include_group group2
include_group group3
include_group group4
tc nmax-ub-ub gen_partition n=$MAXN sumx=$MAXX xpart=unbalanced sumy=100000000 ypart=unbalanced
tc nmax-ub-qb gen_partition n=$MAXN sumx=$MAXX xpart=unbalanced sumy=100000000 ypart=quite_balanced
tc nmax-ub-pb gen_partition n=$MAXN sumx=$MAXX xpart=unbalanced sumy=100000000 ypart=perfectly_balanced
tc nmax-qb-ub gen_partition n=$MAXN sumx=$MAXX xpart=quite_balanced sumy=100000000 ypart=unbalanced
tc nmax-qb-qb gen_partition n=$MAXN sumx=$MAXX xpart=quite_balanced sumy=100000000 ypart=quite_balanced
tc nmax-qb-pb gen_partition n=$MAXN sumx=$MAXX xpart=quite_balanced sumy=100000000 ypart=perfectly_balanced
tc nmax-pb-ub gen_partition n=$MAXN sumx=$MAXX xpart=perfectly_balanced sumy=100000000 ypart=unbalanced
tc nmax-pb-qb gen_partition n=$MAXN sumx=$MAXX xpart=perfectly_balanced sumy=100000000 ypart=quite_balanced
tc nmax-pb-pb gen_partition n=$MAXN sumx=$MAXX xpart=perfectly_balanced sumy=100000000 ypart=perfectly_balanced
tc nmax-ub-ub-ymax gen_partition n=$MAXN sumx=$MAXX xpart=unbalanced sumy=$MAXX ypart=unbalanced
tc nmax-ub-qb-ymax gen_partition n=$MAXN sumx=$MAXX xpart=unbalanced sumy=$MAXX ypart=quite_balanced
tc nmax-ub-pb-ymax gen_partition n=$MAXN sumx=$MAXX xpart=unbalanced sumy=$MAXX ypart=perfectly_balanced
tc nmax-qb-ub-ymax gen_partition n=$MAXN sumx=$MAXX xpart=quite_balanced sumy=$MAXX ypart=unbalanced
tc nmax-qb-qb-ymax gen_partition n=$MAXN sumx=$MAXX xpart=quite_balanced sumy=$MAXX ypart=quite_balanced
tc nmax-qb-pb-ymax gen_partition n=$MAXN sumx=$MAXX xpart=quite_balanced sumy=$MAXX ypart=perfectly_balanced
tc nmax-pb-ub-ymax gen_partition n=$MAXN sumx=$MAXX xpart=perfectly_balanced sumy=$MAXX ypart=unbalanced
tc nmax-pb-qb-ymax gen_partition n=$MAXN sumx=$MAXX xpart=perfectly_balanced sumy=$MAXX ypart=quite_balanced
tc nmax-pb-pb-ymax gen_partition n=$MAXN sumx=$MAXX xpart=perfectly_balanced sumy=$MAXX ypart=perfectly_balanced
tc nmax-left-left gen_partition n=$MAXN sumx=$MAXX xpart=left sumy=$MAXX ypart=left
tc nmax-left-right gen_partition n=$MAXN sumx=$MAXX xpart=left sumy=$MAXX ypart=right
tc nmax-right-left gen_partition n=$MAXN sumx=$MAXX xpart=right sumy=$MAXX ypart=left
tc nmax-right-right gen_partition n=$MAXN sumx=$MAXX xpart=right sumy=$MAXX ypart=right
