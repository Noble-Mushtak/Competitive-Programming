from __future__ import print_function
import sys

lines = (line for line in sys.stdin.read().split("\n"))

for line in lines:
    if line == "": break
    
    balls = [int(x) for x in line]
    if (sum(balls) % len(balls)) != 0:
        print(line+": invalid # of balls")
        continue

    num_balls = sum(balls)//len(balls)
    times = sum(balls)*num_balls*2
    catch_times = set()
    for i in range(times):
        new_catch_time = i+balls[i % len(balls)]
        if new_catch_time in catch_times:
            print(line+": invalid pattern")
            break
        catch_times.add(new_catch_time)
    else:
        print(line+": valid with", num_balls, "balls")