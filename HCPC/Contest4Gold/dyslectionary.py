import sys

lines = [line for line in sys.stdin.read().split("\n")]
words = []
beg = True
for line in lines:
    if line == "":
        max_length = max([len(s) for s in words])
        words = sorted(words, key=lambda s: "".join(reversed(s)))
        for word in words:
            print(" "*(max_length-len(word))+word)
        
        words = []
    else:
        if (len(words) == 0) and (not beg): print("")
        words.append(line)

    beg = False