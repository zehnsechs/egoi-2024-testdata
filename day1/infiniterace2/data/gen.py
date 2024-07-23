#!/usr/bin/env python3

import sys
import random

def cmdlinearg(name, default=None):
  for arg in sys.argv:
    if arg.startswith(name + "="):
      return arg.split("=")[1]
  assert default is not None, name
  return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
q = int(cmdlinearg('q'))
mode = cmdlinearg('mode')
onlyovertake = int(cmdlinearg('onlyovertake', 0))

pm = ['+'] if onlyovertake else ['+','-']

events = []

if mode == "random":
  for i in range(q):
    events.append([random.choice(pm), random.randint(1,n-1)]);
elif mode == "manylaps":
  while len(events) < q:
    x = random.randint(1,n-1)
    events.append(['+', x]);
    events.append(['+', x]);
  for i in range(10):
    idx = random.randint(0,len(events)-1)
    events = events[:idx] + [[random.choice(pm), random.randint(1,n-1)]] + events[idx:]
  while len(events) > q:
    events.pop()
elif mode == "biased":
  heavy = []
  for i in range(3):
    heavy.append(random.randint(1,n-1))
  for i in range(q):
    if random.choice('hhhhhhhhhv') == 'h':
      events.append([random.choice(pm), random.choice(heavy)]);
    else:
      events.append([random.choice(pm), random.randint(1,n-1)]);
elif mode == "ordered":
  for i in range(q):
    events.append([random.choice(pm), (i%(n-1))+1]);
elif mode == "nolaps":
  behind = {}
  for i in range(q):
    x = random.randint(1,n-1)
    if x in behind:
      events.append(['+', x])
      behind.pop(x,None)
    else:
      events.append(['-', x])
      behind[x] = 1
elif mode == "stupid":
  for i in range(q):
    events.append(['-', random.randint(1,n-1)]);
else:
  assert(False)

while len(events) > q:
  events.pop()

print(n)
print(q)
for s,p in events:
  print(p if s=='+' else -p)
