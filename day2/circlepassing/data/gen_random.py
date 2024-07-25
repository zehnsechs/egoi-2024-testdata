#!/usr/bin/env python3

import sys
import random
import math

MAXN = 500000000
MAXM = 500000
MAXQ = 20000

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

MAXN = int(cmdlinearg('maxn', MAXN))
MAXM = int(cmdlinearg('maxm', MAXM))

n = int(cmdlinearg('n', random.randint(2, MAXN)))
m = int(cmdlinearg('m', random.randint(1, min(n, MAXM))));
q = int(cmdlinearg('q', MAXQ));

b = min(int(cmdlinearg('b', -1)), n - 1);

mode = cmdlinearg('mode', '')

kids = set()

if mode == 'g1':
    print(n, 1, q)
    if b != -1:
        f = b
    else:
        f = random.randint(0, n - 1)
    print(f)
    for i in range(0, q):
        y = f
        while f == y:
            y = random.randrange(2 * n)
        print(f, y)
    exit()



if mode == 'm0':
    m = 0
elif mode == 'm1':
    m = 1

print(n, m, q)

if b != -1:
    kids.add(b)

while len(kids) < m:
    kids.add(random.randint(0, n - 1))

print(*sorted(kids))
for i in range(0, q):
    x = 0
    y = 0
    while x == y:
        x = random.randrange(2 * n)
        if mode == 'x0':
            x = 0
        y = random.randrange(2 * n)
    print(x, y)
