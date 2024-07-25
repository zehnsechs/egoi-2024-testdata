#!/usr/bin/env bash
# We use a patched version of gen.sh that puts test groups in a wrapper
# subdirectory with a point-rescaling grader, to allow Kattis to reuse case
# result between groups despite them having different max scores.
REQUIRE_SAMPLE_REUSE=0
. ./gen.sh  # ../../../testdata_tools/gen.sh

compile gen.py

#use_solution nils.cpp
use_solution jb.py

samplegroup
limits group=4
sample 1

group group1 10
limits group=0
tc n2 gen n=2 mode=path
tc star-small-0 gen n=3 mode=star shuffle=0
tc star-small-1 gen n=4 mode=star shuffle=0
tc star-0 gen n=99 mode=star shuffle=0
tc star-1 gen n=100 mode=star shuffle=0

group group2 13
limits group=1
tc n2
tc clique-2 gen n=3 mode=clique
tc clique-3 gen n=4 mode=clique
tc clique-4 gen n=10 mode=clique
tc clique-5 gen n=15 mode=clique
tc clique-6 gen n=30 mode=clique
tc clique-7 gen n=40 mode=clique
tc clique-8 gen n=50 mode=clique
tc clique-9 gen n=100 mode=clique

group group3 11
limits group=2
tc_manual ../manual_tests/sample.in
tc n2
tc path-2 gen n=4 mode=path
tc path-3 gen n=49 mode=path
tc path-4 gen n=99 mode=path
tc path-5 gen n=100 mode=path
tc path-6 gen n=64 mode=path

group group4 36
limits group=3
include_group group1
include_group group3
tc sample
tc n2
tc tree-1 gen n=5 mode=tree
tc tree-2 gen n=10 mode=tree
tc tree-3 gen n=11 mode=tree branch=2
tc tree-4 gen n=100 mode=tree
tc tree-6 gen n=100 mode=tree branch=2
tc tree-7 gen n=100 mode=tree branch=3
tc star-2 gen n=100 mode=star branch=50
tc star-3 gen n=100 mode=star branch=10
tc tree-8 gen n=100 mode=long-branch
tc tree-9 gen n=100 mode=long-branch branch=10
tc tree-10 gen n=100 mode=long-branch branch=3
tc caterpillar gen n=100 mode=caterpillar pathlen=50
tc broom gen n=100 mode=broom pathlen=50
tc star-path-star-1 gen n=100 mode=star-path-star pathlen=2
tc star-path-star-2 gen n=100 mode=star-path-star pathlen=30
tc_manual ../manual_tests/graph2.in
tc_manual ../manual_tests/tree-branch2.in
tc binary gen n=100 mode=binary
tc many-leaves-1 gen n=100 mode=many-leaves stem=5
tc many-leaves-2 gen n=100 mode=many-leaves stem=25
tc almost-path-1 gen n=100 mode=almost-path stem=98
tc almost-path-2 gen n=100 mode=almost-path stem=60
tc smalltree-4-1 gen n=4 mode=tree
tc smalltree-4-2 gen n=4 mode=tree
tc smalltree-5-1 gen n=5 mode=tree
tc smalltree-5-2 gen n=5 mode=tree
tc smalltree-6-1 gen n=6 mode=tree
tc smalltree-6-2 gen n=6 mode=tree
for A in {1..7}; do
	tc smalltree-7-$A gen n=7 mode=tree
	tc smalltree-8-$A gen n=8 mode=tree
done

group group5 30
limits group=4
include_group group2
include_group group3
include_group group4
tc random-1 gen n=10 m=20 mode=graph
tc random-2 gen n=10 m=20 branch=3 mode=graph
tc random-3 gen n=11 m=33 mode=graph
tc random-4 gen n=11 m=14 mode=graph
tc random-5 gen n=100 m=122 mode=graph branch=5
tc_manual ../manual_tests/graph1.in
tc dense-1 gen n=100 m=1 mode=dense
tc dense-2 gen n=100 m=2 mode=dense
tc dense-3 gen n=100 m=40 mode=dense
tc clique-stick-1 gen n=100 mode=clique-stick branch=10
tc clique-stick-2 gen n=100 mode=clique-stick branch=40
tc clique-stick-3 gen n=100 mode=clique-stick branch=80
tc clique-star-1 gen n=100 mode=clique-star branch=1 shuffle=0
tc clique-star-2 gen n=100 mode=clique-star branch=20 shuffle=0
tc dumbbell-1 gen n=100 mode=dumbbell pathlen=2
tc dumbbell-2 gen n=100 mode=dumbbell pathlen=30
tc dumbbell-3 gen n=100 mode=dumbbell pathlen=65 shuffle=0
tc cycle gen n=100 mode=cycle
tc bipartite gen n=100 m=7000 mode=bipartite
tc sunflower gen n=100 mode=sunflower
tc wheel gen n=100 mode=wheel
tc almost-star gen n=100 mode=star addextraedges=2
tc almost-tree gen n=100 mode=tree branch=2 addextraedges=10
tc star-of-cliques-4 gen n=100 mode=star-of-cliques numcliques=4
tc star-of-cliques-10 gen n=100 mode=star-of-cliques numcliques=10
tc star-of-cliques-25 gen n=100 mode=star-of-cliques numcliques=25
for A in {1..13,15,19,20}; do
	tc graph-small-rand-$A gen n=r10 m=r20 mode=graph2
done
