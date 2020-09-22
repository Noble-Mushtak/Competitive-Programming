from __future__ import print_function
import sys

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))
print(test_cases)

def comp_to_point(c):
    return (int(c.real), int(c.imag))

def get_real(c):
    return c[0]

def get_imag(c):
    return c[1]

for i in range(test_cases):
    output = next(lines)
    points = set([(0, 0)])
    cur_point = 0+0j
    direction = 1+0j
    for ch in output:
        rot = None
        if ch == "F":
            rot = 1+0j
        elif ch == "R":
            rot = 0-1j
        elif ch == "B":
            rot = -1+0j
        elif ch == "L":
            rot = 0+1j
        direction *= rot
        cur_point += direction
        points.add(comp_to_point(cur_point))
    points_lst = list(points)
    xs = list(map(get_real, points_lst))
    ys = list(map(get_imag, points_lst))
    min_x = min(xs)
    max_x = max(xs)+1
    min_y = min(ys)-1
    max_y = max(ys)+1
    print(max_y-min_y+1, max_x-min_x+1)
    for cur_y in range(max_y, min_y-1, -1):
        for cur_x in range(min_x, max_x+1):
            if (cur_x, cur_y) in points:
                print(".", end="")
            else:
                print("#", end="")
        print()