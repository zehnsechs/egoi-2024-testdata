#!/usr/bin/python3
import random
random.seed(17061981)

N, M = map(int, input().split())
conn_list = list()
conn_set = set()
for _ in range(M):
    a, b = map(int, input().split())
    a, b = min(a, b), max(a, b)
    conn_list.append((a, b))
    conn_set.add((a, b))

all_pos = set((a, b) for b in range(N) for a in range(b))

result = []
while all_pos:
    move_to = {}

    all_pos_list = list(all_pos)
    random.shuffle(all_pos_list)
    for a, b in all_pos_list:
        if (a, b) in conn_set and a not in move_to and b not in move_to:
            move_to[a] = b
            move_to[b] = a

    random.shuffle(conn_list)
    for a, b in conn_list:
        if a not in move_to and b not in move_to:
            move_to[a] = b
            move_to[b] = a

    color = list(range(N))
    for a, b in move_to.items():
        color[a] = color[b]
    result.append(color)

    new_pos = set()
    for a, b in all_pos:
        ma = move_to.get(a, a)
        mb = move_to.get(b, b)
        if ma != mb and not (ma == b and mb == a):
            new_pos.add((min(ma, mb), max(ma, mb)))

    all_pos = new_pos

    if len(result) == 20_000:
        break

print(len(result))
for x in result:
    print(' '.join(map(str, x)))
