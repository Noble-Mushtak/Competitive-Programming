from __future__ import print_function
import sys

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))

for i in range(test_cases):
    num_people = int(next(lines))
    people = []
    for j in range(num_people):
        people.append(sum((int(x) for x in next(lines).split(" ")[1:])))
    people_sorted = sorted(people)
    people_sums = []
    cur_sum = 0
    for person in people_sorted:
        cur_sum += person
        people_sums.append(cur_sum)
    print(sum(people_sums)/float(num_people))