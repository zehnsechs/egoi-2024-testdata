#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh

use_solution wendy.cpp

compile gen_random.py
compile gen_t1.py

MAXN=500000000
MAXQ=20000
MAXM=500000

samplegroup
limits maxn=$MAXN maxq=$MAXQ maxm=$MAXM
sample 1
sample 2
sample 3
sample 4
sample 5

group group1 14
limits maxn=$MAXN mode=g1 maxm=1 maxq=$MAXQ
tc 1
tc 2
tc g1_1 gen_random n=2 mode=g1
tc g1_2 gen_random n=10 mode=g1
tc g1_3 gen_random n=100 mode=g1 b=99
tc g1_4 gen_random n=1000 mode=g1 q=1
tc g1_5 gen_random n=100000 mode=g1
tc g1_6 gen_random n=$MAXN mode=g1 b=0
tc g1_7 gen_random n=$MAXN mode=g1
tc g1_8 gen_random n=$MAXN mode=g1
tc g1_9 gen_random n=$MAXN mode=g1
tc g1_10 gen_random n=$MAXN mode=g1

group group2 20
limits maxn=1000 maxm=1000 maxq=1000
tc 1
tc 2
tc 3
tc 4
tc g1_4
tc oneb_smalln_smallq1 gen_random m=1 maxn=1000 q=1000
tc oneb_smalln_smallq2 gen_random m=1 maxn=1000 q=1000
tc smallern1 gen_random maxn=10 q=1000
tc smallern2 gen_random maxn=100 q=1000
tc smalln1 gen_random maxn=1000 q=1000 m=12 b=0
tc smalln2 gen_random maxn=1000 q=1000
tc smalln_maxm1 gen_random n=1000 q=1000
tc smalln_maxm2 gen_random n=1000 q=1000
tc smalln_smallm1 gen_random n=1000 maxm=10 q=1000
tc smalln_smallm2 gen_random n=1000 maxm=10 q=1000
tc smalln_smallm3 gen_random n=1000 maxm=100 q=1000 b=999
tc smalln_smallm4 gen_random n=1000 maxm=100 q=1000
tc smalln_smallq1 gen_random n=1000 q=10
tc smalln_smallq2 gen_random n=1000 q=100
tc x0_smallest1 gen_random mode=x0 n=2 m=1 q=5


group group3 22
limits maxn=10000000 maxm=1000 maxq=1000
include_group group2
tc x0_smallest1
tc oneb_smallq1 gen_random maxn=10000000 m=1 q=1000
tc oneb_smallq2 gen_random maxn=10000000 m=1 q=1000
tc smallmq1 gen_random maxn=10000000 maxm=1000 q=1000 b=0
tc smallmq2 gen_random maxn=10000000 m=1000 q=1000
tc smallmq3 gen_random maxn=10000000 maxm=100 q=1000 b=0
tc smallmq4 gen_random maxn=10000000 maxm=10 q=1000
tc smallmq5 gen_random maxn=10000000 m=1 q=1000
tc smallmq6 gen_random maxn=10000000 m=1 q=1000
tc largen_smallmq1 gen_random n=10000000 m=1000 q=1000 b=0
tc largen_smallmq2 gen_random n=10000000 maxm=1000 q=1000
tc largen_smallmq5 gen_random n=10000000 m=100 q=1000
tc largen_smallmq6 gen_random n=10000000 m=100 q=1000 b=9999999


group group4 17
limits maxn=$MAXN maxm=$MAXM maxq=$MAXQ mode=x0
tc 3
tc g1_6
tc x0_smallest1
tc x0_1 gen_random mode=x0
tc x0_2 gen_random mode=x0
tc x0_oneb1 gen_random mode=x0 m=1
tc x0_oneb2 gen_random mode=x0 m=1
tc x0_oneb3 gen_random mode=x0 m=1
tc x0_smallm1 gen_random mode=x0 maxm=10 b=0
tc x0_smallm2 gen_random mode=x0 maxm=10
tc x0_smallm3 gen_random mode=x0 maxm=100
tc x0_smallm4 gen_random mode=x0 maxm=100
tc x0_smallm5 gen_random mode=x0 maxm=1000 b=0
tc x0_smallm6 gen_random mode=x0 maxm=1000
tc x0_smallm7 gen_random mode=x0 maxm=10000
tc x0_largen1 gen_random mode=x0 n=$MAXN
tc x0_largen2 gen_random mode=x0 n=$MAXN
tc x0_largen3 gen_random mode=x0 n=$MAXN m=$MAXM
tc x0_largen4 gen_random mode=x0 n=$MAXN m=$MAXM

group group5 27
limits maxn=$MAXN maxm=$MAXM maxq=$MAXQ
include_group group1
include_group group2
include_group group3
include_group group4
tc 5
tc all1 gen_random n=$MAXN m=$MAXM q=$MAXQ b=0
tc all2 gen_random n=$MAXN m=$MAXM q=$MAXQ
tc all5 gen_random q=100
tc all6 gen_random q=1
tc all7 gen_random
tc all8 gen_random maxn=$MAXN maxm=$MAXM maxq=$MAXQ b=99999999
tc all9 gen_random maxn=$MAXN maxm=$MAXM maxq=$MAXQ
tc all_smallm1 gen_random maxn=$MAXN m=1
tc all_smallm2 gen_random maxn=$MAXN m=1
tc all_smallm12 gen_random maxn=$MAXN maxm=10
tc all_smallm13 gen_random maxn=$MAXN maxm=100 b=0
tc all_smallm14 gen_random maxn=$MAXN maxm=1000
tc all_smallm15 gen_random maxn=$MAXN maxm=1000
tc all_smallm16 gen_random maxn=$MAXN maxm=10000

