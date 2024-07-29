#!/usr/bin/env python3
#@EXPECTED_GRADES@ AC RTE RTE RTE RTE

n = int(input())
x1, x2 = [int(i) for i in input().split()]
y1, y2 = [int(i) for i in input().split()]
print(min(y2,x1) - max(0,y1-x1+min(y2,x1)))
