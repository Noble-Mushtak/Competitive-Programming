from __future__ import print_function
import sys

lines = sys.stdin.read().split("\n")
num_days = int(lines[0])
tree_lives = [int(x) for x in lines[1].split()]
tree_lives = list(reversed(sorted(tree_lives)))

max_tree_life = 0
for i in range(num_days):
    max_tree_life = max(max_tree_life, i+1+tree_lives[i])
print(max_tree_life+1)