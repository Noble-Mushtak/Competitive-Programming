import sys

def reverse_str(s):
    return "".join(list(reversed(s)))

answers = []
lines = sys.stdin.read().split("\n")
test_case = lines[0]
for i in range(len(test_case)-1):
    str1 = test_case[:i+1]
    for j in range(i+1, len(test_case)-1):
        str2 = test_case[i+1:j+1]
        str3 = test_case[j+1:]
        if str1+str2+str3 != test_case:
            print(str1, str2, str3)
            sys.exit(1)
        answers.append(reverse_str(str1)+reverse_str(str2)+reverse_str(str3))

print(sorted(answers)[0])