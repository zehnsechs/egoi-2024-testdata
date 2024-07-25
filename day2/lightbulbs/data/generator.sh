#!/usr/bin/env bash
#. ../../../testdata_tools/gen.sh
. gen.sh

compile gen.py

use_solution ../../data/empty.sh # empty .ans files

samplegroup
limits maxn=5
sample 1

group group1 11 lamps_small
limits maxn=3
tc tiny_all_h gen n=3 mode=random prob=0
tc tiny_all_v gen n=3 mode=random prob=1
tc tiny_rand4 gen n=3 mode=random prob=0.4
tc tiny_rand45 gen n=3 mode=random prob=0.45
tc tiny_rand5 gen n=3 mode=random prob=0.5
tc tiny_rand55 gen n=3 mode=random prob=0.55
tc tiny_rand6 gen n=3 mode=random prob=0.6
tc tiny_unique_row0 gen n=3 mode=random prob=0 force_row=0
tc tiny_unique_col0 gen n=3 mode=random prob=1 force_col=0
tc tiny_checkers1 gen n=3 mode=checkers
tc tiny_checkers2 gen n=3 mode=checkers swap=1
tc tiny_checkers3 gen n=3 mode=checkers dimx=2 dimy=2
tc tiny_checkers4 gen n=3 mode=checkers dimy=2 swap=1
tc tiny_diagonal1 gen n=3 mode=diagonal
tc tiny_diagonal2 gen n=3 mode=diagonal swap=1
tc tiny_diagonal3 gen n=3 mode=antidiagonal
tc tiny_diagonal4 gen n=3 mode=antidiagonal swap=1

group group2 11 lamps_small
limits maxn=10
include_group sample
include_group group1
tc small_all_h gen n=10 mode=random prob=0
tc small_all_v gen n=10 mode=random prob=1
tc small_rand1 gen n=10 mode=random prob=0.1
tc small_rand2 gen n=10 mode=random prob=0.2
tc small_rand3 gen n=10 mode=random prob=0.3
tc small_rand4 gen n=10 mode=random prob=0.4
tc small_rand45 gen n=8 mode=random prob=0.45
tc small_rand5 gen n=10 mode=random prob=0.5
tc small_rand55 gen n=9 mode=random prob=0.55
tc small_rand6 gen n=10 mode=random prob=0.6
tc small_rand7 gen n=10 mode=random prob=0.7
tc small_rand8 gen n=10 mode=random prob=0.8
tc small_rand9 gen n=10 mode=random prob=0.9
tc small_unique_row0 gen n=10 mode=random prob=0 force_row=0
tc small_unique_row3 gen n=10 mode=random prob=0 force_row=3
tc small_unique_row5 gen n=10 mode=random prob=0 force_row=5
tc small_unique_col0 gen n=10 mode=random prob=1 force_col=0
tc small_unique_col1 gen n=10 mode=random prob=1 force_col=1
tc small_unique_col9 gen n=10 mode=random prob=1 force_col=9
tc small_almost_unique_row gen n=10 mode=random prob=0.1 force_row=8
tc small_almost_unique_col gen n=10 mode=random prob=0.9 force_col=9
tc small_unique_row_fake gen n=10 mode=random prob=0 force_row=4 force_col=6
tc small_checkers1 gen n=10 mode=checkers
tc small_checkers2 gen n=10 mode=checkers swap=1
tc small_checkers3 gen n=10 mode=checkers dimx=2 dimy=2
tc small_checkers4 gen n=10 mode=checkers dimx=3 dimy=5 swap=1
tc small_diagonal1 gen n=10 mode=diagonal
tc small_diagonal2 gen n=10 mode=diagonal antidiagonal=1 swap=1
tc small_diagonal3 gen n=9 mode=diagonal swap=1
tc small_diagonal4 gen n=9 mode=diagonal antidiagonal=1
tc small_diagonal5 gen n=8 mode=diagonal antidiagonal=1 swap=1
tc small_diagonal6 gen n=8 mode=diagonal
tc small_diagonal7 gen n=7 mode=diagonal swap=1
tc small_diagonal8 gen n=7 mode=diagonal antidiagonal=1
tc small_circle gen n=10 mode=circle cx=5 cy=4 rad=5
tc small_quartercircle gen n=10 mode=circle cx=10 cy=0 rad=10
tc small_concentric gen n=10 mode=concentric cx=3 cy=5
tc small_rays1 gen n=10 mode=rays cx=3 cy=5 numrays=5
tc small_rays2 gen n=10 mode=rays cx=-2 cy=-2 numrays=30
tc small_split1 gen n=10 mode=split prob=0.08
tc small_split2 gen n=10 mode=split prob=0.7 anti=1

group group3 78 lamps_scoring
limits maxn=100
include_group group2
tc all_h gen n=100 mode=random prob=0
tc all_v gen n=100 mode=random prob=1
tc rand1 gen n=100 mode=random prob=0.1
tc rand2 gen n=100 mode=random prob=0.2
tc rand3 gen n=100 mode=random prob=0.3
tc rand4 gen n=100 mode=random prob=0.4
tc rand45 gen n=100 mode=random prob=0.45
tc rand5 gen n=100 mode=random prob=0.5
tc rand55 gen n=100 mode=random prob=0.55
tc rand6 gen n=100 mode=random prob=0.6
tc rand7 gen n=100 mode=random prob=0.7
tc rand8 gen n=100 mode=random prob=0.8
tc rand9 gen n=100 mode=random prob=0.9
tc unique_row0 gen n=100 mode=random prob=0 force_row=0
tc unique_row32 gen n=100 mode=random prob=0 force_row=32
tc unique_row59 gen n=100 mode=random prob=0 force_row=59
tc unique_col0 gen n=100 mode=random prob=1 force_col=0
tc unique_col19 gen n=100 mode=random prob=1 force_col=19
tc unique_col59 gen n=100 mode=random prob=1 force_col=59
tc almost_unique_row gen n=100 mode=random prob=0.1 force_row=25
tc almost_unique_col gen n=100 mode=random prob=0.9 force_col=25
tc unique_row_fake gen n=100 mode=random prob=0 force_row=39 force_col=55
tc checkers1 gen n=100 mode=checkers
tc checkers2 gen n=100 mode=checkers swap=1
tc checkers3 gen n=100 mode=checkers dimx=2 dimy=2
tc checkers4 gen n=100 mode=checkers dimx=3 dimy=5 swap=1
tc checkers5 gen n=100 mode=checkers dimx=30 dimy=30 swap=1
tc diagonal1 gen n=100 mode=diagonal
tc diagonal2 gen n=100 mode=diagonal swap=1
tc diagonal3 gen n=100 mode=antidiagonal
tc diagonal4 gen n=100 mode=antidiagonal swap=1
tc circle gen n=100 mode=circle cx=50 cy=49 rad=50
tc quartercircle gen n=100 mode=circle cx=100 cy=0 rad=100
tc concentric gen n=100 mode=concentric cx=30 cy=53
tc rays1 gen n=100 mode=rays cx=30 cy=53 numrays=5
tc rays2 gen n=100 mode=rays cx=-5 cy=-5 numrays=30
tc split1 gen n=100 mode=split prob=0.08
tc split2 gen n=100 mode=split prob=0.7 anti=1
