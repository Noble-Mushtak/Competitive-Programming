input_nums = []
with open("exercise.in", "r") as file:
    input_nums = [int(x) for x in file.read().split()]

num_fields = input_nums.pop(0)
num_trails = input_nums.pop(0)
tree = []
for i in range(num_fields):
    tree.append([])
for i in range(num_fields-1):
    beg = input_nums.pop(0)-1
    end = input_nums.pop(0)-1
    tree[beg].append((end, i))
    tree[end].append((beg, i))

visited = []
for i in range(num_fields):
    visited.append(False)
paths = []
for i in range(num_fields):
    paths.append(set())
cur_path = set()
def dfs(vertex):
    global visited
    global paths
    global cur_path

    visited[vertex] = True
    paths[vertex] = cur_path.copy()
    for v2, e in tree[vertex]:
        if not visited[v2]:
            cur_path.add(e)
            dfs(v2)
            cur_path.remove(e)
dfs(0)

routes = 0
new_trails = []
for i in range(num_trails-num_fields+1):
    beg = input_nums.pop(0)-1
    end = input_nums.pop(0)-1
    new_trails.append((beg, end))
for i, tpl in enumerate(new_trails):
    beg1, end1 = tpl
    for tpl2 in new_trails[(i+1):]:
        beg2, end2 = tpl2
        if (beg1 != beg2) or (end1 != end2):
            test_set = (paths[beg1] | paths[end1]) & (paths[beg2] | paths[end2])
            if len(test_set) > 0: routes += 1

with open("exercise.out", "w") as file:
    print(routes, file=file)