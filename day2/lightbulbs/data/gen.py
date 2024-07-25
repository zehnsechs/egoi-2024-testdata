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

print(n)
grid = [['?']*n for _ in range(n)]

if mode == 'random':
    prob = float(cmdlinearg('prob'))
    for i in range(n):
        for j in range(n):
            if random.random() < prob:
                grid[i][j] = 'v'
            else:
                grid[i][j] = 'h'
elif mode == 'checkers':
    dimx = int(cmdlinearg('dimx',1))
    dimy = int(cmdlinearg('dimy',1))
    for i in range(n):
        for j in range(n):
            if (i%(2*dimx)<dimx) == (j%(2*dimy)<dimy):
                grid[i][j] = 'v'
            else:
                grid[i][j] = 'h'
elif mode == 'diagonal':
    for i in range(n):
        for j in range(n):
            if i == j:
                grid[i][j] = 'v'
            else:
                grid[i][j] = 'h'
elif mode == 'antidiagonal':
    for i in range(n):
        for j in range(n):
            if i+j==n-1:
                grid[i][j] = 'v'
            else:
                grid[i][j] = 'h'
elif mode == 'circle':
    cx = int(cmdlinearg('cx'))
    cy = int(cmdlinearg('cy'))
    rad = int(cmdlinearg('rad'))
    for i in range(n):
        for j in range(n):
            if rad <= math.sqrt((i-cx)*(i-cx)+(j-cy)*(j-cy)) <= rad+1.5:
                grid[i][j] = 'v'
            else:
                grid[i][j] = 'h'
elif mode == 'concentric':
    cx = int(cmdlinearg('cx'))
    cy = int(cmdlinearg('cy'))
    for i in range(n):
        for j in range(n):
            if math.sqrt((i-cx)*(i-cx)+(j-cy)*(j-cy))%3 < 1.5:
                grid[i][j] = 'v'
            else:
                grid[i][j] = 'h'
elif mode == 'rays':
    cx = int(cmdlinearg('cx'))
    cy = int(cmdlinearg('cy'))
    numrays = int(cmdlinearg('numrays'))
    for i in range(n):
        for j in range(n):
            if (numrays*(math.atan2(i-cx,j-cy)+10))%2 < 1:
                grid[i][j] = 'v'
            else:
                grid[i][j] = 'h'
elif mode == 'split':
    prob = float(cmdlinearg('prob'))
    anti = float(cmdlinearg('anti',0))
    for i in range(n):
        for j in range(n):
            (v,h) = ('v','h') if (anti==0 and i>j) or (anti==1 and i>(n-j-1)) else ('h','v')
            if random.random() < prob:
                grid[i][j] = v
            else:
                grid[i][j] = h
else:
    assert(False)

force_row = int(cmdlinearg('force_row',-1))
force_col = int(cmdlinearg('force_col',-1))
if force_row != -1:
    for i in range(n):
        grid[force_row][i] = 'v'
if force_col != -1:
    for i in range(n):
        grid[i][force_col] = 'h'
swap = int(cmdlinearg('swap',0))
if swap==1:
    for i in range(n):
        for j in range(n):
            grid[i][j] = chr(ord(grid[i][j])^ord('h')^ord('v'))

for i in range(n):
    print("".join(grid[i]))
