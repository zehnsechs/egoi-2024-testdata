#!/usr/bin/env python3
#@EXPECTED_GRADES@ TLE TLE AC TLE TLE

n = int(input())
r = [0]*n
delayed = [[] for i in range(n)]
for i in range(n):
  l, r[i] = [int(i) for i in input().split()]
  if i-l >= 0:
    delayed[i-l].append(i)

dp = [0]*n
active = []
for i in reversed(range(n)):
  for j in active:
    if i+r[i] < j:
      dp[i] = max(dp[i], dp[j])
  dp[i] += 1
  active += delayed[i]

print(max(dp))

