N = int(input())
Q = int(input())

lap = 0
last = {}

for _ in range(Q):
    x = int(input())
    if x > 0:
        if x in last:
            if last[x] == lap:
                lap += 1
        last[x] = lap
    elif -x in last:
        del last[-x]

print(lap)
