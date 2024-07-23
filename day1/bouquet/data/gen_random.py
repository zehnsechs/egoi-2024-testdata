#!/usr/bin/env python3

import sys
import random
import math

MAXN = 200000

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n', random.randint(1, MAXN)))
maxL = int(cmdlinearg('maxL', random.randint(0, n)));
maxR = int(cmdlinearg('maxR', random.randint(0, n)));
min_ans = int(cmdlinearg('min_ans', random.randint(0, n)));

maxL = min(maxL, n)
maxR = min(maxR, n)

mode = cmdlinearg('mode', '')

print(n)
if mode == 'lr':
    l = random.randint(0, maxL)
    r = l
    for i in range(0, n):
        print(str(l) + ' ' + str(r))
elif min_ans == -1:
    for i in range(0, n):
        l = 0
        r = n - 1 - i
        print(str(l) + ' ' + str(r))
elif min_ans == -2:
    for i in range(0, n):
        l = random.randint(0, min(6, n))
        r = random.randint(max(0, n - 1 - i - 6), n - 1 - i)
        print(str(l) + ' ' + str(r))
elif min_ans != 0:
    arr = []
    for i in range(0, n):
        arr.append(i)
    random.shuffle(arr)
    for i in range(0, n - min_ans):
        arr.pop()
    contained = {}
    for i in range(0, min_ans):
        contained[arr[i]] = 1;
    ls = []
    rs = []
    vals = []
    for i in range(0, n):
        if i in contained:
            vals.append(i)
            ls.append(0)
            rs.append(0)
        else:
            ls.append(random.randint(0, maxL))
            rs.append(random.randint(0, maxR))
    for i in range(0, min_ans):
        if i > 0:
            ls[vals[i]] = random.randint(0, min(vals[i] - vals[i - 1] - 1, maxL))
        else :
            ls[vals[i]] = random.randint(0, maxL)
        
        if i + 1 < min_ans:
            rs[vals[i]] = random.randint(0, min(maxR, vals[i + 1] - vals[i] - 1))
        else:
            rs[vals[i]] = random.randint(0, maxR)
    
    for i in range(0, n):
        print(str(ls[i]) + ' ' + str(rs[i]))
else:
    for i in range(0, n):
        l = random.randint(0, maxL)
        r = random.randint(0, maxR)
        if mode == 'lr':
            l = r
        print(str(l) + ' ' + str(r))
