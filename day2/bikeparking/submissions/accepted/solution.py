#!/usr/bin/env python3

n = int(input())
x = list(map(int,input().split()))
y = list(map(int,input().split()))

ans = 0

exile = max(0, y[n-1]-x[n-1])
moving = y[n-1]-exile

for i in range(n-1)[::-1]:
    slots = x[i]
    if exile > 0:
        if slots >= exile:
            slots -= exile
            ans += exile
            exile = 0
        else:
            exile -= slots
            ans += slots
            slots = 0
    if moving > 0:
        if slots >= moving:
            slots -= moving
            ans += moving
            moving = 0
        else:
            moving -= slots
            ans += slots
            slots = 0
    if slots > 0:
        exile = max(0, y[i]-slots)
        moving = y[i]-exile
    else:
        exile += y[i]

ans -= exile

print(ans)
