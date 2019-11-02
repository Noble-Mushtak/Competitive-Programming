import sys
edge_list = {}
def add_edge(start, end):
    if start not in edge_list:
        edge_list[start] = [end]
    else:
        edge_list[start].append(end)

lines = (line for line in sys.stdin.read().split("\n"))
num_paths = int(next(lines))
for i in range(num_paths):
    tokens = next(lines).split()
    add_edge(tokens[0], tokens[1])

visited_so_far = []
memoed = {}
def dfs(vertex):
    global visited_so_far
    visited_so_far.append(vertex)
    if vertex in edge_list:
        for new_vertex in edge_list[vertex]:
            if new_vertex in visited_so_far:
                return True
            elif dfs(new_vertex):
                return True
    visited_so_far.pop()
    memoed[vertex] = False

for line in lines:
    if line == "": continue
    visited_so_far = []
    if dfs(line): print line, "safe"
    else: print line, "trapped"