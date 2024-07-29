N = int(input())
x = list(map(int, input().split()))
y = list(map(int, input().split()))

result = 0

available = []
for i in range(N):
    if y[i] and available:
        result += 1
        y[i] -= 1
        available[-1][0] -= 1
        if not available[-1][0]:
            available.pop()

    if x[i]:
        available.append([x[i], i])

for _, i in available:
    if y[i]:
        y[i] -= 1

result -= sum(y)

print(result)
