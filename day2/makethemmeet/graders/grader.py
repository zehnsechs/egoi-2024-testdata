import sys

assert sys.argv[1] == "rescale"
rescale_from = float(sys.argv[2])
rescale_to = float(sys.argv[3])

lines = []
for line in sys.stdin.readlines():
    verdict, score = line.split()
    lines.append((verdict, float(score)))

assert len(lines) == 1
verdict, score = lines[0]

score = score * rescale_to / rescale_from
score = float(int(score + 1e-7)) # floor as per problem statement

print("%s %f" % (verdict, score))
