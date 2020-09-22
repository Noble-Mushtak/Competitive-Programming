from __future__ import print_function
import sys

keypad = {
    "a": (2, 1),
    "b": (2, 2),
    "c": (2, 3),
    "d": (3, 1),
    "e": (3, 2),
    "f": (3, 3),
    "g": (4, 1),
    "h": (4, 2),
    "i": (4, 3),
    "j": (5, 1),
    "k": (5, 2),
    "l": (5, 3),
    "m": (6, 1),
    "n": (6, 2),
    "o": (6, 3),
    "p": (7, 1),
    "q": (7, 2),
    "r": (7, 3),
    "s": (7, 4),
    "t": (8, 1),
    "u": (8, 2),
    "v": (8, 3),
    "w": (9, 1),
    "x": (9, 2),
    "y": (9, 3),
    "z": (9, 4),
    " ": (0, 1)
}

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))

for i in range(test_cases):
    message = next(lines)
    answer = ""
    last_num = -1
    for ch in message:
        encoded = keypad[ch]
        if encoded[0] == last_num: answer += " "
        answer += "".join([str(encoded[0])]*encoded[1])
        last_num = encoded[0]
    print("Case #"+str(i+1)+":", answer)