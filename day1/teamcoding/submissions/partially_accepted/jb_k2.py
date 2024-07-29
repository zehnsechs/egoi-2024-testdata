#!/usr/bin/python3
#@EXPECTED_GRADES@ WA AC WA WA WA

n, cols = [int(x) for x in input().split()]
color = [int(x) for x in input().split()]
g = [[] for _ in range(n)]
for i in range(n-1):
  x = int(input())
  y = i+1
  g[x].append(y)
  g[y].append(x)

best = len([x for x in range(n) if color[x] == color[0]])
best_swp = 0

other_per_level = [0]*n

level = [0]*n
ord, stack = [], [0]
while stack:
  x = stack.pop()
  ord.append(x)
  other_per_level[level[x]] += (color[x] != color[0])
  for y in g[x]:
    g[y].remove(x)
    level[y] = level[x] + 1
    stack.append(y)

already = [(0 if color[x]==color[0] else 1) for x in range(n)]
count = [0]*n
tmp = [dict() for _ in range(n)]
for x in reversed(ord):
  tmp[x][level[x]] = count[x] = min(1,other_per_level[level[x]])
  for y in g[x]:
    already[x] += already[y]
    if len(tmp[y]) > len(tmp[x]):
      tmp[x], tmp[y] = tmp[y], tmp[x]
      count[x], count[y] = count[y], count[x]
    for lev in tmp[y]:
      a = (tmp[x][lev] if lev in tmp[x] else 0)
      count[x] -= a
      tmp[x][lev] = min(other_per_level[lev], a + tmp[y][lev])
      count[x] += tmp[x][lev]
  if color[x] != color[0]:
    if count[x] > best:
      best = count[x]
      best_swp = count[x] - already[x]
    if count[x] == best and best_swp > count[x]-already[x]:
      best_swp = count[x] - already[x]
print(best, best_swp)


