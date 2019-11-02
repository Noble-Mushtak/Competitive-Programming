import sys
staff = ["G: ", "F: ", "E: ", "D: ", "C: ", "B: ", "A: ", "g: ", "f: ", "e: ", "d: ", "c: ", "b: ", "a: "]
hyphens = ["F", "D", "B", "g", "e", "a"]

notes_info = sys.stdin.read().split()
notes_info = notes_info[1:]
num_spaces = 0
beg = False
for note_info in notes_info:
    if beg:
        for i, line in enumerate(staff):
            if line[0] in hyphens: staff[i] += "-"
            else: staff[i] += " "
    else: beg = True
    if len(note_info) == 1: note_info += "1"
    note = note_info[0]
    duration = int(note_info[1])
    for i, line in enumerate(staff):
        if line[0] == note:
            staff[i] += "*"*duration
        else:
            if line[0] in hyphens: staff[i] += "-"*duration
            else: staff[i] += " "*duration
print("\n".join(staff)) 