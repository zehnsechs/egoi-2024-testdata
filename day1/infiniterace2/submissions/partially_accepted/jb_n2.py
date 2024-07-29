#!/bin/python3
# @EXPECTED_GRADES@ AC WA WA WA

n = int(input())
q = int(input())
laps, t = 0, []
for i in range(q):
  t.append(int(input()))
for i in range(q-1):
  laps += (t[i]>0 and t[i+1]>0)
print(laps)
