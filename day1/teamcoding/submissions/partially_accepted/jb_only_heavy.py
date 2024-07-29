#!/usr/bin/python3

n, cols = [int(x) for x in input().split()]
color = [int(x) for x in input().split()]
g = [[] for _ in range(n)]
for i in range(n-1):
  x = int(input())
  y = i+1
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

ans  = [[0,0] for i in range(n)]
for c in range(cols):
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
