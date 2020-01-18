import sys
from math import *

"""
y-y1 = (y2-y1) / (x2-x1) * (x - x1)
(x2-x1)*y -y1*(x2-x1) = (y2-y1) * x - x1*(y2-y1)
(y1-y2)*x + (x2-x1)*y = y1*(x2-x1) - x1*(y2-y1)
(y1-y2)*x + (x2-x1)*y = y1*x2 - x1*y2
"""

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))

def distance(A, B, C, x, y):
    return abs(A*x+B*y-C)/sqrt(A*A+B*B)

def get_city(pair):
    return pair[0]

def get_dist(pair):
    return pair[1]

for i in range(test_cases):
    words = next(lines).split(" ")
    x1 = int(words[0])
    y1 = int(words[1])
    x2 = int(words[2])
    y2 = int(words[3])
    
    A = y1-y2
    B = x2-x1
    C = y1*x2-x1*y2
    
    num_lines = int(next(lines))
    cities = []
    worst_distance = -1
    for j in range(num_lines):
        words = next(lines).split(" ")
        city_name = words[0]
        city_x = int(words[1])
        city_y = int(words[2])
        dist = distance(A, B, C, city_x, city_y)
        if (worst_distance < 0) or (dist < worst_distance-1e-5):
            cities = [city_name]
            worst_distance = dist
        elif dist < worst_distance+1e-5:
            cities.append(city_name)
    print(" ".join(cities))
    