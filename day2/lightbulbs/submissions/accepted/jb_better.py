#!/usr/bin/python3
import random
random.seed(23)

n = int(input())

def query(q, t='?'):
  print(t)
  grid = [['0' for i in range(n)] for i in range(n)]
  for r,c in q:
    grid[r][c] = '1'
  for row in grid:
    print(" ".join(row))
  if t == '!':
    exit()
  return int(input())

know_h, know_v = [], []
rows, cols = [1]*n, [1]*n
cand = []
possible = [[]]

def sim(q, guess, h):
  v = [[0]*n, [0]*n]
  for i in q:
    v[1-guess[i]][cand[i][1-guess[i]]] = 1
  if h:
    for r,c in know_h:
      v[0][r] = 1
  else:
    for r,c in know_v:
      v[1][c] = 1
  r, c = sum(v[0]), sum(v[1])
  return (r+c)*n - r*c

while True:
  to_rem = []
  for i in range(len(cand)):
    have = [p[i] for p in possible]
    if sum(have) == 0:
      if cols[cand[i][1]]:
        cols[cand[i][1]] = 0
        know_v.append(cand[i])
      to_rem.append(i)
    elif sum(have) == len(have):
      if rows[cand[i][0]]:
        rows[cand[i][0]] = 0
        know_h.append(cand[i])
      to_rem.append(i)
  for i in reversed(to_rem):
    cand.pop(i)
    for p in possible:
      p.pop(i)
  if len(know_h) == n:
    query(know_h,'!')
  if len(know_v) == n:
    query(know_v,'!')

  while len(possible) < 1000 and len(cand) < sum(rows)+sum(cols):
    r = random.choice([i for i in range(n) if rows[i]])
    c = random.choice([i for i in range(n) if cols[i]])
    if (r,c) in cand:
      break
    cand.append((r,c))
    npossible = []
    for p in possible:
      npossible.append(p+[0])
      npossible.append(p+[1])
    possible = npossible

  best_q, best_val, best_h = [], 1e9, 0
  for prob in [90,80,70,60,50,50,30,20]:
    qi = []
    for i in range(len(cand)):
      if random.randint(0,100) < prob:
        qi.append(i)
    h = random.randint(0,1)
    cnts = [0]*(n*n+1)
    for p in possible:
      cnts[sim(qi,p,h)] += 1
    if max(cnts) < best_val:
      best_val = max(cnts)
      best_q = qi
      best_h = h

  k = query([cand[i] for i in best_q] + (know_h if best_h else know_v))
  possible = [p for p in possible if k == sim(best_q,p,best_h)]
  assert(len(possible))
