import copy

phase, n = map(int, input().split())
p = list(map(int, input().split()))

has = []
add = []

# Phase 1
has.append([{i} for i in range(n)])
add.append([set() for i in range(n)])
for i in range(n):
    j = p[i]
    while j > i:
        j = p[j]
    if j != i:
        has[0][i].add(j)
        add[0][i].add(j)

# Phase 2
has.append(copy.deepcopy(has[0]))
add.append([set() for i in range(n)])
for i in reversed(range(n)):
    for j in reversed(range(i+1, n)):
        if p[j] in has[1][i]:
            has[1][i].symmetric_difference_update(has[1][j])
            add[1][i].add(j)

# Phase 3
has.append(copy.deepcopy(has[1]))
add.append([set() for i in range(n)])
for i in range(n):
    for j in range(i):
        if p[j] in has[2][i]:
            has[2][i].symmetric_difference_update(has[2][j])
            add[2][i].add(j)

# import sys
# for item in has:
#     print(item, file=sys.stderr)
# print(file=sys.stderr)
# for item in add:
#     print(item, file=sys.stderr)
# print(file=sys.stderr)

if phase == 0:
    print(0 if p == list(range(n)) else 3)
    exit(0)

indices = range(n) if phase != 2 else reversed(range(n))
x = n * [0]
y = n * [0]

for i in indices:
    x[i] = int(input())
    y[i] = x[i]
    for j in add[phase-1][i]:
        y[i] ^= x[j] if phase == 1 else y[j]
    print(y[i])
