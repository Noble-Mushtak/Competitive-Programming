import sys
from math import *

numbers = [float(x) for x in sys.stdin.read().split()]
area = numbers[0]
perimeter = numbers[1]
radius = sqrt(area/pi)
needed_perimeter = 2*pi*radius
if needed_perimeter <= perimeter-1e-6: print("Diablo is happy!")
else: print("Need more materials!")