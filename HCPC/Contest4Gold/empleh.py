import sys
lines = [line for line in sys.stdin.read().split("\n")]
dictionary = {}
for i in range(8):
    for j in range(8):
        dictionary[(i, j)] = None
for i, line in enumerate(lines):
    if i >= 2: break
    tokens = line.split(" ")
    if len(tokens[1]) == 0: continue
    list = tokens[1].split(",")
    for str in list:
        if len(str) == 2: str = "P"+str
        dictionary[(ord(str[1])-ord("a"), 7-(ord(str[2])-ord("1")))] = (str[0], i)

bound = "+---+---+---+---+---+---+---+---+"
for j in range(8):
    print(bound)
    for i in range(8):
        print("|", end="")
        if ((i+j) & 1) == 1: print(":", end="")
        else: print(".", end="")
        if dictionary[(i, j)] == None:
            if ((i+j) & 1) == 1: print(":", end="")
            else: print(".", end="")
        elif dictionary[(i, j)][1] == 0:
            print(dictionary[(i, j)][0], end="")
        else:
            print(dictionary[(i, j)][0].lower(), end="")
        if ((i+j) & 1) == 1: print(":", end="")
        else: print(".", end="")
    print("|")
print(bound)