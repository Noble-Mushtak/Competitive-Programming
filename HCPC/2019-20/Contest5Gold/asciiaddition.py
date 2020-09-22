from __future__ import print_function
import sys

zero = """xxxxx
x...x
x...x
x...x
x...x
x...x
xxxxx"""
one = """....x
....x
....x
....x
....x
....x
....x"""
two = """xxxxx
....x
....x
xxxxx
x....
x....
xxxxx"""
three = """xxxxx
....x
....x
xxxxx
....x
....x
xxxxx"""
four = """x...x
x...x
x...x
xxxxx
....x
....x
....x"""
five = """xxxxx
x....
x....
xxxxx
....x
....x
xxxxx"""
six = """xxxxx
x....
x....
xxxxx
x...x
x...x
xxxxx"""
seven = """xxxxx
....x
....x
....x
....x
....x
....x"""
eight = """xxxxx
x...x
x...x
xxxxx
x...x
x...x
xxxxx"""
nine = """xxxxx
x...x
x...x
xxxxx
....x
....x
xxxxx"""
plus = """.....
..x..
..x..
xxxxx
..x..
..x..
....."""

translate = { zero: "0", one: "1", two: "2", three: "3", four: "4", five: "5", six: "6", seven: "7", eight: "8", nine: "9", plus: "+" }
detranslate = {"0": zero, "1": one, "2": two, "3": three, "4": four, "5": five, "6": six, "7": seven, "8": eight, "9": nine }

lines = sys.stdin.read().split("\n")
def read_num(index):
    collector = ""
    for line in lines:
        if line == "": break
        collector += line[index*6:index*6+5]+"\n"
    return translate[collector[:-1]]

num_nums = len(lines[0])//6+1
expr = ""
for i in range(num_nums): expr += read_num(i)
answer = str(eval(expr))
lines = [""]*7
for i, char in enumerate(answer):
    for j in range(7):
        segment = detranslate[char][j*6:j*6+5]
        if i > 0: segment = "."+segment
        lines[j] += segment
print("\n".join(lines))