#!/bin/python3
# @EXPECTED_GRADES@ WA AC WA WA

n = int(input())
q = int(input())

laps = 0
last_overtake = [-1]*n
last_lap = 0
for t in range(q):
  x = int(input())
  if last_overtake[x] >= last_lap:
    last_lap = t
    laps += 1
  last_overtake[x] = t

print(laps)
