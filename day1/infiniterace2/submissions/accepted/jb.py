#!/bin/python3

n = int(input())
q = int(input())

laps = 0
behind = {}
for i in range(q):
  x = int(input())
  if x > 0:
    if x in behind:
      laps += 1
      behind = {}
    behind[x] = 1
  else:
    behind.pop(-x,None)

print(laps)
