import sys

def num_factors(num, factor):
    answer = 0
    while num % factor == 0:
        answer += 1
        num //= factor
    return answer

lines = (line for line in sys.stdin.read().split("\n"))
num2s = 0
num5s = 0
no2sand5s = 1
answers = []
for test_case in range(1, 1000001):
    num2s += num_factors(test_case, 2)
    num5s += num_factors(test_case, 5)
    new_num = test_case
    while (new_num % 2) == 0: new_num //= 2
    while (new_num % 5) == 0: new_num //= 5
    no2sand5s *= new_num
    no2sand5s %= 10
    min2and5s = min(num2s, num5s)
    answers.append((no2sand5s*2**(num2s-min2and5s)*5**(num5s-min2and5s)) % 10)
    # print(test_case, answers[-1])