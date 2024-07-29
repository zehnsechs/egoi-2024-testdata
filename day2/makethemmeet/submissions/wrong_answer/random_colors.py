#!/usr/bin/python3
import random
n,m = map(int, input().split())

k = 1000
print(k)
for i in range(k):
    row = [random.randint(1, 3) for _ in range(n)]
    print(*row)
