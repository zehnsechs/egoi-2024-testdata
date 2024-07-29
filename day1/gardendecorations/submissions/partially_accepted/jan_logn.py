phase, n = map(int, input().split())
p = list(map(int, input().split()))
ii = [None] * n
for i in range(n):
    ii[p[i]] = i

swaps = []
while p != list(range(n)):
    swaps.append([])
    used = set()

    for i in range(n):
        if p[i] != i:
            j = ii[i]
            if i not in used and j not in used:
                swaps[-1].append([min(i, j), max(i, j)])
                p[i], p[j] = p[j], p[i]
                ii[p[i]] = i
                ii[p[j]] = j
                used.add(i)
                used.add(j)

swaps = list(reversed(swaps))

if phase == 0:
    print(3 * len(swaps))
    exit(0)

subphase = (phase - 1) % 3

swaps_index = (phase - 1) // 3
swap_with = {}
for swapi, swapj in swaps[swaps_index]:
    if (swaps_index % 2 == 1) ^ (subphase == 1):
        swap_with[swapi] = swapj
    else:
        swap_with[swapj] = swapi

indices = range(n) if phase % 2 == 1 else reversed(range(n))
x = n * [None]
for i in indices:
    x[i] = int(input())
    if i in swap_with:
        x[i] ^= x[swap_with[i]]
    print(x[i])
