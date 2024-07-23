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

def rec(n):
    # probably failed attempt at giving greedy left to right swaps a worse constant factor
    # but maybe it does something interesting?
    if n == 0:
        return []
    small = n // 3
    large = small * 2
    cyc = [n-1 - x for x in rec(large)]
    smalls = list(range(small))
    random.shuffle(smalls)
    out = []
    for i in range(small):
        out.append(smalls[i])
        out.append(cyc[2*i])
        out.append(cyc[2*i+1])
    for i in range(n % 3):
        out.append(small + i)
    return out

def genperm(n, mode):
    if mode == "random":
        perm = list(range(n))
        random.shuffle(perm)
        return perm
    if mode == "randcycle":
        cyc = list(range(n))
        random.shuffle(cyc)
        perm = [None] * n
        for i in range(n):
            perm[cyc[i]] = cyc[i - 1]
        return perm
    if mode == "zigzag1":
        assert n % 2 == 0
        lefts = list(range(n//2))
        rights = list(range(n//2, n))
        random.shuffle(lefts)
        random.shuffle(rights)
        li = [None] * n
        for i in range(n//2):
            li[lefts[i]] = rights[i]
            li[rights[i]] = lefts[(i + 1) % (n//2)]
        return li
    if mode == "zigzag2":
        lefts = list(range(n//2))
        rights = list(range(n//2, n))
        random.shuffle(lefts)
        random.shuffle(rights)
        return lefts + rights
    if mode == "rec1":
        return rec(n)
    if mode == "rec2":
        cyc = rec(n)
        perm = [None] * n
        for i in range(n):
            perm[cyc[i]] = cyc[i - 1]
        return perm
    if mode == "id":
        return list(range(n))
    if mode == "rot":
        return [(i + 1) % n for i in range(n)]
    if mode == "tor":
        return [(i - 1) % n for i in range(n)]
    if mode == "rev":
        return [n-1 - i for i in range(n)]
    assert False, f"bad mode {mode}"

def main():
    random.seed(int(cmdlinearg("seed", sys.argv[-1])))
    n = int(cmdlinearg("n"))
    mode = cmdlinearg("mode")
    tapestr = cmdlinearg("tape", "")

    perm = genperm(n, mode)
    if tapestr:
        tape = [int(c) for c in tapestr]
    else:
        tape = [random.randint(0, 1) for _ in range(n)]

    print(n)
    print(*perm)
    print(*tape)

main()
