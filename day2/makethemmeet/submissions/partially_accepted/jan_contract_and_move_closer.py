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


def do_move(pos, move_to):
    new_pos = set()
    for a, b in pos:
        mas = move_to.get(a, [a])
        mbs = move_to.get(b, [b])
        for ma in mas:
            for mb in mbs:
                if ma != mb and not (ma == b and mb == a):
                    new_pos.add((min(ma, mb), max(ma, mb)))
    return list(new_pos)


result = []
while pos:
    pos.sort(key=lambda ab: dist[ab[0]][ab[1]])
    pos_set = set(pos)

    best_len_pos = len(pos)
    best_move_to = {}

    for a in range(N):
        move_to = {}
        for b in conn[a]:
            if not any(c in move_to for c in conn[b]):
                move_to[b] = [a]
        move_to[a] = list(move_to.keys())
        if len(move_to) <= 2:
            continue
        len_pos = len(do_move(pos, move_to))
        if len_pos < best_len_pos:
            best_len_pos = len_pos
            best_move_to = move_to

    move_to = best_move_to

    for a, b in pos:
        for a, b in [(a, b), (b, a)]:
            if a in move_to or b in move_to:
                continue
            for c in conn[a]:
                if c in move_to:
                    continue
                if c == b or dist[c][b] < dist[a][b]:
                    move_to[b] = [b]
                    move_to[a] = [c]
                    move_to[c] = [a]
                    break

    color = list(range(N))
    for a, bs in move_to.items():
        for b in bs:
            color[b] = color[a]
    result.append(color)

    pos = do_move(pos, move_to)

    if len(result) == 20_000:
        break

print(len(result))
for x in result:
    print(' '.join(map(str, x)))
