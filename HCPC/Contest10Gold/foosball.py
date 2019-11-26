from __future__ import print_function
import sys

lines = sys.stdin.read().split("\n")
num_players = int(lines[0])
names = lines[1].split()
points = lines[2]

dynasties = []
cur_dynasty = None
cur_dynasty_team = None
cur_dynasty_len = 0
teams = {
    "W": (names[0], names[2]),
    "B": (names[1], names[3])
}
cur_line = names[4:]
opposite = {
    "W": "B",
    "B": "W"
}

def add_dynasty(curd, curdln):
    global dynasties
    if curd == None: return
    dynasties.append((curd[0], curd[1], curdln))

def switch_team(point):
    global teams
    teams[point] = (teams[point][1], teams[point][0])

def advance_team(point):
    global teams
    global cur_line
    # print("O", teams[point])
    head = cur_line[0]
    cur_line = cur_line[1:]+[teams[point][1]]
    teams[point] = (head, teams[point][0])
    # print(teams[point], cur_line)

for i, point in enumerate(points):
    if cur_dynasty_team == point:
        cur_dynasty_len += 1
    else:
        add_dynasty(cur_dynasty, cur_dynasty_len)
        if cur_dynasty == None: cur_dynasty = teams[point]
        else: cur_dynasty = (teams[point][1], teams[point][0])
        cur_dynasty_team = point
        cur_dynasty_len = 1
    switch_team(point)
    advance_team(opposite[point])
add_dynasty(cur_dynasty, cur_dynasty_len)

max_len = max(map(lambda x: x[2], dynasties))
answers = []
for dynasty in dynasties:
    if dynasty[2] == max_len:
        answers.append(dynasty)
for dynasty in answers:
    print(dynasty[0], dynasty[1])