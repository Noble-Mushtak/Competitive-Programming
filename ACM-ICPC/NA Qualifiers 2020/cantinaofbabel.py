import sys

lines = (line for line in sys.stdin.read().split("\n"))

num_players = int(next(lines))
player_speaks = {}
player_understands = {}
for i in range(num_players):
    tokens = next(lines).split()
    player_name = tokens[0]
    player_lang = tokens[1]
    player_speaks[player_name] = player_lang
    player_understands[player_name] = set(tokens[1:])

player_understands_player = {}
for pl1 in player_speaks.keys():
    player_understands_player[pl1] = []
    for pl2, pl2_lang in player_speaks.items():
        if pl1 != pl2 and (pl2_lang in player_understands[pl1]):
            player_understands_player[pl1].append(pl2)

visited = {}
for pl in player_speaks.keys():
    visited[pl] = False
L = []

def visit(pl):
    if not visited[pl]:
        visited[pl] = True
        for pl2 in player_understands_player[pl]:
            visit(pl2)
        L.insert(0, pl)

for pl in player_speaks.keys():
    visit(pl)

components = {}
added_to_component = set()
    
def assign(pl, root_pl):
    if pl not in added_to_component:
        components[root_pl].append(pl)
        added_to_component.add(pl)
        for pl2 in player_speaks.keys():
            if pl in player_understands_player[pl2]:
                assign(pl2, root_pl)
    
for pl in L:
    if pl not in added_to_component:
        components[pl] = []
        assign(pl, pl)

largest_component_size = 0
for pl, comp in components.items():
    largest_component_size = max(len(comp), largest_component_size)
print(num_players - largest_component_size)
