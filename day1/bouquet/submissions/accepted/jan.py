import bisect
import heapq

N = int(input())
L, R = zip(*(map(int, input().split()) for _ in range(N)))

best = [0]
available = []
for n in range(N):
    l = min(L[n], n)
    r = min(R[n], N-1-n)
    i = bisect.bisect_right(best, n-l)
    heapq.heappush(available, (n+r, i, n+1))
    while available and available[0][0] == n:
        _, i, m = heapq.heappop(available)
        if i == len(best):
            best.append(m)
        else:
            best[i] = min(best[i], m)

print(len(best) - 1)
