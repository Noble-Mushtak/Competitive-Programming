from __future__ import print_function
import sys

lines = (line for line in sys.stdin.read().split("\n"))

lower = [0]
upper = [11]
while True:
    guess = int(next(lines))
    if guess == 0: break
    
    verdict = next(lines)
    if verdict == "right on":
        if max(lower) < guess and min(upper) > guess:
            print("Stan may be honest")
        else:
            print("Stan is dishonest")
        lower = [0]
        upper = [11]
    elif verdict == "too low":
        lower.append(guess)
    elif verdict == "too high":
        upper.append(guess)