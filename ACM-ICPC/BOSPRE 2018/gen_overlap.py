import sys
import random

random.seed(0)
print("--- SAMPLE 1 ---")
num = 10**int(sys.argv[1])
min = -10**15
max = 10**15
for i in range(num):
    minX, minY = random.randint(min, max-10), random.randint(min, max-10)
    maxX, maxY = random.randint(minX+1, max), random.randint(minY+1, max)
    print(minX, maxX, minY, maxY)
print("*")