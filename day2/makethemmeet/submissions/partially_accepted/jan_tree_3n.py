#!/usr/bin/python3
from collections import defaultdict

N, M = map(int, input().split())
assert M == N-1, "no tree"

conn = defaultdict(list)
for _ in range(M):
    a, b = map(int, input().split())
    conn[a].append(b)
    conn[b].append(a)

for i in range(N):
    if len(conn[i]) == 1:
        sink = i
        root = conn[i][0]
        break

even = list(range(N))
odd = list(range(N))
trap = [root if i == sink else i for i in range(N)]


def dfs(n, parent, depth):
    childs = [c for c in conn[n] if c != parent]
    for c in childs:
        if depth % 2 == 0:
            even[c] = n
        else:
            odd[c] = n
        dfs(c, n, depth + 1)


dfs(root, None, 0)

print(3*N)
for i in range(N):
    print(' '.join(map(str, even)))
    print(' '.join(map(str, odd)))
    print(' '.join(map(str, trap)))
