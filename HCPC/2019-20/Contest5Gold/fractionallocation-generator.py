from __future__ import print_function
import sys

for denominator in range(1, 10001):
    test = denominator+1
    answer = 0
    while True:
        test2 = (denominator*test)//(test-denominator)
        if test2 < test: break
        if ((denominator*test) % (test-denominator)) == 0: answer += 1
        test += 1
    print(answer)
