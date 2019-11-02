ops = ["+", "-", "/", "*"]

answers = {}
for x in ops:
    for y in ops:
        for z in ops:
            answer = int(eval("4"+x+"4"+y+"4"+z+"4"))
            answers[answer] = " ".join(["4", x, "4", y, "4", z, "4", "=", str(answer)])

import sys
tokens = (token for token in sys.stdin.read().split())
num_queries = int(next(tokens))
for i in range(num_queries):
    try:
        print(answers[int(next(tokens))])
    except KeyError:
        print("no solution")