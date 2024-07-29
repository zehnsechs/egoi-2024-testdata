#!/usr/bin/python3

n,m,q, = [int(x) for x in input().split()]

a = [int(x) for x in input().split()]
am = a + [ai+n for ai in a]

def dist(x,y):
    return min((y-x)%(2*n),(x-y)%(2*n))

lower = [-1 for _ in range(2*n)]
c = -1
for i in range(2*n):
    if c < 2*m-1 and am[c+1]==i:
        c = c+1
    lower[i]=c

higher = [0 for _ in range(2*n)]
d = 0
flag = True
for i in range(2*n):
    higher[i]=d
    if m>0 and  am[d] == i:
        if d<2*m-1 and flag:
            d = d+1
        else:
            d = 0
            flag = False



for _ in range(q):
    x,y = [int(z) for z in input().split()]
    if m==0:
        print(dist(x,y))
        continue

    xl = am[lower[x]]
    xh = am[higher[x]]


    yl = am[lower[y]]
    yh = am[higher[x]]

    print(min(dist(x,y),dist(xl,x)+1+dist((xl+n)%(2*n),y),dist(xh,x)+1+dist((xh+n)%(2*n),y),dist(yl,y)+1+dist((yl+n)%(2*n),x),dist(yh,y)+1+dist((yh+n)%(2*n),x)))

