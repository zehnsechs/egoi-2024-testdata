#!/usr/bin/env bash
# We use a patched version of gen.sh that puts test groups in a wrapper
# subdirectory with a point-rescaling grader, to allow Kattis to reuse case
# result between groups despite them having different max scores.
. ./gen.sh  # ../../../testdata_tools/gen.sh

compile gen.py

use_solution ../../data/noop.py

N=500

samplegroup
limits n=100 mode=general
sample 1

group group1 10
limits n=2 mode=general
tc tiny-1 gen n=2 tape=01 mode=rev
tc id-1 gen n=2 tape=10 mode=id
tc tiny-2 gen n=2 tape=10 mode=rev
tc tiny-3 gen n=2 tape=00 mode=rev
tc tiny-4 gen n=2 tape=11 mode=rev
tc id-2 gen n=2 tape=01 mode=id
tc tiny-5 gen n=2 mode=rev
tc tiny-6 gen n=2 mode=rev
tc tiny-7 gen n=2 mode=rev
tc tiny-8 gen n=2 mode=rev
tc tiny-9 gen n=2 mode=rev
tc tiny-10 gen n=2 mode=rev
tc tiny-11 gen n=2 mode=rev

group group2 24
limits n=15 mode=general
include_group sample
include_group group1
tc rev-n3 gen n=3 mode=rev
tc smaller-3 gen n=4 mode=random
tc smaller-4 gen n=5 mode=random
tc small-1 gen n=15 mode=random
tc small-2 gen n=14 mode=random
tc small-3 gen n=15 mode=randcycle
tc small-4 gen n=14 mode=randcycle
tc small-5 gen n=14 mode=zigzag1
tc id-small gen n=15 mode=id
tc rot-1 gen n=3 mode=rot
tc tor-1 gen n=3 mode=tor

group group3 9
limits n=$N mode=rev
tc tiny-1
tc tiny-2
tc tiny-3
tc tiny-4
tc tiny-5
tc tiny-6
tc tiny-7
tc tiny-8
tc tiny-9
tc tiny-10
tc tiny-11
tc rev-n3
tc rev-1 gen n=$N mode=rev
tc rev-2 gen n=$((N-1)) mode=rev

group group4 13
limits n=$N mode=rot
tc tiny-1
tc tiny-2
tc tiny-3
tc tiny-4
tc tiny-5
tc tiny-6
tc tiny-7
tc tiny-8
tc tiny-9
tc tiny-10
tc tiny-11
tc rot-1
tc rot-2 gen n=$N mode=rot
tc rot-3 gen n=$((N-1)) mode=rot

group group5 13
limits n=$N mode=tor
tc tiny-1
tc tiny-2
tc tiny-3
tc tiny-4
tc tiny-5
tc tiny-6
tc tiny-7
tc tiny-8
tc tiny-9
tc tiny-10
tc tiny-11
tc tor-1
tc smaller-4
tc tor-2 gen n=$N mode=tor
tc tor-3 gen n=$((N-1)) mode=tor

group group6 31
limits n=$N mode=general
include_group group2
include_group group3
include_group group4
include_group group5
tc large-1 gen n=$N mode=random
tc large-2 gen n=$((N-1)) mode=random
tc large-3 gen n=$N mode=randcycle
tc large-4 gen n=$((N-1)) mode=randcycle
tc large-5 gen n=$N mode=zigzag1
tc large-6 gen n=$N mode=zigzag2
tc large-7 gen n=$N mode=rec1
tc large-8 gen n=$N mode=rec2
