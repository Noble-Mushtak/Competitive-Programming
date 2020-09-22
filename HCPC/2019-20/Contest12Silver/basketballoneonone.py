import sys
lines = sys.stdin.read().split("\n")
game = lines[0]
score = [0, 0]
for i in range(0, len(game), 2):
    player = 0 if game[i] == "A" else 1
    points = int(game[i+1])
    score[player] += points
    if (score[player] >= 11) and (score[player]-score[1-player] >= 2):
        print("A" if player == 0 else "B")
        break