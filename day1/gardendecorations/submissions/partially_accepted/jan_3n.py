phase, n = map(int, input().split())
p = list(map(int, input().split()))
ii = [None] * n
for i in range(n):
    ii[p[i]] = i

swaps = []
for i in range(n):
    if p[i] != i:
        j = ii[i]
        swaps.append((i, j))
        p[i], p[j] = p[j], p[i]
        ii[p[j]] = j
swaps = list(reversed(swaps))

if phase == 0:
    print(3 * len(swaps))
    exit(0)

subphase = (phase - 1) % 3
swaps_index = (phase - 1) // 3
swap = swaps[swaps_index]
if (swaps_index % 2 == 1) ^ (subphase == 1):
    swapi, swapj = swap[1], swap[0]
else:
    swapi, swapj = swap[0], swap[1]

indices = range(n) if phase % 2 == 1 else reversed(range(n))
for i in indices:
    x = int(input())
    if i == swapi:
        value = x
    elif i == swapj:
        x ^= value
    print(x)
