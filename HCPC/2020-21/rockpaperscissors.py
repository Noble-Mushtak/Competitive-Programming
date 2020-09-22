import sys

lines = ((token for token in line.split()) for line in sys.stdin.read().split("\n"))

def word_to_int(word):
    if word == "rock": return 0
    if word == "paper": return 1
    if word == "scissors": return 2
    raise ValueError("The word "+word+" is invalid")

completed_test_case_before = False

while True:
    first_line = next(lines)
    num_players = int(next(first_line))
    if num_players == 0:
        break
    num_games_per_pair = int(next(first_line))
    
    wins = [0]*num_players
    losses = [0]*num_players
    
    num_games = num_games_per_pair*num_players*(num_players-1)//2
    for i in range(num_games):
        game_line = next(lines)
        first_player_index = int(next(game_line))-1
        first_player_choice = word_to_int(next(game_line))
        second_player_index = int(next(game_line))-1
        second_player_choice = word_to_int(next(game_line))
        
        choice_diffs = second_player_choice-first_player_choice
        if choice_diffs < 0:
            choice_diffs += 3
        
        if choice_diffs == 1:
            wins[second_player_index] += 1
            losses[first_player_index] += 1
        elif choice_diffs == 2:
            wins[first_player_index] += 1
            losses[second_player_index] += 1
    
    if completed_test_case_before: print()
    for i in range(num_players):
        if wins[i]+losses[i] == 0:
            print("-")
        else:
            win_average = wins[i]/(wins[i]+losses[i])
            print("{:.3f}".format(win_average))
    
    completed_test_case_before = True