#!/usr/bin/python3
def minDirectPass(n, x, y):
    return min(abs(x - y), n - abs(x - y))

n, m, q = [int(x) for x in input().split()]
s = [int(x) for x in input().split()]
s += [a + n for a in s]

n *= 2

for _ in range(q):
    x, y = [int(x) for x in input().split()]
    res = minDirectPass(n, x, y)
    
    l = 0
    r = len(s) if s[0] < x else 0
    while r - l > 1: 
        mid = (l + r) // 2
        if s[mid] > x: 
            r = mid
        else:
            l = mid 

    # right bridge
    r = 0 if r == len(s) else r
    res = min(res, minDirectPass(n, x, s[r]) + minDirectPass(n, (s[r] + n // 2) % n, y) + 1) 

    # left bridge
    r = r - 1 if r != 0 else len(s) - 1
    res = min(res, minDirectPass(n, x, s[r]) + minDirectPass(n, (s[r] + n // 2) % n, y) + 1)

    print(res)