from __future__ import print_function
import sys
import copy

lines = (line for line in sys.stdin.read().split("\n"))
first_line_nums = [int(x) for x in next(lines).split()]
num_people = first_line_nums[0]
num_pairs = first_line_nums[1]

like_mapping = {}
reverse_mapping = {}
marked = {}
for i in range(num_people):
    like_mapping[i] = set()
    marked[i] = set()

for i in range(num_pairs):
    nums = [int(x) for x in next(lines).split()]
    num0, num1 = nums[0], nums[1]
    like_mapping[num0].add(num1)
    reverse_mapping[num1].add(num0)

def num_likes(person):
    return len(like_mapping[person])

def num_reverses(person):
    return len(reverse_mapping[person])

permut1 = list(sorted(range(num_people), key=num_likes))
permut2 = list(sorted(range(num_people), key=num_reverses))
taken1 = set()
taken2 = set()

if num_likes(permut1[0]) == 0:
    print("YES")
    sys.exit(0)
if num_reverses(permut1[0]) == 0:
    print("NO")
    sys.exit(0)

while num_likes(permut1[0]) == 1:
    