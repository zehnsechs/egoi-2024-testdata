#!/bin/python3

qq = 0

def query(q, t='?'):
  global qq
  qq += 1

  print(t)
  grid = [['0' for i in range(n)] for i in range(n)]
  for r,c in q:
    grid[r-1][c-1] = '1'
  for row in grid:
    print("".join(row))
  if t == '!':
    exit()
  return int(input())

n = int(input())

h, v = [], []

a = query([(1,1), (1,2), (1,3)])
if a == 3*n: v.append((1,1))
elif a == n: h.append((1,1))
elif a-query([(1,2), (1,3)]) == n-1: v.append((1,1))
else: h.append((1,1))

while len(h) < n and len(v) < n:
  p = (1+len(h), 1+len(v))
  (hh,vv) = (h,v) if len(h) else (v,h)
  if query(hh+[p]) == (len(hh)+1)*n:
    hh.append(p)
  else:
    vv.append(p)

while qq < 2000:
  ss = 0
  q = []
  for i in range(n):
    for j in range(n):
      ss = (1231231*ss + 121773)%1000000007
      if ss%2:
        q.append([i,j])
  ss += query(q)

query(h if len(h) == n else v,'!')