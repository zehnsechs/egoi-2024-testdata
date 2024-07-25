#!/usr/bin/env python3

import sys
import random
import math

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

def int2(s):
    if s.startswith("r"):
        return random.randint(2, int(s[1:]))
    return int(s)

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int2(cmdlinearg('n'))
m = int2(cmdlinearg('m', "0"))
branch = int(cmdlinearg('branch', 101))
shuffle = int(cmdlinearg('shuffle', 1))
mode = cmdlinearg('mode')

edges = []
edge_set = set()

if mode == "clique":
    for i in range(n):
        for j in range(i+1,n):
            edges.append((i, j))

elif mode == "tree":
    for i in range(1, n):
        start = max(0, i-branch)
        p = random.randint(start, i-1)
        edges.append((i, p))

elif mode == "graph":
    for i in range(1, n):
        start = max(0, i-branch)
        p = random.randint(start, i-1)
        edges.append((i, p))
        edge_set.add((i,p))
        edge_set.add((p,i))

    fail = 0
    while len(edges) < m and fail < 10:
        u = random.randrange(0, n-1)
        v = random.randint(u+1, min(n-1, u+branch))
        if (u, v) not in edge_set:
            edges.append((u, v))
            edge_set.add((u, v))
            edge_set.add((v, u))
            fail = 0
        else:
            fail += 1

elif mode == "graph2":
    for i in range(1, n):
        start = max(0, i-branch)
        p = random.randint(start, i-1)
        edges.append((i, p))
        edge_set.add((i,p))
        edge_set.add((p,i))

    fail = 0
    while len(edges) < m and fail < 10:
        u = random.randint(0, n-1)
        v = random.randint(0, n-1)
        if u == v:
            continue
        if (u, v) not in edge_set:
            edges.append((u, v))
            edge_set.add((u, v))
            edge_set.add((v, u))
            fail = 0
        else:
            fail += 1

elif mode == "dense":
    remove = set()
    for _ in range(m):
        a = random.randrange(0, n)
        b = random.randrange(0, n)
        remove.add((a, b))
        remove.add((b, a))

    for i in range(n):
        for j in range(i):
            if (i,j) not in remove:
                edges.append((i, j))

elif mode == "clique-stick":
    branch = min(branch, n-1)
    ind = list(range(n))
    random.shuffle(ind)
    for i in range(n-branch):
        for j in range(i):
            edges.append((ind[i], ind[j]))
    for i in range(n-branch, n):
        edges.append((ind[i-1], ind[i]))

elif mode == "star":
    order = list(range(n))
    if shuffle:
        random.shuffle(order)
    for i in range(1,n):
        p = max(0, i - branch)
        edges.append((order[p], order[i]))

elif mode == "clique-star":
    for i in range(n-branch):
        for j in range(i):
            edges.append((i, j))
    for i in range(n-branch, n):
        edges.append((0, i))

elif mode == "long-branch":
    for i in range(1, n):
        start = max(0, i-branch)
        p = random.randint(start, i-1)
        if i >= n // 2:
            p = i-1
        edges.append((i, p))

elif mode == "path":
    for i in range(1, n):
        edges.append((i-1,i))
    shuffle = 0

elif mode == "caterpillar":
    pathlen = int(cmdlinearg('pathlen'))
    for i in range(pathlen):
        edges.append((i,i+1))
    for i in range(pathlen+1,n):
        edges.append((i,random.randint(0,pathlen)))

elif mode == "broom":
    pathlen = int(cmdlinearg('pathlen'))
    for i in range(pathlen):
        edges.append((i,i+1))
    for i in range(pathlen+1,n):
        edges.append((i,0))

elif mode == "star-path-star":
    pathlen = int(cmdlinearg('pathlen'))
    for i in range(pathlen):
        edges.append((i,i+1))
    r = (n+pathlen)//2
    for i in range(pathlen+1,r):
        edges.append((i,0))
    for i in range(r,n):
        edges.append((i,pathlen))

elif mode == "dumbbell":
    pathlen = int(cmdlinearg('pathlen'))
    for i in range(pathlen):
        edges.append((i,i+1))
    r = (n+pathlen)//2
    for i in range(pathlen+1,r):
        edges.append((i,0))
        for j in range(i+1,r):
            edges.append((i,j))
    for i in range(r,n):
        edges.append((i,pathlen))
        for j in range(i+1,n):
            edges.append((i,j))

elif mode == "cycle":
    for i in range(n):
        edges.append((i,(i+1)%n))

elif mode == "binary":
    for i in range(1, n):
        edges.append(((i-1)//2, i))

elif mode == "many-leaves":
    stem = int(cmdlinearg('stem', 100))
    stem = min(stem, n)
    for i in range(1, stem):
        start = max(0, i-branch)
        p = random.randint(start, i-1)
        edges.append((i, p))
    for i in range(stem, n):
        p = random.randint(0, stem)
        edges.append((i, p))

elif mode == "almost-path":
    stem = int(cmdlinearg('stem', 100))
    stem = min(stem, n)
    for i in range(1, stem):
        edges.append((i-1, i))
    for i in range(stem, n):
        start = max(0, i-branch)
        p = random.randint(start, i-1)
        edges.append((i, p))

elif mode == "bipartite":
    part1 = list(range(0,n//2))
    part2 = list(range(n//2,n))
    pairs = []
    for p1 in part1:
        for p2 in part2:
            pairs.append((p1,p2))

    random.shuffle(pairs)
    for i in range(m):
        if i >= len(pairs):
            break
        edges.append(pairs[i])

elif mode == "sunflower":
    x = 1
    while x < n:
        r = random.randint(1,random.randint(min(n-x,2), min(n-x,4)))
        for i in range(r):
            edges.append((x,0))
            if i > 0:
                edges.append((x-1,x))
            x += 1

elif mode == "wheel":
    for x in range(0,n-1):
        edges.append((x,n-1))
        edges.append((x,(x+1)%(n-1)))

elif mode == "star-of-cliques":
    num_cliques = int(cmdlinearg('numcliques'))
    assert n % num_cliques == 0, 'num_cliques must evenly divide n'
    clique_size = n // num_cliques
    assert clique_size >= 3

    for i in range(num_cliques):
        fr = i * clique_size
        for j in range(fr, fr + clique_size):
            for k in range(fr, j):
                edges.append((j, k))
        if i > 0:
            edges.append([random.randrange(0, clique_size), random.randrange(fr, fr+clique_size)])

else:
    assert(False)

for i in range(int(cmdlinearg('addextraedges', 0))):
    x, y = 0, 0
    while x == y or (x,y) in edges or (y,x) in edges:
        x = random.randint(0,n-1)
        y = random.randint(0,n-1)
    edges.append((x,y))

if shuffle == 1:
    random.shuffle(edges)
    perm = list(range(n))
    #random.shuffle(perm)
    edges = [(perm[u],perm[v]) for (u,v) in edges]

print(n,len(edges))
for u,v in edges:
    print(u,v)

