#!/usr/bin/python3

n, m, q = [int(x) for x in input().split()]
t = int(input())
x, y = [int(x) for x in input().split()]
mod = 2*n;

print(min(
    (x-y)%mod,
    (y-x)%mod,
    #(x-t)%mod+1+(t+n-y)%mod,
    (t-x)%mod+1+(t+n-y)%mod,
    (t-x)%mod+1+(y-t-n)%mod,
    (x-t)%mod+1+(y-t-n)%mod,
    (y-t)%mod+1+(t+n-x)%mod,
    (t-y)%mod+1+(t+n-x)%mod,
    (t-y)%mod+1+(x-t-n)%mod,
    (y-t)%mod+1+(x-t-n)%mod,
))
