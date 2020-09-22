from __future__ import print_function
import sys

def num_times(S, L):
    answer = 0
    for i in range(len(L)-len(S)+1):
        if S == L[i:i+len(S)]: answer += 1
    return answer

lines = sys.stdin.read().split("\n")
for line in lines:
    if line == "0":
        break
    words = line.split()
    S = words[0]
    L = words[1]
    answer1 = num_times(S, L)
    answer2 = 0
    substrings = set()
    for i in range(len(S)):
        newS = S[:i]+S[(i+1):]
        substrings.add(newS)
    for string in substrings:
        answer2 += num_times(string, L)
    answer3 = 0
    superstrings = set()
    for i in range(len(S)+1):
        for z in range(26):
            new_letter = chr(ord("A")+z)
            newS = S[:i]+new_letter+S[i:]
            superstrings.add(newS)
    for string in superstrings:
        answer3 += num_times(string, L)
    print(answer1, answer2, answer3)