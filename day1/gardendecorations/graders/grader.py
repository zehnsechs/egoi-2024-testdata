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

# Round to nearest integer, per problem statement
score = round(score)

print("%s %f" % (verdict, score))
