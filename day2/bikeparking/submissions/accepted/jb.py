#!/usr/bin/env python3

n = int(input())
x = [int(i) for i in input().split()]
y = [int(i) for i in input().split()]

good, okay, bad, free = 0, 0, 0, 0

for i in range(n):
  k = min(y[i], free)
  free -= k
  y[i] -= k
  good += k

  k = min(y[i], okay)
  okay -= k
  bad += k
  good += k
  y[i] -= k

  k = min(y[i], x[i])
  okay += k
  y[i] -= k
  x[i] -= k

  free += x[i]
  bad += y[i]

print(good - bad)
