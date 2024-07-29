#!/usr/bin/python3

# should use <= 4*n many rounds

n, m = [int(x) for x in input().split()]
g = [[] for _ in range(n)]
adj = [[0]*n for _ in range(n)]
for i in range(m):
  x, y = [int(x) for x in input().split()]
  if x == y or adj[x][y]:
    continue
  g[x].append(y)
  g[y].append(x)
  adj[x][y] = adj[y][x] = 1

if not [x for x in range(n) if len(g[x]) < n-1]:
  q = n + (n%2)
  circ, col = [i for i in range(q)], [0]*q
  print(2*(q-1))
  for _ in range(q-1):
    for i in range(q//2):
      col[circ[i]] = col[circ[-1-i]] = i
    print(*col[:n])
    print(*col[:n])
    circ = [0] + circ[2:q] + [circ[1]]
  exit()

def go():
  for r in range(n):
    for x in range(n):
      for y in range(n):
        if r != x and r != y and x != y:
          if adj[r][x] == 1 and adj[r][y] == 1 and adj[x][y] == 0:
            g[r] = [x,y] + g[r]
            return r
root = go()

assert(root != -1)

childs = [[] for _ in range(n)]
par = [-1]*n
par[root] = -2
queue = [root]
for x in queue:
  for y in g[x]:
    if par[y] == -1:
      childs[x].append(y)
      par[y] = x
      queue.append(y)

for x in childs[root]:
  bad = [y for y in childs[root] if adj[x][y]]
  for y in bad:
    childs[root].remove(y)
    childs[x].append(y)
    par[y] = x

# in our tree, childs[roots] form an independent set of size >= 2

ans, free = [], [0]*n
free[root] = 1
while sum(free) < n-1:
  col = [i+1 for i in range(n)]
  active, nfree = free.copy(), free.copy()

  if free[root]:
    active[root] = 1e9
  else: # need to make root free for next round
    best, b = 1e9, -1
    for x in childs[root]:
      pending = sum([not free[y] for y in childs[x]])
      if free[x] and pending < best:
        best, b = pending, x
    active[b] = 0
    col[b] = col[root]
    nfree[b], nfree[root] = 0, 1

  for x in range(n):
    if x != root and not free[x] and active[par[x]] >= 1:
      col[x] = col[par[x]]
      active[par[x]] -= 1
      nfree[x], nfree[par[x]] = 1, 0

  ans.append(col)
  free = nfree

assert(not free[root])

def dfs(x):
  for y in childs[x]:
    col = [i+1 for i in range(n)]
    col[y] = col[x]
    ans.append(col)
    dfs(y)
    ans.append(col)
dfs(root)

print(len(ans))
for col in ans:
  print(*col)
