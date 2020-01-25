from __future__ import print_function
import sys

lines = (line for line in sys.stdin.read().split("\n"))
while True:
    nums = [int(x) for x in next(lines).split(" ")]
    if nums == [0, 0, 0]:
        break
    nums = list(sorted(nums))
    if (nums[0]*nums[0]+nums[1]*nums[1]) == nums[2]*nums[2]:
        print("right")
    else:
        print("wrong")