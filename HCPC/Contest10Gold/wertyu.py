import sys

keyboard = [
    "`1234567890-=",
    "QWERTYUIOP[]\\",
    "ASDFGHJKL;'",
    "ZXCVBNM,./"
]
def translate(chr):
    if chr == " ": return " "
    for row in keyboard:
        try:
            return row[row.index(chr)-1]
        except:
            pass
    print("NO: ", char)
    sys.exit(1)

lines = sys.stdin.read().split("\n")
for line in lines:
    if line == "": continue
    new_line = ""
    for char in line:
        new_line += translate(char)
    print(new_line)