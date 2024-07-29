#!/usr/bin/env python3
#@EXPECTED_GRADES@ TLE TLE AC TLE TLE

n = int(input())
r = [0]*n
delayed = [[] for i in range(n)]
for i in range(n):
  l, r[i] = [int(i) for i in input().split()]
  if i-l >= 0:
    delayed[i-l].append(i)

dp = [1]*n
segtree = [0]*(2*n)
proc = [0]*n
for i in reversed(range(n)):
  if i+r[i]+1 < n:
    dp[i] = 1+proc[i+r[i]+1]

  for j in delayed[i]:
    proc[j] = dp[j]
  for j in reversed(range(n-1)):
    proc[j] = max(proc[j], proc[j+1])

print(max(dp))
