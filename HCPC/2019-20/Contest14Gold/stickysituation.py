from __future__ import print_function
import sys

lines = sys.stdin.read().split("\n")
num_trees = int(lines[0])
trees = [int(x) for x in lines[1].split()]
trees = list(sorted(trees))

answer = False
for i in range(len(trees)-2):
    if trees[i]+trees[i+1] > trees[i+2]:
        answer = True
        break

print("possible" if answer else "impossible")