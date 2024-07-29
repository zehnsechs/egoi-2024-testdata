#!/bin/python3

n = int(input())
q = int(input())

behind = set()
ans = 0
for _ in range(q):
    x = int(input())
    if x > 0:
        if x in behind:
            ans += 1
            behind = set([x])
        else:
            behind.add(x)
    else:
        x = -x
        if x in behind:
            behind.remove(x)
print(ans)
