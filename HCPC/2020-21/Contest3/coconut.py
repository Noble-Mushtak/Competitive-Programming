import sys

tokens = sys.stdin.read().split()
num_syllables = int(tokens[0])
num_players = int(tokens[1])

hands = [(0, i+1) for i in range(num_players)]
cur_ind = 0
while len(hands) > 1:
    cur_ind += num_syllables-1
    cur_ind %= len(hands)
    if hands[cur_ind][0] == 0:
        hands[cur_ind] = (1, hands[cur_ind][1])
        hands.insert(cur_ind, (1, hands[cur_ind][1]))
    elif hands[cur_ind][0] == 1:
        hands[cur_ind] = (2, hands[cur_ind][1])
        cur_ind += 1
    elif hands[cur_ind][0] == 2:
        del hands[cur_ind]
        cur_ind %= len(hands)
print(hands[0][1])