import sys

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))
count = {}
for i in range(test_cases):
    cur_line = next(lines)
    if cur_line not in count: count[cur_line] = 1
    else: count[cur_line] += 1

min_count = 1000000
strs = []
for str, count in count.items():
    if count < min_count:
        strs = [str]
        min_count = count
    elif count == min_count:
        strs.append(str)
        min_count = count
print("\n".join(sorted(strs)))