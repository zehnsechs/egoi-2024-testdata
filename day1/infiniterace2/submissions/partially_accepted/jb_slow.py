#!/bin/python3
# @EXPECTED_GRADES@ AC TLE AC TLE

n = int(input())
q = int(input())

laps = 0
behind = []
for i in range(q):
  x = int(input())
  if x > 0:
    if x in behind:
      laps += 1
      behind = []
    behind.append(x)
  elif -x in behind:
    behind.remove(-x)

print(laps)
