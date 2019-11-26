from __future__ import print_function
import sys

lines = sys.stdin.read().split("\n")
for line in lines:
    if line == "": break
    numer, denom, num_digits = [int(x) for x in line.split()]
    print("0.", end="")
    for i in range(num_digits):
        numer *= 10
        print(numer//denom, end="")
        numer %= denom
    print("")