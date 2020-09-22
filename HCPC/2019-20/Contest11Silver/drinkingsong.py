import sys

template = """N_TOKEN bottles of WORD_TOKEN on the wall, N_TOKEN bottles of WORD_TOKEN.
Take one down, pass it around, K_TOKEN bottles of WORD_TOKEN on the wall."""

def fill_in(n, word):
    if n == 2:
        return word.join((str(n-1)+" bottle").join(str(n).join(template.split("N_TOKEN")).split("K_TOKEN bottles")).split("WORD_TOKEN"))
    if n == 1:
        return ("no more bottles of "+word).join("Take it down".join(word.join("no more".join((str(n)+" bottle").join(template.split("N_TOKEN bottles")).split("K_TOKEN")).split("WORD_TOKEN")).split("Take one down")).split("no more bottles of "+word+" on the wall"))
    return word.join(str(n-1).join(str(n).join(template.split("N_TOKEN")).split("K_TOKEN")).split("WORD_TOKEN"))

lines = sys.stdin.read().split("\n")
start = int(lines[0])
word = lines[1]

for cur in range(start, 0, -1):
    print(fill_in(cur, word))
    if cur > 1: print("")