#!/usr/bin/python3

n,m,q, = [int(x) for x in input().split()]

a = [int(x) for x in input().split()]
am = a + [ai+n for ai in a]

def dist(x,y):
    return min((y-x)%(2*n),(x-y)%(2*n))

def lower(i):
    if i < a[0]:
        return am[-1]
    l=0 # l is <=
    h=2*m # h is >
    
    while l!=h-1:
        mid=(l+h)//2
        if am[mid]<= i:
            l = mid
        else:
            h = mid
    return am[l]

def higher(i):
    if i > am[-1]: # gives full points if this is a TODO improve testdata
        return am[0]
    l=-1 #l is always lower
    h=2*m-1 #h is always >=

    while l!=h-1:
        mid=(l+h)//2+(l+h)%2 # make sure to round up
        if am[mid]>=i:
            h=mid
        else:
            l=mid
    return am[h]


for _ in range(q):
    x,y = [int(z) for z in input().split()]
    if m==0:
        print(dist(x,y))
        continue
    
    xl = lower(x)
    xh = higher(x)

    
    yl = lower(y)
    yh = higher(y)

    print(min(dist(x,y),dist(xl,x)+1+dist((xl+n)%(2*n),y),dist(xh,x)+1+dist((xh+n)%(2*n),y),dist(yl,y)+1+dist((yl+n)%(2*n),x),dist(yh,y)+1+dist((yh+n)%(2*n),x)))

