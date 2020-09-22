import sys

def valid(seq, ind):
    if len(seq) < ind-1: return False
    if (len(seq) > ind-1) and (seq[ind-1] != 0): return False
    for i in seq[:(ind-1)]:
        if i == 0: return False
    return True

answers = [[]]
for i in range(1, 2001):
    for j in range(1, i+1):
        if valid(answers[i-1], j):
            answers.append([x-1 for x in answers[i-1][:(j-1)]]+[j]+answers[i-1][j:])
            break
    else:
        print(i)

def print_answer(seq):
    while len(seq) > 0:
        if len(seq) < 10:
            print(" ".join([str(i) for i in seq]))
            break
        print(" ".join([str(i) for i in seq[:10]]))
        seq = seq[10:]

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))
for line in range(test_cases):
    tokens = next(lines).split()
    test_case = int(tokens[0])
    query = int(tokens[1])
    print test_case, len(answers[query])
    print_answer(answers[query])