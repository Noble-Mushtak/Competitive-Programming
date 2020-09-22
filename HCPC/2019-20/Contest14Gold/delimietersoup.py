from __future__ import print_function
import sys

opens = ['(', '[', '{']
closeds = [')', ']', '}']

def match(open, closed):
    return opens.index(open) == closeds.index(closed)

lines = sys.stdin.read().split("\n")
num_letters = int(lines[0])
code = lines[1]

stack = []
for i, letter in enumerate(code):
    if letter in opens:
        stack.append(letter)
    if letter in closeds:
        if (len(stack) == 0) or (not match(stack[-1], letter)):
            print(letter, i)
            sys.exit(0)
        else:
            stack.pop()

print("ok so far")
