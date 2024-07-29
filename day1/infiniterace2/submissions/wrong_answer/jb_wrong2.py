#!/bin/python3

n = int(input())
q = int(input())
laps, t = 0, []
for i in range(q):
  t.append(int(input()))
for i in range(q-1):
  laps += (t[i]==t[i+1])
print(laps)
