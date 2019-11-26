import sys

expr = sys.stdin.read().split("\n")[0]

def find_matching_paren(ind):
    num_parens_so_far = 0
    for i in range(ind+1, len(expr)):
        if expr[i] == "(": num_parens_so_far += 1
        if expr[i] == ")":
            if num_parens_so_far == 0: return i
            num_parens_so_far -= 1
    print(i)
    sys.exit(1)

labels = [-1]*len(expr)
num_labels = 0
for i in range(len(expr)):
    if expr[i] == "(":
        matching_ind = find_matching_paren(i)
        labels[i] = num_labels
        labels[matching_ind] = num_labels
        num_labels += 1

answers = []
for bs in range(2**num_labels-1):
    new_line = ""
    for i in range(len(expr)):
        if (labels[i] == -1) or ( ((bs >> labels[i]) & 1) > 0):
            new_line += expr[i]
    answers.append(new_line)
answers = sorted(list(set(answers)))
for line in answers: print(line)