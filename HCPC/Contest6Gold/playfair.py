import sys

lines = (line for line in sys.stdin.read().split("\n"))

key = next(lines).replace(" ", "").upper()
encoded = {}
decoded = {}

num_letters = 0
for letter in key:
    if letter not in encoded:
        encoded[letter] = (num_letters//5, num_letters % 5)
        num_letters += 1

for i in range(26):
    letter = chr(i+ord("A"))
    if letter == "Q": continue
    if letter not in encoded:
        encoded[letter] = (num_letters//5, num_letters % 5)
        num_letters += 1

for let, pair in encoded.items():
    decoded[pair] = let
    # print(let, pair)

message = [c for c in next(lines).replace(" ", "").upper()]
num_letters = 0
while num_letters < len(message):
    cur_letter = message[num_letters]
    if num_letters == len(message)-1:
        message.insert(num_letters+1, "X")
        continue
        
    next_letter = message[num_letters+1]
    cur_pair = encoded[cur_letter]
    next_pair = encoded[next_letter]
    if cur_letter == next_letter:
        message.insert(num_letters+1, "X")
    elif cur_pair[0] == next_pair[0]:
        message[num_letters] = decoded[(cur_pair[0], (cur_pair[1]+1) % 5)]
        message[num_letters+1] = decoded[(next_pair[0], (next_pair[1]+1) % 5)]
        num_letters += 2
    elif cur_pair[1] == next_pair[1]:
        message[num_letters] = decoded[((cur_pair[0]+1) % 5, cur_pair[1])]
        message[num_letters+1] = decoded[((next_pair[0]+1) % 5, next_pair[1])]
        num_letters += 2
    else:
        message[num_letters] = decoded[(cur_pair[0], next_pair[1])]
        message[num_letters+1] = decoded[(next_pair[0], cur_pair[1])]
        num_letters += 2
    # print(cur_letter, next_letter, cur_pair, next_pair, message[num_letters], message[num_letters+1])
print("".join(message))