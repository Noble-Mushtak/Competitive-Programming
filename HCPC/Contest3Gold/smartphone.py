import sys

def lcp(str1, str2):
    answer = ""
    for i in range(len(str1)):
        if i >= len(str2): break
        if str1[i] == str2[i]: answer += str1[i]
        else: break
    return answer

lines = (line for line in sys.stdin.read().split())
test_cases = int(next(lines))
for i in range(test_cases):
    desired_word = next(lines)
    words = [next(lines), next(lines), next(lines), next(lines)]
    answer = 10000000
    for i, word in enumerate(words):
        cur_lcp = lcp(word, desired_word)
        test_answer = int(i != 0)+len(word)-len(cur_lcp)+len(desired_word)-len(cur_lcp)
        answer = min(answer, test_answer)
    print(answer)