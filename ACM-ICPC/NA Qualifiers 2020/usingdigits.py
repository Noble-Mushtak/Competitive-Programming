import sys
from queue import PriorityQueue

lines = (line for line in sys.stdin.read().split("\n"))

first_line = [int(x) for x in next(lines).split()]
num_cols = first_line[0]
num_rows = first_line[1]

code = next(lines)

grid = []
for i in range(num_rows):
    grid.append([])
    line = next(lines)
    for j in range(num_cols):
        grid[-1].append(int(line[j]))

start = (0, num_rows-1, 0)
end = (num_cols-1, 0, None)

visited = set()

distance = {}
distance[start] = grid[start[1]][start[0]]

queue = PriorityQueue()
queue.put((distance[start], start))

def valid_loc(x, y):
    if x < 0:
        return False
    if y < 0:
        return False
    if x >= num_cols:
        return False
    if y >= num_rows:
        return False
    return True

def neighbors(node):
    x, y, code_ind = node
    neighbors = [(x+1, y, code_ind), (x, y-1, code_ind)]
    if code_ind < len(code):
        cur_hop = int(code[code_ind])
        neighbors.append((x+cur_hop+1, y, code_ind+1))
        neighbors.append((x, y-cur_hop-1, code_ind+1))
    return neighbors

best_dist = None

while not queue.empty():
    dist, cur_v = queue.get()
    if cur_v in visited:
        continue
    
    x, y, code_ind = cur_v
    # print(x, y, code_ind, dist)
    if x == num_cols-1 and y == 0:
        # print(dist)
        if best_dist == None:
            best_dist = dist
        else:
            best_dist = min(best_dist, dist)
    
    for node in neighbors(cur_v):
        x2, y2, code_ind2 = node
        if not valid_loc(x2, y2):
            continue
        
        alt_dist = distance[cur_v] + grid[y2][x2]
        if node not in distance or alt_dist < distance[node]:
            distance[node] = alt_dist
            queue.put((distance[node], node))

print(best_dist)
