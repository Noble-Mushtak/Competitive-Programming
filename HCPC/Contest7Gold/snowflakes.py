import sys

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))
for l in range(test_cases):
    num_nums = int(next(lines))
    last_index = {}
    last_index_still_being_updated = 0
    preanswers = [0]*(num_nums+1)
    for i in range(num_nums):
        cur_num = int(next(lines))
        if cur_num in last_index:
            last_index_still_being_updated = max(last_index_still_being_updated, last_index[cur_num]+1)
        # for j in range(last_index_still_being_updated, i+1): answers[j] += 1
        preanswers[last_index_still_being_updated] += 1
        preanswers[i+1] -= 1
        last_index[cur_num] = i
    answer = 0
    cur_sum = 0
    for i in range(num_nums):
        cur_sum += preanswers[i]
        answer = max(cur_sum, answer)
    print(answer)