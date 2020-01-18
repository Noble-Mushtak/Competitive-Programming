import sys

def hailstone(cur_num):
    if cur_num == 1:
        return 1
    elif (cur_num & 1) == 0:
        return cur_num+hailstone(cur_num // 2)
    else:
        return cur_num+hailstone(3*cur_num+1)

lines = sys.stdin.read().split("\n")
print(hailstone(int(lines[0])))