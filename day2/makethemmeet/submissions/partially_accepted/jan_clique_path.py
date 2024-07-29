#!/usr/bin/python3
N, M = map(int, input().split())

even = [i//2 for i in range(N)]
odd = [(i+1)//2 for i in range(N)]

print(N)
for i in range(N):
    print(' '.join(map(str, even if i % 2 == 0 else odd)))
