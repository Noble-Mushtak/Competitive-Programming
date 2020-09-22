from __future__ import print_function
import itertools
import sys
import copy

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))

for i in range(test_cases):
    num_colors = int(next(lines))
    colors = next(lines).split()
    num_pairs = int(next(lines))
    pairs = set()
    for j in range(num_pairs):
        words = next(lines).split()
        pairs.add((words[0], words[1]))
    
    def first_arrangements(starting, left):
        if len(left) == 0:
            return starting
        for color in left:
            if len(starting) == 0 or (not (((color, starting[-1]) in pairs) or ((starting[-1], color) in pairs))):
                new_left = copy.deepcopy(left)
                new_left.remove(color)
                answer = first_arrangements(starting+[color], new_left)
                if answer != None:
                    return answer
        return None

    # print(len(arrangements))
    print(first_arrangements([], colors))