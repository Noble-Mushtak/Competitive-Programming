import sys

lines = (line for line in sys.stdin.read().split("\n"))

first_line = [int(x) for x in next(lines).split()]
width = first_line[0]
num_partitions = first_line[1]

partitions = [int(x) for x in next(lines).split()]
partitions.insert(0, 0)
partitions.append(width)

answers = set()

for i, line1 in enumerate(partitions):
    for line2 in partitions[:i]:
        answers.add(line1-line2)

print(" ".join([str(ans) for ans in sorted(list(answers))]))