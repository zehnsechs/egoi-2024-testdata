import random

N = int(input())

px = list(range(N))
py = list(range(N))
random.seed(42)
random.shuffle(px)
random.shuffle(py)


def query(type, points):
    print(type)
    for y in range(N):
        print(''.join('1' if (py[y], px[x]) in points else '0' for x in range(N)))
    return int(input()) if type == '?' else None


hor = set()
ver = set()

res = query('?', {(0,0), (0,1), (0,2)})
if res == 3*N:
    ver.add((0,0))
elif res == N:
    hor.add((0,0))
else:
    res2 = query('?', {(0,1), (0,2)})
    if res2 == 2*N:
        hor.add((0,0))
    elif res2 == N:
        ver.add((0,0))
    elif res == 2*N-1:
        hor.add((0,0))
    else:
        ver.add((0,0))

y = x = 0
last = 'H' if hor else 'V'

while len(hor) < N and len(ver) < N:
    q = [(y,x)]
    if last == 'H':
        y += 1
    else:
        x += 1
    q.append((y,x))
    res = query('?', q)
    if res == 2*N:
        if last == 'H':
            hor.add((y,x))
        else:
            ver.add((y,x))
    else:
        if last == 'H':
            ver.add((y,x))
            last = 'V'
        else:
            hor.add((y,x))
            last = 'H'

query('!', hor if len(hor) == N else ver)
