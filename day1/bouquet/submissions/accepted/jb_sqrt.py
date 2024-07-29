#!/usr/bin/env python3

n = int(input())
r = [0]*n
delayed = [[] for i in range(n)]
for i in range(n):
  l, r[i] = [int(i) for i in input().split()]
  if i-l >= 0:
    delayed[i-l].append(i)

dp = [0]*n
segtree = [0]*(2*n)
proc = [0]*(n+1)
active = []
for i in reversed(range(n)):
  if i+r[i]+1 < n:
    dp[i] = max(dp[i], proc[i+r[i]+1])
  for j in active:
    if i+r[i] < j:
      dp[i] = max(dp[i], dp[j])
  dp[i] += 1

  proc[i] = proc[i+1]
  active += delayed[i]
  if len(active) > 400: # ~ sqrt n
    for j in active:
      proc[j] = dp[j]
    for j in range(n-1,i-1,-1):
      proc[j] = max(proc[j], proc[j+1])
    active = []

print(max(dp))
