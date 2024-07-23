#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh

use_solution mainAC.cpp

compile gen_random.py

MAXN=200000
MAXVAL=1000000000

samplegroup
limits maxn=$MAXN maxval=$MAXVAL all_equal=0 r0=0
sample 1
sample 2
sample 3
sample 4
sample 5

group group1 8
limits maxn=$MAXN maxval=$MAXVAL all_equal=1 r0=0
tc 4
tc n1-lr gen_random n=1 maxL=200000 maxR=200000 min_ans=0 mode=lr
tc lr-1 gen_random n=200000 maxL=0 maxR=0 min_ans=0 mode=lr
tc lr-2 gen_random n=200000 maxL=52 maxR=52 min_ans=0 mode=lr
tc lr-3 gen_random n=200000 maxL=500 maxR=500 min_ans=0 mode=lr
tc lr-4 gen_random n=200000 maxL=1000 maxR=1000 min_ans=0 mode=lr
tc lr-5 gen_random n=200000 maxL=5000 maxR=5000 min_ans=0 mode=lr
tc lr-6 gen_random n=200000 maxL=10000 maxR=10000 min_ans=0 mode=lr
tc lr-7 gen_random n=200000 maxL=50000 maxR=50000 min_ans=0 mode=lr
tc lr-8 gen_random n=200000 maxL=100000 maxR=100000 min_ans=0 mode=lr
tc smalln-32 gen_random n=1000 maxL=0 maxR=0 min_ans=0 mode=lr
tc smalln-33 gen_random n=1000 maxL=10 maxR=10 min_ans=0 mode=lr
tc smalln-34 gen_random n=1000 maxL=50 maxR=50 min_ans=0 mode=lr
tc smalln-35 gen_random n=1000 maxL=100 maxR=100 min_ans=0 mode=lr
tc smalln-36 gen_random n=1000 maxL=500 maxR=500 min_ans=0 mode=lr

group group2 16
limits maxn=$MAXN maxval=$MAXVAL all_equal=0 r0=1
tc 3
tc lr-1
tc n1-r0 gen_random n=1 maxL=$MAXVAL maxR=0 min_ans=0
tc r0-02 gen_random n=200000 maxL=1 maxR=0 min_ans=0
tc r0-03 gen_random n=200000 maxL=2 maxR=0 min_ans=0
tc r0-04 gen_random n=200000 maxL=3 maxR=0 min_ans=0
tc r0-05 gen_random n=200000 maxL=4 maxR=0 min_ans=0
tc r0-06 gen_random n=200000 maxL=5 maxR=0 min_ans=0
tc r0-07 gen_random n=200000 maxL=9 maxR=0 min_ans=0
tc r0-08 gen_random n=200000 maxL=10 maxR=0 min_ans=0
tc r0-09 gen_random n=200000 maxL=25 maxR=0 min_ans=0
tc r0-10 gen_random n=200000 maxL=33 maxR=0 min_ans=0
tc r0-11 gen_random n=200000 maxL=47 maxR=0 min_ans=0
tc r0-12 gen_random n=200000 maxL=62 maxR=0 min_ans=0
tc r0-13 gen_random n=200000 maxL=81 maxR=0 min_ans=0
tc r0-14 gen_random n=200000 maxL=103 maxR=0 min_ans=0
tc r0-15 gen_random n=200000 maxL=508 maxR=0 min_ans=0
tc r0-16 gen_random n=200000 maxL=1000 maxR=0 min_ans=0
tc r0-17 gen_random n=200000 maxL=9418 maxR=0 min_ans=0
tc r0-18 gen_random n=200000 maxL=4400 maxR=0 min_ans=0
tc r0-19 gen_random n=200000 maxL=5344 maxR=0 min_ans=0
tc r0-20 gen_random n=200000 maxL=200000 maxR=0 min_ans=0
tc r0-21 gen_random n=200000 maxL=1000000000 maxR=0 min_ans=0
tc smalln-26 gen_random n=1000 maxL=5 maxR=0 min_ans=0
tc smalln-27 gen_random n=1000 maxL=9 maxR=0 min_ans=0
tc smalln-28 gen_random n=1000 maxL=10 maxR=0 min_ans=0
tc smalln-29 gen_random n=1000 maxL=25 maxR=0 min_ans=0
tc smalln-30 gen_random n=1000 maxL=33 maxR=0 min_ans=0
tc smalln-31 gen_random n=1000 maxL=47 maxR=0 min_ans=0
tc smalln-32
tc small_lr-03 gen_random n=200000 maxL=2 maxR=0 min_ans=0
tc small_lr-06 gen_random n=200000 maxL=1 maxR=0 min_ans=0

