import sys

lines = (line for line in sys.stdin.read().split("\n"))

magic_words = "Simon says"

num_lines = int(next(lines))
for i in range(num_lines):
    command = next(lines)
    if command.startswith(magic_words):
        print(command[len(magic_words):])