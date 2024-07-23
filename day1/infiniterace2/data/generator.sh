#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution jb.py

compile gen.py

MAXN=200000
MAXQ=200000

samplegroup
limits maxn=$MAXN maxq=$MAXQ
sample_manual 1
sample 2
sample 3
sample 4
sample 5

group group1 29
limits maxn=2 maxq=$MAXQ
tc 2
tc 3
tc n2-1 gen mode=random n=2 q=1
tc n2-2 gen mode=random n=2 q=2
tc n2-3 gen mode=random n=2 q=5
tc n2-4 gen mode=random n=2 q=$MAXQ
tc n2-5 gen mode=random n=2 q=$MAXQ
tc n2-6 gen mode=random n=2 q=$MAXQ
tc n2-7 gen mode=random n=2 q=$MAXQ
tc n2-8 gen mode=random n=2 q=100
tc onlyovertake-n2-1 gen mode=random onlyovertake=1 n=2 q=2
tc onlyovertake-n2-2 gen mode=random onlyovertake=1 n=2 q=$MAXQ
tc onlyovertake-n2-3 gen mode=random onlyovertake=1 n=2 q=100
tc n2-nolaps-1 gen mode=nolaps n=2 q=$MAXQ
tc n2-nolaps-2 gen mode=nolaps n=2 q=100
tc n2-ordered-1 gen mode=ordered n=2 q=$MAXQ
tc n2-ordered-2 gen mode=ordered n=2 q=100
tc n2-stupid gen mode=ordered n=2 q=$MAXQ
tc n2-manylaps-medium gen mode=manylaps n=2 q=100
tc n2-manylaps-large gen mode=manylaps n=2 q=$MAXQ

group group2 34
limits maxn=$MAXN maxq=$MAXQ onlyovertake=1
tc 2
tc 4
tc 5
tc onlyovertake-n2-1
tc onlyovertake-n2-2
tc onlyovertake-n2-3
tc onlyovertake-ordered-1 gen mode=ordered onlyovertake=1 n=100 q=100
tc onlyovertake-ordered-2 gen mode=ordered onlyovertake=1 n=$MAXN q=$MAXQ
tc onlyovertake-1 gen mode=random onlyovertake=1 n=$MAXN q=1
tc onlyovertake-2 gen mode=random onlyovertake=1 n=3 q=$MAXQ
tc onlyovertake-3 gen mode=random onlyovertake=1 n=4 q=$MAXQ
tc onlyovertake-4 gen mode=random onlyovertake=1 n=10 q=$MAXQ
tc onlyovertake-5 gen mode=random onlyovertake=1 n=30 q=$MAXQ
tc onlyovertake-6 gen mode=random onlyovertake=1 n=203 q=$MAXQ
tc onlyovertake-7 gen mode=random onlyovertake=1 n=4000 q=$MAXQ
tc onlyovertake-8 gen mode=random onlyovertake=1 n=50000 q=$MAXQ
tc onlyovertake-9 gen mode=random onlyovertake=1 n=$MAXN q=$MAXQ
tc onlyovertake-10 gen mode=random onlyovertake=1 n=$MAXN q=$MAXQ
tc onlyovertake-11 gen mode=random onlyovertake=1 n=$MAXN q=$MAXQ
tc onlyovertake-12 gen mode=random onlyovertake=1 n=100 q=100
tc onlyovertake-biased-medium gen mode=biased onlyovertake=1 n=100 q=100
tc onlyovertake-biased-large gen mode=biased onlyovertake=1 n=$MAXN q=$MAXQ
tc onlyovertake-manylaps-medium gen mode=manylaps onlyovertake=1 n=100 q=100
tc onlyovertake-manylaps-large gen mode=manylaps onlyovertake=1 n=$MAXN q=$MAXQ

group group3 22
limits maxn=100 maxq=100
tc 1
tc 2
tc 3
tc 5
tc n2-1
tc n2-2
tc n2-3
tc n2-8
tc n2-nolaps-2
tc n2-ordered-2
tc n2-manylaps-medium
tc onlyovertake-n2-1
tc onlyovertake-n2-3
tc onlyovertake-12
tc onlyovertake-ordered-1
tc onlyovertake-biased-medium
tc onlyovertake-manylaps-medium
tc medium-1 gen mode=random n=100 q=100
tc medium-2 gen mode=random n=100 q=100
tc medium-nolaps gen mode=nolaps n=100 q=100
tc medium-ordered gen mode=ordered n=100 q=100
tc medium-biased gen mode=biased n=100 q=100
tc medium-stupid gen mode=stupid n=100 q=100
tc medium-manylaps gen mode=manylaps n=100 q=100

group group4 15
limits maxn=$MAXN maxq=$MAXQ
include_group sample
include_group group1
include_group group2
include_group group3
tc large-nolaps-1 gen mode=nolaps n=$MAXN q=$MAXQ
tc large-nolaps-2 gen mode=nolaps n=50000 q=$MAXQ
tc large-ordered-1 gen mode=ordered n=$MAXN q=$MAXQ
tc large-ordered-2 gen mode=ordered n=40000 q=$MAXQ
tc large-manylaps gen mode=manylaps n=$MAXN q=$MAXQ
tc large-1 gen mode=random n=$MAXN q=1
tc large-2 gen mode=random n=3 q=$MAXQ
tc large-3 gen mode=random n=4 q=$MAXQ
tc large-4 gen mode=random n=10 q=$MAXQ
tc large-5 gen mode=random n=30 q=$MAXQ
tc large-6 gen mode=random n=203 q=$MAXQ
tc large-7 gen mode=random n=4000 q=$MAXQ
tc large-8 gen mode=random n=50000 q=$MAXQ
tc large-9 gen mode=random n=$MAXN q=$MAXQ
tc large-10 gen mode=random n=$MAXN q=$MAXQ
tc large-11 gen mode=random n=$MAXN q=$MAXQ
tc large-biased gen mode=biased n=$MAXN q=$MAXQ
tc large-stupid gen mode=stupid n=$MAXN q=$MAXQ
