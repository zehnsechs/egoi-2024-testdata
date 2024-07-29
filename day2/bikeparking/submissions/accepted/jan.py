N = int(input())
x = list(map(int, input().split()))
y = list(map(int, input().split()))

result = 0

available = []
for i in range(N):
    while y[i] and available:
        n = min(y[i], available[-1][0])
        result += n
        y[i] -= n
        available[-1][0] -= n
        if not available[-1][0]:
            available.pop()

    available.append([x[i], i])

for n, i in available:
    y[i] -= min(y[i], n)

result -= sum(y)

print(result)
