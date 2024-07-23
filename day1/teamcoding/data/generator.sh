#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

compile gen.py
compile gen_special_cases.py

use_solution charlotte_split.cpp

N=100000

samplegroup
limits maxn=10 maxk=10 maxc=10 graph=tree
sample 1
sample 2
sample 3
sample 4

group group1 12
limits maxn=$N maxk=$N maxc=$N graph=path
tc 1
tc singleton gen_special_cases n=1 mode=singleton
tc path-1 gen n=5 k=2 mode=path
tc path-2 gen n=10 mode=path
tc path-3 gen n=15 mode=path
tc path-4 gen n=7 mode=path
tc path-5 gen n=8 mode=path
tc path-6 gen n=100 mode=path
tc path-7 gen n=2000 mode=path
tc path-8 gen n=$N mode=path
tc path-bip-small gen n=100 k=2 mode=path
tc path-bip-mid gen n=2000 k=2 mode=path
tc path-bip-long gen n=$N k=2 mode=path
tc path-col-small gen n=100 k=100 mode=path
tc path-col-mid gen n=2000 k=2000 mode=path
tc path-col-long gen n=$N k=$N mode=path

group group2 19
limits maxn=$N maxk=2 maxc=$N graph=tree
tc 2
tc singleton
tc path-1
tc path-bip-small
tc path-bip-mid
tc path-bip-long
tc depth-two-small gen_special_cases n=100 mode=depth_two
tc depth-two-mid gen_special_cases n=2000 mode=depth_two
tc depth-two-large gen_special_cases n=$N mode=depth_two
tc caterpillar-small gen_special_cases n=100 mode=caterpillar colorful=0
tc caterpillar-mid gen_special_cases n=2000 mode=caterpillar colorful=0
tc caterpillar-large gen_special_cases n=$N mode=caterpillar colorful=0
tc almost_star_bip gen_special_cases n=$N mode=almoststar_bip
tc bip-1 gen n=10 k=2 mode=bipartite
tc bip-3 gen n=100 k=2 mode=bipartite
tc bip-5 gen n=$N k=2 mode=bipartite
tc bip-6 gen n=$N k=2 mode=bipartite
tc bip-8 gen n=100 k=2 mode=bipartite_special
tc bip-8-2 gen n=2000 k=2 mode=bipartite_special
tc bip-9 gen n=$N k=2 mode=bipartite_special
tc bip-10 gen n=$N k=2 mode=bipartite_special
tc bip-11 gen n=$N k=2 mode=bipartite_special

group group3 27
limits maxn=$N maxk=$N maxc=10 graph=tree
include_group sample
tc singleton
tc path-1
tc path-2
tc path-3
tc path-4
tc path-5
tc sub3-1 gen n=12 mode=random
tc sub3-2 gen n=11 mode=random
tc sub3-3 gen n=2000 mode=light-random
tc sub3-4 gen n=2000 mode=light-random tree=deep
tc sub3-5 gen n=2000 mode=light-random tree=shallow
tc sub3-6 gen n=$N mode=light-random
tc sub3-7 gen n=$N mode=light-random tree=deep
tc sub3-8 gen n=$N mode=light-random tree=deeper
tc sub3-9 gen n=$N mode=light-random tree=shallow
tc sub3-10 gen n=$N mode=light-random tree=shallower
tc long-almostpath gen n=$N mode=almostpath
tc three-paths-large gen_special_cases n=$N mode=three_paths
tc three-paths-mid gen_special_cases n=2000 mode=three_paths
# the tc below passes the validator for this group (by accident?), so I add them here
tc path-6
tc path-8
tc path-col-small
tc path-col-mid
tc path-col-long
tc bip-1
tc deeper-mid gen n=2000 mode=random tree=deeper
tc random-mid gen n=2000 mode=random tree=random
tc sub4-1 gen n=2000 mode=random
tc sub5-2 gen n=10000 mode=random
tc sub5-3 gen n=$N mode=random tree=random
tc sub5-4 gen n=$N mode=random tree=deep
tc sub5-5 gen n=$N mode=random tree=deeper
tc sub5-6 gen n=$N mode=random tree=shallow

group group4 23
limits maxn=2000 maxk=2000 maxc=2000 graph=tree
include_group sample
tc depth-two-mid
tc bip-8-2
tc caterpillar-mid
tc path-bip-mid
tc path-col-mid
tc singleton
tc path-1
tc path-2
tc path-3
tc path-4
tc path-5
tc path-6
tc path-7
tc path-bip-small
tc path-col-small
tc depth-two-small
tc caterpillar-small
tc bip-1
tc bip-3
tc bip-8
tc sub3-1
tc sub3-2
tc sub3-3
tc sub3-4
tc sub3-5
tc caterpillar-col-mid gen_special_cases n=2000 mode=caterpillar colorful=1
tc three-paths-mid
tc sqrt-paths-mid gen_special_cases n=2000 mode=sqrt_paths
tc many-mid gen n=2000 mode=many
tc tie-mid gen n=2000 mode=tie
tc reg-mid-1 gen n=2000 mode=regular r=3
tc reg-mid-2 gen n=2000 mode=regular r=100
tc deeper-mid
tc shallow-mid gen n=2000 mode=random tree=shallow
tc random-mid
tc sub4-1
tc bib-med gen n=2000 mode=bipartite

group group5 19
limits maxn=$N maxk=$N maxc=$N graph=tree
include_group group1
include_group group2
include_group group3
include_group group4
tc caterpillar-col-long gen_special_cases n=$N mode=caterpillar colorful=1
tc sqrt-paths-large gen_special_cases n=$N mode=sqrt_paths
tc sub5-2
tc sub5-3
tc sub5-4
tc sub5-5
tc sub5-6
tc sub5-7 gen n=$N mode=random tree=shallower
tc bib5-1 gen n=10000 mode=bipartite
tc bib5-2 gen n=$N mode=bipartite
tc reg5-1 gen n=10000 mode=regular r=5
tc reg5-2 gen n=10000 mode=regular r=1000
tc reg5-3 gen n=10000 mode=regular r=5
tc reg5-4 gen n=10000 mode=regular r=1000
tc reg5-5 gen n=$N mode=regular r=5
tc reg5-6 gen n=$N mode=regular r=1000
tc reg5-7 gen n=$N mode=regular r=5
tc reg5-8 gen n=$N mode=regular r=1000
tc reg5-9 gen n=$N mode=regular r=50
tc reg5-10 gen n=$N mode=regular r=10000
tc large-many1 gen n=10000 mode=many
tc large-many2 gen n=$N mode=many
tc large-tie gen n=$N mode=tie
