from __future__ import print_function
import sys

lines = sys.stdin.read().split("\n")
target = int(lines[0])

def print_score(num):
    if (num % 3) == 0:
        print("triple", num//3)
    elif (num % 2) == 0:
        print("double", num//2)
    else:
        print("single", num)

scores = list(range(1, 21))
real_scores = []
for score in scores:
    real_scores.append(score)
    real_scores.append(2*score)
    real_scores.append(3*score)

for score1 in real_scores:
    if score1 == target:
        print_score(score1)
        sys.exit(0)
    for score2 in real_scores:
        if score1+score2 == target:
            print_score(score1)
            print_score(score2)
            sys.exit(0)
        for score3 in real_scores:
            if score1+score2+score3 == target:
                print_score(score1)
                print_score(score2)
                print_score(score3)
                sys.exit(0)
print("impossible")