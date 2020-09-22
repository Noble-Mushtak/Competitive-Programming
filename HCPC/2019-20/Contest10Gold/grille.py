import sys

def rotate(gr):
    new_gr = []
    for i, row in enumerate(gr):
        new_gr.append([])
        for j in range(len(gr)):
            new_gr[-1].append(gr[j][len(gr)-i-1])
    return new_gr

def translate(gr):
    answer = []
    for i in range(len(gr)):
        for j in range(len(gr)):
            if gr[i][j]: answer.append((i, j))
    return answer

def validate(translations):
    union = set()
    for t in translations: union = union.union(t)
    return (len(union) == num_lines**2) and (sum([len(x) for x in translations]) == num_lines**2)

lines = (line for line in sys.stdin.read().split("\n"))
num_lines = int(next(lines))
grille = []
for i in range(num_lines):
    row = next(lines)
    grille.append([ch == "." for ch in row])
grilles = [grille]
for i in range(3): grilles.append(rotate(grilles[-1]))
store1 = grilles[1]
store2 = grilles[3]
grilles[1] = store2
grilles[3] = store1
grilles = map(translate, grilles)

encoded = next(lines)

if validate(grilles):
    answer = [""]*(num_lines**2)
    counter = 0
    encountered = set()
    for gr in grilles:
        for i, j in gr:
            if (i, j) not in encountered:
                answer[num_lines*i+j] = encoded[counter]
                counter += 1
                encountered.add((i, j))
    for ch in answer:
        if ch == "": sys.exit(1)
    print("".join(answer))
else:
    print("invalid grille")