group group3 28
limits maxn=1000 maxval=$MAXVAL all_equal=0 r0=0
include_group sample
tc full-ranges-01 gen_random n=1000 maxL=1000 maxR=1000 min_ans=-1
tc full-ranges-02 gen_random n=1000 maxL=1000 maxR=1000 min_ans=-2
tc full-ranges-03 gen_random n=999 maxL=1000 maxR=1000 min_ans=-2
tc smalln-01 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=1
tc smalln-02 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=2
tc smalln-03 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=3
tc smalln-04 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=5
tc smalln-05 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=7
tc smalln-06 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=10
tc smalln-07 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=17
tc smalln-08 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=24
tc smalln-09 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=36
tc smalln-10 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=52
tc smalln-11 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=70
tc smalln-12 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=123
tc smalln-13 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=206
tc smalln-14 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=319
tc smalln-15 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=455
tc smalln-16 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=513
tc smalln-17 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=602
tc smalln-18 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=775
tc smalln-19 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=900
tc smalln-20 gen_random n=1000 maxL=1000000000 maxR=1000000000 min_ans=1000
tc smalln-21 gen_random n=513 maxL=1000000000 maxR=1000000000 min_ans=1
tc smalln-22 gen_random n=609 maxL=1000000000 maxR=1000000000 min_ans=2
tc smalln-23 gen_random n=875 maxL=1000000000 maxR=1000000000 min_ans=3
tc smalln-24 gen_random n=913 maxL=1000000000 maxR=1000000000 min_ans=4
tc smalln-25 gen_random n=425 maxL=1000000000 maxR=1000000000 min_ans=5
tc smalln-26
tc smalln-27
tc smalln-28
tc smalln-29
tc smalln-30
tc smalln-31
tc smalln-32
tc smalln-33
tc smalln-34
tc smalln-35
tc smalln-36
tc smalln-37 gen_random n=1000 maxL=1010 maxR=1010 min_ans=1
tc smalln-38 gen_random n=1000 maxL=100 maxR=100 min_ans=2
tc smalln-39 gen_random n=1000 maxL=100 maxR=100 min_ans=3
tc smalln-40 gen_random n=1000 maxL=100 maxR=100 min_ans=5
tc smalln-41 gen_random n=1000 maxL=100 maxR=100 min_ans=7
tc smalln-42 gen_random n=1000 maxL=100 maxR=100 min_ans=10
tc smalln-43 gen_random n=1000 maxL=100 maxR=100 min_ans=17
tc smalln-44 gen_random n=1000 maxL=100 maxR=100 min_ans=24
tc smalln-45 gen_random n=1000 maxL=100 maxR=100 min_ans=36
tc smalln-46 gen_random n=1000 maxL=100 maxR=100 min_ans=52
tc smalln-47 gen_random n=1000 maxL=100 maxR=100 min_ans=70
tc smalln-48 gen_random n=1000 maxL=100 maxR=100 min_ans=123
tc smalln-49 gen_random n=1000 maxL=100 maxR=100 min_ans=200
tc smalln-50 gen_random n=1000 maxL=100 maxR=100 min_ans=250
tc smalln-51 gen_random n=1000 maxL=100 maxR=100 min_ans=300
tc smalln-52 gen_random n=1000 maxL=100 maxR=100 min_ans=350
tc smalln-53 gen_random n=1000 maxL=100 maxR=100 min_ans=375
tc smalln-54 gen_random n=1000 maxL=100 maxR=100 min_ans=400
tc smalln-55 gen_random n=1000 maxL=100 maxR=100 min_ans=500
tc smalln-56 gen_random n=1000 maxL=100 maxR=100 min_ans=575
tc smalln-57 gen_random n=1000 maxL=200 maxR=200 min_ans=700
tc smalln-58 gen_random n=1000 maxL=200 maxR=200 min_ans=800
tc smalln-59 gen_random n=1000 maxL=200 maxR=200 min_ans=900
tc smalln-60 gen_random n=1000 maxL=200 maxR=200 min_ans=933
tc smalln-61 gen_random n=1000 maxL=200 maxR=200 min_ans=947
tc smalln-62 gen_random n=1000 maxL=200 maxR=200 min_ans=973
tc smalln-63 gen_random n=1000 maxL=1010 maxR=1010 min_ans=5
tc smalln-64 gen_random n=1000 maxL=1010 maxR=1010 min_ans=7
tc smalln-65 gen_random n=1000 maxL=1010 maxR=1010 min_ans=10
tc smalln-66 gen_random n=1000 maxL=1010 maxR=1010 min_ans=17
tc smalln-67 gen_random n=1000 maxL=1010 maxR=1010 min_ans=24
tc smalln-68 gen_random n=1000 maxL=1010 maxR=1010 min_ans=36
tc smalln-69 gen_random n=1000 maxL=1010 maxR=1010 min_ans=52
tc smalln-70 gen_random n=1000 maxL=1010 maxR=1010 min_ans=70
tc smalln-71 gen_random n=1000 maxL=1010 maxR=1010 min_ans=123

