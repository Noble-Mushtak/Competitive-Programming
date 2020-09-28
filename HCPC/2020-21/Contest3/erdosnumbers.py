import sys
import queue

paul = "PAUL_ERDOS"

lines = (line for line in sys.stdin.read().split("\n"))
edges = {}
dists = {}
authors = []
for line in lines:
    if line == "": continue
    names = line.split()
    author = names[0]
    authors.append(author)
    if author not in edges:
        edges[author] = []
    for name2 in names[1:]:
        if name2 not in edges:
            edges[name2] = []
        edges[author].append(name2)
        edges[name2].append(author)


marked = set()
marked.add(paul)

q = queue.Queue()
q.put(paul)
dists[paul] = 0
while not q.empty():
    cur_name = q.get()
    for other in edges[cur_name]:
        if other not in marked:
            dists[other] = dists[cur_name]+1
            q.put(other)
            marked.add(other)

for author in authors:
    if author in dists:
        print(author, dists[author])
    else:
        print(author, "no-connection")