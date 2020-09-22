import sys

letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_."

def encode(num, message):
    new_message = ""
    for ch in message:
        try:
            new_message += letters[(letters.index(ch)+num) % len(letters)]
        except IndexError:
            print("Oh noes")
    return "".join(reversed(new_message))

lines = sys.stdin.read().split("\n")
for line in lines:
    if line == "0":
        break
    words = line.split()
    rot = int(words[0])
    message = words[1]
    print(encode(rot, message))