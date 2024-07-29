#!/usr/bin/python3
from collections import defaultdict

N, M = map(int, input().split())
conn = defaultdict(set)
dist = [[0 if a == b else N for a in range(N)] for b in range(N)]
for _ in range(M):
    a, b = map(int, input().split())
    a, b = min(a, b), max(a, b)
    conn[a].add(b)
    conn[b].add(a)
    dist[a][b] = dist[b][a] = 1

for c in range(N):
    for a in range(N):
        for b in range(N):
            dist[a][b] = min(dist[a][b], dist[a][c] + dist[c][b])

pos = list((a, b) for b in range(N) for a in range(b))

result = []
while pos:
    pos.sort(key=lambda ab: dist[ab[0]][ab[1]])

    move_to = {}
    for a, b in pos:
        for a, b in [(a, b), (b, a)]:
            if a in move_to or b in move_to:
                continue
            for c in conn[a]:
                if c in move_to:
                    continue
                if c == b or dist[c][b] < dist[a][b]:
                    move_to[b] = b
                    move_to[a] = c
                    move_to[c] = a
                    break

    color = list(range(N))
    for a, b in move_to.items():
        color[a] = color[b]
    result.append(color)

    new_pos = set()
    for a, b in pos:
        ma = move_to.get(a, a)
        mb = move_to.get(b, b)
        if ma != mb and not (ma == b and mb == a):
            new_pos.add((min(ma, mb), max(ma, mb)))
    pos = list(new_pos)

    if len(result) == 20_000:
        break

print(len(result))
for x in result:
    print(' '.join(map(str, x)))
