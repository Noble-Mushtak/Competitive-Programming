import sys

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))
for i in range(test_cases):
    num_distances = int(next(lines))
    distances = [int(x) for x in next(lines).split()]
    old_distances = [[(0, 0)]+[None]*1000]
    for dist in distances:
        new_distances = [None]*1001
        
        def update_distance(cur_dist, od, old_dist):
            if cur_dist < 0: return
            if cur_dist > 1000: return
            max_height = max(cur_dist, old_dist[1])
            if (new_distances[cur_dist] == None) or (new_distances[cur_dist][1] > max_height): new_distances[cur_dist] = (i, max_height)
        
        for i in range(1001):
            if old_distances[-1][i] != None:
                update_distance(i-dist, i, old_distances[-1][i])
                update_distance(i+dist, i, old_distances[-1][i])
        old_distances.append(new_distances)
    if old_distances[-1][0] == None: print("IMPOSSIBLE")
    else:
        cur_height = 0
        answer = ""
        for i in range(1, len(old_distances)):
            if old_distances[-i][cur_height][0] > cur_height: answer = "D"+answer
            else: answer = "U"+answer
            cur_height = old_distances[-i][cur_height][0]
        print(answer)