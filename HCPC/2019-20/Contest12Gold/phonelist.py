from __future__ import print_function
import sys

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))

for i in range(test_cases):
    num_strs = int(next(lines))
    all_strs = []
    for j in range(num_strs):
        all_strs.append(next(lines))
    all_strs = list(sorted(all_strs, key=len, reverse=True))
    
    all_prefixes = set()
    answer = True
    for str in all_strs:
        if str in all_prefixes:
            answer = False
            break
        for j in range(1, len(str)+1):
            all_prefixes.add(str[:j])
    print("YES" if answer else "NO")