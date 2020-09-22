import sys
morse_code = {
 "A": ".-",
 "B": "-...",
 "C": "-.-.",
 "D": "-..",
 "E": ".",
 "F": "..-.",
 "G": "--.",
 "H": "....",
 "I": "..",
 "J": ".---",
 "K": "-.-",
 "L": ".-..",
 "M": "--",
 "N": "-.",
 "O": "---",
 "P": ".--.",
 "Q": "--.-",
 "R": ".-.",
 "S": "...",
 "T": "-",
 "U": "..-",
 "V": "...-",
 "W": ".--",
 "X": "-..-",
 "Y": "-.--",
 "Z": "--..",
 "_": "..--",
 ",": ".-.-",
 ".": "---.",
 "?": "----"
}

def encode_str(str):
   if str == "": return "", []
   answer1, answer2 = encode_str(str[1:])
   return morse_code[str[0]]+answer1, [len(morse_code[str[0]])]+answer2

def decode_str(str, seq):
    if str == "": return ""
    first = str[:seq[0]]
    letter = None
    for i, k in morse_code.items():
        if k == first:
            letter = i
    if letter == None: sys.exit(1)
    return letter+decode_str(str[seq[0]:], seq[1:])

lines = (line for line in sys.stdin.read().split())
for line in lines:
    encoded, sequence = encode_str(line)
    # print(encoded, sequence)
    sequence = list(reversed(sequence))
    print(decode_str(encoded, sequence))