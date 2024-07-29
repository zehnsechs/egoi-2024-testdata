#!/usr/bin/python3

magic = 300 # ~ sqrt n

n, cols = [int(x) for x in input().split()]
color = [int(x) for x in input().split()]
g = [[] for _ in range(n)]
for i in range(n-1):
  x = i+1
  y = int(input())
  g[x].append(y)
  g[y].append(x)

dfs_in, dfs_out, level = [0]*n, [0]*n, [0]*n
ord, stack = [], [0]
while stack:
  x = stack.pop()
  if x < 0:
    dfs_out[~x] = len(ord)
    continue
  stack.append(~x)
  dfs_in[x] = len(ord)
  ord.append(x)
  for y in g[x]:
    g[y].remove(x)
    level[y] = level[x] + 1
    stack.append(y)

where = [[] for _ in range(cols)]
for x,c in enumerate(color):
  where[c].append(x)
ans  = [[0,0] for i in range(n)]

# light colors
below = [[1] for _ in range(n)]
for x in reversed(ord):
  for y in g[x]:
    below[y].append(0)
    if len(below[y]) > len(below[x]):
      below[x], below[y] = below[y], below[x]
    for i in range(len(below[y])):
      below[x][len(below[x])-i-1] += below[y][len(below[y])-i-1]

  if len(where[color[x]]) <= magic:
    for y in where[color[x]]:
      idx = level[y]-level[x]
      if 0 <= idx < len(below[x]):
        below[x][-1-idx] -= 1
        ans[x][0] += (below[x][-1-idx] >= 0)
        ans[x][1] += (dfs_in[x] <= dfs_in[y] < dfs_out[x])
    for y in where[color[x]]:
      idx = level[y]-level[x]
      if 0 <= idx < len(below[x]):
        below[x][-1-idx] += 1

# heavy colors
for c in range(len(where)):
  if len(where[c]) > magic:
    have, c_level = [0]*n, [0]*n
    for x in range(n):
      c_level[level[x]] += (color[x] == c)
    for x in ord:
      if color[x] == c:
        for i in range(dfs_in[x],dfs_out[x]):
          y = ord[i]
          lev = level[y]
          have[lev] += 1
          ans[x][0] += (have[lev] <= c_level[lev])
          ans[x][1] += (color[y] == c)
        for i in range(dfs_in[x],dfs_out[x]):
          y = ord[i]
          have[level[y]] = 0
          if color[y] == c:
            color[y] = -1

mx, covered = max(ans)
print(mx, mx-covered)
