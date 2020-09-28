import sys

lines = (line for line in sys.stdin.read().split("\n"))

dimens = [int(x) for x in next(lines).split()]
num_rows = dimens[0]
num_columns = dimens[1]

grid = []
for i in range(num_rows):
    next_line = next(lines)
    grid.append([])
    for j in range(num_columns):
        grid[-1].append(next_line[j] == "#")

labels = [[0]*num_columns for i in range(num_rows)]

def set_grid(i, j, lab):
    global labels
    
    stack = [(i, j)]
    labels[i][j] = lab
    while len(stack) > 0:
        i2, j2 = stack.pop()
        # print(i2, j2, labels[2][0])
        for x in [-1, 0, 1]:
            for y in [-1, 0, 1]:
                try:
                    coord1, coord2 = i2+x, j2+y
                    if coord1 < 0: continue
                    if coord2 < 0: continue
                    
                    if grid[coord1][coord2] and labels[coord1][coord2] == 0:
                        # print("S", coord1, coord2, labels)
                        labels[coord1][coord2] = lab
                        # print("F", coord1, coord2, labels)
                        stack.append((coord1, coord2))
                except IndexError:
                    pass

num_labels = 0
for i in range(num_rows):
    for j in range(num_columns):
        # print(i, j, labels[i][j], grid[i][j])
        if grid[i][j] and labels[i][j] == 0:
            num_labels += 1
            set_grid(i, j, num_labels)

print(num_labels)