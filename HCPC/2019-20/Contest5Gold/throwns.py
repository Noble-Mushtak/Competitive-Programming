from __future__ import print_function
import sys

lines = sys.stdin.read().split("\n")
tokens0 = lines[0].split(" ")
num_students = int(tokens0[0])
stack = []
tokens1 = (token for token in lines[1].split(" "))

try:
    while True:
        next_command = next(tokens1)
        if next_command == "undo":
            num = int(next(tokens1))
            for i in range(num): stack.pop()
        else:
            stack.append(int(next_command))
except:
    pass

answer = sum(stack) % num_students
if answer < 0: answer += num_students
print(answer)