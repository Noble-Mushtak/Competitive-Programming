import sys

lines = (line for line in sys.stdin.read().split("\n"))

has_queen = []
num_queens = 0
for i in range(8):
    cur_line = next(lines)
    has_queen.append([])
    for j in range(8):
        has_queen[-1].append(cur_line[j] == "*")
        if has_queen[-1][-1]:
            num_queens += 1
if num_queens != 8:
    print("invalid")
    sys.exit(0)

def can_attack_dir(i0, j0, dx, dy):
    i, j = i0, j0
    while True:
        i += dx
        j += dy
        try:
            if i < 0:
                break
            if j < 0:
                break
            if has_queen[i][j]:
                return True
        except IndexError:
            break
    return False

def can_attack(i, j):
    return can_attack_dir(i, j, 1, 0) or can_attack_dir(i, j, -1, 0) or can_attack_dir(i, j, 0, 1) or can_attack_dir(i, j, 0, -1) or can_attack_dir(i, j, 1, 1) or can_attack_dir(i, j, 1, -1) or can_attack_dir(i, j, -1, 1) or can_attack_dir(i, j, -1, -1)

for i in range(8):
    for j in range(8):
        if has_queen[i][j] and can_attack(i, j):
            print("invalid")
            sys.exit(0)

print("valid")