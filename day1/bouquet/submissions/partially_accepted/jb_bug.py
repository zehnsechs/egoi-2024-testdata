#!/usr/bin/env python3
#@EXPECTED_GRADES@ AC AC WA WA WA

n = int(input())
r = [0]*n
delayed = [[] for i in range(n)]
for i in range(n):
  l, r[i] = [int(i) for i in input().split()]
  if i-l >= 0:
    delayed[i-l].append(i)

dp = [0]*n
segtree = [0]*(2*n)
for i in reversed(range(n)):
  x, y = i+r[i]+0+n, 2*n # off by one bug here, 0 should be a 1
  while x < y:
    if x&1:
      dp[i] = max(dp[i], segtree[x])
      x += 1
    if y&1:
      y -= 1
      dp[i] = max(dp[i], segtree[y])
    x //= 2
    y //= 2

  dp[i] += 1

  for j in delayed[i]:
    x = j+n
    while x > 0:
      segtree[x] = max(segtree[x], dp[j])
      x //= 2

print(max(dp))
