#!/usr/bin/env python3

import sys
import random
import math

MAXN = 500000000

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

MAXN = int(cmdlinearg('maxn', MAXN))

n = int(cmdlinearg('n', random.randint(2, MAXN)))
if cmdlinearg('b', '') == 'last':
    b = n - 1
else:
    b = int(cmdlinearg('b', random.randint(0, n - 1)));

print(n, 1, 1)
print(b)
mode = cmdlinearg('mode', '')

if mode == 'direct':
    x = random.choice([0, n])
    y = n - x
elif mode == 'nopass':
    x = random.randint(0, n - 1)
    y = random.randint(- n // 2, x + n // 2)
elif mode ==  'pass':
    x = random.randint(0, n - 1)
    y = random.randint(x + n // 2 + 1, (3 * n) // 2 - 1)
elif mode == 'close':
    x = random.randint(0, n - 1)
    yopt = [i + off for i in [- n // 2, x + n // 2] for off in range(-2, 3)]
    y = random.choice(yopt)
elif mode == 'offsets':
    x = int(cmdlinearg('xoff')) + n*int(cmdlinearg('swap',0))
    y = int(cmdlinearg('yoff')) + n*(1-int(cmdlinearg('swap',0)))
else:
    x = random.randint(0, 2 * n - 1)
    y = random.randint(0, 2 * n - 1)

x = (x + b + 2 * n) % (2 * n)
y = (y + b + 2 * n) % (2 * n)

if x == y:
    x = (x + 1) % (2 * n)

if random.randint(0, 1) == 1:
    x = (x + n) % (2 * n)
    y = (y + n) % (2 * n)

a = [x, y]
random.shuffle(a)
print(a[0], a[1])
