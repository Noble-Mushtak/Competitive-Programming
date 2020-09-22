from __future__ import print_function
from math import factorial
import sys

lines = sys.stdin.read().split("\n")
for line in lines:
    if line == "": break
    num_letters = len(line)
    letter_counts = {}
    for ch in line:
        if ch in letter_counts: letter_counts[ch] += 1
        else: letter_counts[ch] = 1
    answer = factorial(num_letters)
    for ch in letter_counts: answer = answer//factorial(letter_counts[ch])
    print(answer)