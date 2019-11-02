def sum(num):
    if num == 0: return 0
    return sum(num//10)+(num % 10)

import sys
tokens = (token for token in sys.stdin.read().split())
while True:
    query = int(next(tokens))
    if query == 0: break
    
    for i in range(11, 1000):
        if sum(query) == sum(i*query):
            print(i)
            break