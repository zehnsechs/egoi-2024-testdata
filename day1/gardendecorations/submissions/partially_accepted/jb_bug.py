#!/usr/bin/python3

phase, n = [int(x) for x in input().split()]
p = [int(x) for x in input().split()]
if phase == 0:
  print(3)
  exit()

seen, res = [0]*n, [0]*n
ip = [p.index(i) for i in range(n)]

a, b = p.copy(), ip.copy()
for i in range(n):
  while a[i] > i:
    a[i] = p[a[i]]
  while b[i] > i:
    b[i] = ip[b[i]]

for i in (reversed(range(n)) if phase==2 else range(n)):
  seen[i] = int(input())
  if phase == 1:
    res[i] = seen[i]^(0 if a[i] == i else seen[a[i]])

  if phase == 2:
    res[i] = seen[i]
    def go(j,q,val):
      if j > i: # BUG: should be a while loop, still works if P = reversal
        res[i] = res[i] ^ val[j]
        j = q[j]
    go(p[b[i]],a,seen)
    if a[i] != i: go(ip[a[i]],b,res)

  if phase == 3:
    res[i] = seen[i]^(0 if b[i] == i else res[b[i]])

  print(res[i])
