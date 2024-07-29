#!/bin/python3

n = int(input())
q = int(input())

cnt = [0]*n
for i in range(q):
  cnt[abs(int(input()))] += 1

print(max(0,max(cnt)-1))
