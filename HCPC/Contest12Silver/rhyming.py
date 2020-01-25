from __future__ import print_function
import sys

def matches_suffix(message, suffix):
    num_letters = len(suffix)
    if len(message) < num_letters: return False
    return message[-num_letters:] == suffix

lines = (line for line in sys.stdin.read().split("\n"))
word = next(lines)

num_sets = int(next(lines))
desired_endings = []
for i in range(num_sets):
    endings = next(lines).split(" ")
    for ending in endings:
        if matches_suffix(word, ending):
            desired_endings += endings
            break

num_guesses = int(next(lines))
for j in range(num_guesses):
    phrase = next(lines)
    answer = False
    for ending in desired_endings:
        if matches_suffix(phrase, ending):
            answer = True
            break
    print("YES" if answer else "NO")