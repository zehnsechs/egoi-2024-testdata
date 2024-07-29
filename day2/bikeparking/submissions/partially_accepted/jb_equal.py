#!/usr/bin/python3
#@EXPECTED_GRADES@ WA AC WA WA WA
n = int(input())
a = int(input().split()[0])
print(max(n-2,0)*a)
