#!/usr/bin/env python3
import sys

mode = sys.argv[1]
assert mode in ("lamps_small", "lamps_scoring"), mode
max_score = float(sys.argv[2])

lines = []
for line in sys.stdin.readlines():
    verdict, queries = line.split()
    lines.append((verdict, float(queries)))

assert len(lines) == 1
verdict, queries = lines[0]

score = 0.0
if verdict == 'AC':
    if mode == "lamps_small":
        score = max_score
    elif mode == "lamps_scoring":
        assert max_score == 78, "max_score should be 78 :)"
        if queries <= 85:
            score = 78
        elif queries <= 200:
            score = 58 + (200.0 - queries) * 4.0 / 23.0
        elif queries <= 2000:
            score = (2000.0 - queries) * 29.0 / 900
        else:
            assert False, f"Q = {queries} > 2000 too large"
        score = float(int(score + 1e-7)) # floor as per problem statement
        score = min(max(score,float(0.0)), max_score)
    else:
        assert False, f"unknown mode {mode}"

print("%s %f" % (verdict, score))
