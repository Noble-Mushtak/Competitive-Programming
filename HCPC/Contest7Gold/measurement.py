import sys

prefactors = [1, 1000, 12, 3, 22, 10, 8, 3]
factors = []
prod = 1
for el in prefactors:
    prod *= el
    factors.append(float(prod))

dict = [("thou", "th"), ("inch", "in"), ("foot", "ft"), ("yard", "yd"), ("chain", "ch"), ("furlong", "fur"), ("mile", "mi"), ("league", "lea")]
def find_index(str):
    for i, pair in enumerate(dict):
        if str == pair[0] or str == pair[1]: return i
    # ERROR
    lst = []
    print(lst[0])

lines = sys.stdin.read().split("\n")
test_case = lines[0].split()
num = int(test_case[0])
unit1 = find_index(test_case[1])
unit2 = find_index(test_case[3])
print(num*factors[unit1]/factors[unit2])