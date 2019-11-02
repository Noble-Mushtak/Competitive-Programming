from __future__ import print_function
import sys

dot_strs = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

def split(lst):
    if len(lst) == 0: return []
    lines = []
    for line in lst:
        if line == "": break
        lines.append(line)
    return [lines]+split(lst[len(lines)+1:])

lines = sys.stdin.read().split("\n")
test_cases = split(lines)
beg = True
for test_case in test_cases:
    if len(test_case) == 0: continue
    if not beg: print("")
    else: beg = False

    locations = {}
    num_dots = 0
    for i, line in enumerate(test_case):
        for j, char in enumerate(line):
            if char != ".":
                num_dots += 1
                locations[char] = (i, j)
                
    for i in range(num_dots-1):
        cur_loc = locations[dot_strs[i]]
        new_loc = locations[dot_strs[i+1]]
        if cur_loc[0] == new_loc[0]:
            if cur_loc[1] > new_loc[1]: cur_loc, new_loc = new_loc, cur_loc
            for j in range(cur_loc[1]+1, new_loc[1]):
                char = "-"
                if test_case[cur_loc[0]][j] == "|": char = "+"
                elif test_case[cur_loc[0]][j] != "." and test_case[cur_loc[0]][j] != "-": char = test_case[cur_loc[0]][j]
                test_case[cur_loc[0]] = test_case[cur_loc[0]][:j]+char+test_case[cur_loc[0]][(j+1):]
        else:
            if cur_loc[0] > new_loc[0]: cur_loc, new_loc = new_loc, cur_loc
            for j in range(cur_loc[0]+1, new_loc[0]):
                char = "|"
                if test_case[j][cur_loc[1]] == "-": char = "+"
                elif test_case[j][cur_loc[1]] != "." and test_case[j][cur_loc[1]] != "|": char = test_case[j][cur_loc[1]]
                test_case[j] = test_case[j][:cur_loc[1]]+char+test_case[j][(cur_loc[1]+1):]

    print("\n".join(test_case))