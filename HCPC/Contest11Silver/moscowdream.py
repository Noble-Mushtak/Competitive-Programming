import sys
lines = sys.stdin.read().split("\n")
words = lines[0].split()
a = int(words[0])
b = int(words[1])
c = int(words[2])
n = int(words[3])
if (a >= 1) and (b >= 1) and (c >= 1) and (a+b+c >= n) and (n >= 3):
    print("YES")
else:
    print("NO")