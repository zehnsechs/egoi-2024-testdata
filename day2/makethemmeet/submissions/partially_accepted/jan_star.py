#!/usr/bin/python3
N, M = map(int, input().split())

print(3)
print(' '.join(['0'] * N))
print(' '.join(['1'] * 2 + ['0'] * (N-2)))
print(' '.join(['0'] * N))
