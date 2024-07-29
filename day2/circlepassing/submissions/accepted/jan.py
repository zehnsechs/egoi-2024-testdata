#!/usr/bin/python3
import bisect

N, M, Q = map(int, input().split())
X = sorted(map(int, input().split()))

def dist(a, b):
    return min((a-b) % (2*N), (b-a) % (2*N))

def dist_via(a, b):
    i = bisect.bisect_left(X, a)
    xs = [X[(i+d) % M] for d in [-1, 0, +1]]
    return min(dist(a, x) + 1 + dist(x+N, b) for x in xs)

for _ in range(Q):
    fr, to = map(int, input().split())
    print(min(dist(fr, to), dist_via(fr, to), dist_via(to, fr)))
