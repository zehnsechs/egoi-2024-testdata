import random
import sys


def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default


def gen_list(n, minx, maxx):
    return [random.randint(minx, maxx) for _ in range(n)]


random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
minx = int(cmdlinearg('minx'))
maxx = int(cmdlinearg('maxx'))
miny = int(cmdlinearg('miny'))
maxy = int(cmdlinearg('maxy'))

while True:
    x = gen_list(n, minx, maxx)
    y = gen_list(n, miny, maxy)
    if sum(y) <= sum(x):
        break

print(n)
print(*x)
print(*y)
