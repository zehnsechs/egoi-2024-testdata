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
ys = list(range(N))
xs = list(range(N))

def add_hor(point):
    hor.add(point)
    ys.remove(point[0])

def add_ver(point):
    ver.add(point)
    xs.remove(point[1])

def add_same(point, last):
    (add_hor if last in hor else add_ver)(point)

def add_diff(point, last):
    (add_ver if last in hor else add_hor)(point)

q = [(0, 0), (0, 1), (0, 2)]
res = query('?', q)
if res == 3*N:
    add_ver(q[0])
    add_ver(q[1])
    add_ver(q[2])
    last = q[2]
elif res == N:
    add_hor(q[0])
    last = q[0]
else:
    res2 = query('?', [q[1], q[2]])
    if res2 == 2*N:
        add_hor(q[0])
        add_ver(q[1])
        add_ver(q[2])
        last = q[0]
    elif res2 == N:
        add_ver(q[0])
        add_hor(q[1])
        last = q[1]
    elif res == 2*N-1:
        add_hor(q[0])
        last = q[0]
    else:
        add_ver(q[0])
        last = q[0]

while len(hor) < N and len(ver) < N:
    q = [last]
    if last in hor:
        q.append((ys[0], last[1]))
        if len(ys) >= 2:
            q.append((ys[1], last[1]))
    else:
        q.append((last[0], xs[0]))
        if len(xs) >= 2:
            q.append((last[0], xs[1]))
    res = query('?', q)
    if len(q) == 3:
        if res == 3*N:
            add_same(q[1], last)
            add_same(q[2], last)
            last = q[2]
        elif res == 2*N-1:
            add_diff(q[1], last)
            last = q[1]
        else:
            res2 = query('?', q[0:2])
            if res2 == 2*N:
                add_same(q[1], last)
                add_diff(q[2], last)
                last = q[2]
            else:
                add_diff(q[1], last)
                add_same(q[2], last)
                last = q[1]
    else:
        if res==2*N:
            add_same(q[1], last)
        else:
            add_diff(q[1], last)
        last = q[1]

query('!', hor if len(hor) == N else ver)
