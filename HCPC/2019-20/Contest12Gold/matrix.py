from __future__ import print_function
import sys

lines = sys.stdin.read().split("\n")
if len(lines) % 3 != 1:
    print("WHAT IS GOING ON?!?!?!")
    sys.exit(1)

for i in range(len(lines)/3):
    line1 = lines[3*i]
    point1 = [int(x) for x in line1.split(" ")]
    line2 = lines[3*i+1]
    point2 = [int(x) for x in line2.split(" ")]
    
    det = point1[0]*point2[1]-point1[1]*point2[0]
    print("Case "+str(i+1)+":")
    print(point2[1]/det, -point1[1]/det)
    print(-point2[0]/det, point1[0]/det)