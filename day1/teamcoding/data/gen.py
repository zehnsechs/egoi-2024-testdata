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

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
mode = cmdlinearg('mode')

k = int(cmdlinearg('k',random.randint(2,n)))

cols = [random.randrange(k) for _ in range(n)]
random.shuffle(cols)
debug_prints=True

def edge(u,v):
    return [u,v]

def gen_tree(n, mode):
    pars = [-1]
    depth = [0]
    for i in range(1, n):
        if mode == 'random':
            pred = random.randrange(i)
        elif mode == 'star':
            pred = 0
        elif mode in 'binary':
            pred = (i - 1) // 2
        elif mode == 'shallow':
            pred = int(random.uniform(0, i**0.2) ** 5)
        elif mode == 'shallower':
            pred = int(2**random.uniform(-2, math.log2(i)))
        elif mode == 'deep':
            pred = i-1 - int(random.uniform(0, i**0.1) ** 10)
        elif mode == 'deeper':
            if i < 4:
                pred = random.randrange(i)
            else:
                hi = math.log2(math.log2(i))
                pred = i - int(2 ** 2 ** min(random.uniform(-3, hi), random.uniform(-3, hi), random.uniform(-3, hi)))
        else:
            assert False, f"unknown mode {mode}"
        assert 0 <= pred < i
        pars.append(pred)
        depth.append(depth[pred] + 1)

    if debug_prints:
        print("max depth =", max(depth), file=sys.stderr)
    return pars

V = [i for i in range(1,n)]
random.shuffle(V)
V.insert(0,0)
   
if mode == 'random':
    tree_mode = cmdlinearg('tree','random')
    pars = gen_tree(n,tree_mode)
    E = [edge(V[i],V[pars[i]]) for i in range(1,n)]
if mode == 'almostpath':
    k = n//2+1
    cols = [(i%(n//2))+1 for i in range(n-n//2)]
    cols[0]=0
    E = [edge(V[i+1],V[i]) for i in range(n-1-n//2)]
    E.append(edge(V[n-n//2],0))
    E2 = [edge(V[i+1+n-n//2],V[i+n-n//2]) for i in range(n//2-1)]
    cols2 = [(i%k)+1 for i in range(n//2)]
    E = E+E2
    cols = cols+cols2
if mode == 'path':
    E = [edge(i+1,i) for i in range(n-1)]
if mode == 'bipartite_special':
    c2 = random.randint(0,1)
    c1 = 1-c2

    cols = [c1 for _ in range(n)]
    cols[0] = c2

    E = [edge(V[i],V[random.randint(0,i-2)]) for i in range(2,n)]
    E.append([V[1],V[0]])

    
    for _ in range(random.randint(n//10,n//3)):
        v = random.randint(1,n-1)
        cols[V[v]]=c2

if mode == 'bipartite':
    cols = [random.randint(0,1) for _ in range(n)]
    cols[0] = 2 
    if(k==2):
        cols[0]=random.randint(0,1)
    E = [edge(V[i],V[random.randint(0,i-2)]) for i in range(2,n)]
    E.append([V[1],V[0]])
if mode == 'regular':
    cols = [random.randint(0,5) for _ in range(n)]
    cols[0] = 2 
    r = int(cmdlinearg('r'))
    E = [edge(V[i],V[i//r]) for i in range(1,n)]
if mode == 'many':
    cols[0] = 0
    cols[V[1]] = 1
    cols[V[2]] = 2
    cols[V[3]] = 3
    col_c = [[3,3,3,3,3,3,2,2,2,1],
             [1,1,1,1,1,1,3,3,3,2],
             [2,2,2,2,2,2,1,1,1,3]]
    E=[edge(V[i],0) for i in range(1,4)] #this could also be a parameter
    for i in range(4,n):
        j = random.randint(0,i//3-1)*3 + i%3
        E.append(edge(V[i],V[j]))
        cols[V[i]] = random.choice(col_c[i%3])

if mode=='tie':
    V = [i for i in range(n)]
    #reference tree
    T = [0,0,2,5,0,1,5,6,6]
    cols = [0]
    E = []
    E.append(edge(V[1],V[0]))
    E.append(edge(V[2],V[0]))

    for i in range((n-3)//20):
        for _ in range(20):
            cols.append(random.choice([2*i+1]*6+[2*i+2]*4))
        for j in range(1,10):
            #print("i",i,"j",j, file=sys.stderr)
            E.append(edge(V[20*i+2*j+1],V[20*i+2*T[j-1]+1]))
            E.append(edge(V[20*i+2*j+2],V[20*i+2*T[j-1]+2]))
        E.append(edge(V[20*i+21],V[20*i+19]))
        E.append(edge(V[20*i+22],V[20*i+20]))
    n = len(cols)
    k = max(cols)+1
    
    E = E[:-2]


if mode=='light-random':
    if k <= n//8:
        k = n//8
    cols = random.sample([i for i in range(k)]*10, k=n)
    tree_mode = cmdlinearg('tree','random')
    pars = gen_tree(n,tree_mode)
    E = [edge(V[i],V[pars[i]]) for i in range(1,n)]


print(n,k)
print(*cols)
E.sort()
for i in range(len(E)):
    if not (E[i][0]==i+1):
        print(E,file=sys.stderr)
        assert(False)
    print(E[i][1])



