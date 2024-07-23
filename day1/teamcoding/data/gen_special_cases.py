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

par = [-1]*n
col = [-1]*n

k = -1

if mode == "singleton":
  col[0] = 0
  k=1
  assert(n == 1)
elif mode == "three_paths":
  col[0] = 0
  x, y, z = 0, 0, 0
  nxt = 1
  nxt_col = 1
  while nxt+5 <= n:
    a, b, c = nxt, nxt+1, nxt+2
    nxt += 3
    par[a], par[b], par[c] = x, y, z
    col[a] = col[b] = col[c] = nxt_col
    nxt_col += 1
    x, y, z = a, b, c
  col[x], col[y], col[z] = nxt_col, nxt_col+1, nxt_col+2
  nxt_col += 3
  a, b = nxt, nxt+1
  nxt += 2
  par[a] = y
  par[b] = z
  col[a] = col[z]
  col[b] = col[x]
  n = nxt
  k = nxt_col
elif mode == "depth_two":
  m = (n-1)//2
  col[0] = 0
  for i in range(m):
    a, b = 2*i+1, 2*i+2
    par[a], par[b] = 0, a
    col[a] = col[b] = 1
  n = 2*m+1
  k = 2
elif mode == "caterpillar":
  colorful = int(cmdlinearg('colorful'))
  m = (n-2)//2
  col[0] = 0
  spine = 0
  legs = []
  for i in range(m):
    a, b = 2*i+2, 2*i+1
    par[a], par[b] = spine, a
    spine = a
    col[a] = a if colorful else 0
    col[b] = 1
    legs.append(b)
  a = 2*m+1
  par[a] = legs[-2]
  col[a] = a if colorful else 0
  n = 2*m+2
  k = n if colorful else 2
elif mode == "sqrt_paths":
  m = int(math.sqrt(n-1))
  for i in range(m):
    for j in range(m):
      col[i*m+j+1] = (j+i)%m
      par[i*m+j+1] = max(0, (i-1)*m+j+1)
  for x in range(m*m+1, n):
    col[x] = random.randint(0,m-1);
    par[x] = 0
  k = m
elif mode=='almoststar_bip':
  k = 2
  col[0] = 0
  for i in range(1,n-11):
    col[i] = 1
    par[i] = 0
  col[n-11] = 0
  par[n-11] = 0
  for i in range(n-10,n-3):
    col[i] = 1
    par[i] = i-1
  col[n-9] = 0
  col[n-8] = 0

  col[n-3] = 0
  par[n-3] = n-12
  col[n-2] = 1
  par[n-2] = n-3
  col[n-1] = 1
  par[n-1] = n-2
else:
  assert(False)


# shuffle all vertex labels and colors
permutation = [i for i in range(1,n)]
random.shuffle(permutation)
permutation = [0] + permutation
col_permutation = [i for i in range(k)]
random.shuffle(col_permutation)
col2 = [-1]*n
par2 = [-1]*n
for i in range(n):
  col2[permutation[i]] = col_permutation[col[i]]
  par2[permutation[i]] = permutation[par[i]]

print(n,k)
print(*col2)
for i in range(1,n):
  print(par2[i])
