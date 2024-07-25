import random
import sys


def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default


def partition_unbalanced(N, sumx):
    x = []
    for _ in range(N-1):
        i = random.randint(0, sumx)
        sumx -= i
        x.append(i)
    x.append(sumx)
    random.shuffle(x)
    return x


def partition_quite_balanced(N, sumx):
    avg = sumx // N
    assert avg > 0
    delta = min(avg, 5)
    while True:
        x = []
        for _ in range(N-1):
            x.append(avg + random.randint(-delta, delta))
        x.append(sumx - sum(x))
        if x[-1] >= 0:
            random.shuffle(x)
            return x


def partition_perfectly_balanced(N, sumx):
    N1 = sumx % N
    x = [sumx//N + 1] * N1 + [sumx//N] * (N-N1)
    random.shuffle(x)
    return x


def partition_left(N, sumx):
    return [sumx] + (N-1) * [0]


def partition_right(N, sumx):
    return (N-1) * [0] + [sumx]


def get_partitioner(name):
    if name == 'unbalanced':
        return partition_unbalanced
    elif name == 'quite_balanced':
        return partition_quite_balanced
    elif name == 'perfectly_balanced':
        return partition_perfectly_balanced
    elif name == 'left':
        return partition_left
    elif name == 'right':
        return partition_right


random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
sumx = int(cmdlinearg('sumx'))
sumy = int(cmdlinearg('sumy'))
x_partitioner = get_partitioner(cmdlinearg('xpart'))
y_partitioner = get_partitioner(cmdlinearg('ypart'))

x = x_partitioner(n, sumx)
y = y_partitioner(n, sumy)

print(n)
print(*x)
print(*y)