group group4 18
limits maxn=$MAXN maxval=2 all_equal=0 r0=0
tc 4
tc 5
tc r0-02
tc r0-03
tc smalln-32
tc small_lr-01 gen_random n=200000 maxL=2 maxR=2 min_ans=0
tc small_lr-02 gen_random n=200000 maxL=2 maxR=1 min_ans=0
tc small_lr-03
tc small_lr-04 gen_random n=200000 maxL=1 maxR=2 min_ans=0
tc small_lr-05 gen_random n=200000 maxL=1 maxR=1 min_ans=0
tc small_lr-06
tc lr-1
tc small_lr-08 gen_random n=200000 maxL=0 maxR=2 min_ans=0
tc small_lr-09 gen_random n=200000 maxL=0 maxR=1 min_ans=0
tc small_lr-10 gen_random n=199999 maxL=2 maxR=2 min_ans=0
tc small_lr-11 gen_random n=199998 maxL=2 maxR=2 min_ans=0
tc small_lr-12 gen_random n=199997 maxL=2 maxR=2 min_ans=0
tc small_lr-13 gen_random n=199996 maxL=2 maxR=2 min_ans=0
tc small_lr-14 gen_random n=199996 maxL=1 maxR=1 min_ans=0
tc small_lr-15 gen_random n=200000 maxL=2 maxR=2 min_ans=1
tc small_lr-16 gen_random n=200000 maxL=2 maxR=2 min_ans=5
tc small_lr-17 gen_random n=200000 maxL=2 maxR=2 min_ans=10
tc small_lr-18 gen_random n=200000 maxL=2 maxR=2 min_ans=107
tc small_lr-19 gen_random n=200000 maxL=2 maxR=2 min_ans=314
tc small_lr-20 gen_random n=200000 maxL=2 maxR=2 min_ans=415
tc small_lr-21 gen_random n=200000 maxL=2 maxR=2 min_ans=5152
tc small_lr-22 gen_random n=200000 maxL=2 maxR=2 min_ans=61616
tc full-19 gen_random n=200000 maxL=2 maxR=2 min_ans=900


group group5 30
limits maxn=$MAXN maxval=$MAXVAL all_equal=0 r0=0
include_group group1
include_group group2
include_group group3
include_group group4
tc full-ranges-large-01 gen_random n=200000 maxL=200000 maxR=200000 min_ans=-1
tc full-ranges-large-02 gen_random n=200000 maxL=200000 maxR=200000 min_ans=-2
tc full-ranges-large-03 gen_random n=199999 maxL=200000 maxR=200000 min_ans=-2

tc full-01 gen_random n=200000 maxL=1000000000 maxR=1000000000 min_ans=1
tc full-02 gen_random n=200000 maxL=200010 maxR=200010 min_ans=3
tc full-03 gen_random n=200000 maxL=200010 maxR=200010 min_ans=5
tc full-04 gen_random n=200000 maxL=1000000000 maxR=1000000000 min_ans=10
tc full-05 gen_random n=200000 maxL=200010 maxR=200010 min_ans=17
tc full-06 gen_random n=200000 maxL=200010 maxR=200010 min_ans=24
tc full-07 gen_random n=200000 maxL=200010 maxR=200010 min_ans=36
tc full-08 gen_random n=200000 maxL=50000000 maxR=50000000 min_ans=52
tc full-09 gen_random n=200000 maxL=20 maxR=30 min_ans=70
tc full-10 gen_random n=200000 maxL=30 maxR=20 min_ans=70
tc full-11 gen_random n=200000 maxL=200010 maxR=200010 min_ans=123
tc full-12 gen_random n=200000 maxL=5000 maxR=5000 min_ans=206
tc full-13 gen_random n=200000 maxL=200010 maxR=200010 min_ans=455
tc full-14 gen_random n=200000 maxL=200010 maxR=200010 min_ans=513
tc full-15 gen_random n=200000 maxL=20 maxR=20 min_ans=513
tc full-16 gen_random n=200000 maxL=1000 maxR=1000 min_ans=514
tc full-17 gen_random n=200000 maxL=1000000000 maxR=1000000000 min_ans=515
tc full-18 gen_random n=200000 maxL=200010 maxR=200010 min_ans=775
tc full-19
tc full-20 gen_random n=200000 maxL=1000000000 maxR=1000000000 min_ans=10000
tc full-21 gen_random n=200000 maxL=200010 maxR=200010 min_ans=1509
tc full-22 gen_random n=200000 maxL=200010 maxR=200010 min_ans=3515
tc full-23 gen_random n=200000 maxL=7 maxR=7 min_ans=6156
tc full-24 gen_random n=200000 maxL=7 maxR=515151 min_ans=6156
tc full-25 gen_random n=200000 maxL=200010 maxR=200010 min_ans=12311
tc full-26 gen_random n=200000 maxL=200010 maxR=200010 min_ans=24144
tc full-27 gen_random n=200000 maxL=100000 maxR=2 min_ans=23133
tc full-28 gen_random n=200000 maxL=200010 maxR=200010 min_ans=123141
tc full-29 gen_random n=200000 maxL=200010 maxR=200010 min_ans=165155
tc full-30 gen_random n=200000 maxL=200010 maxR=200010 min_ans=199589
