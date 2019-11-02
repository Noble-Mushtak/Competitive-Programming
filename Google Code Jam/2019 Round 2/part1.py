import sys
def get_line():
    return tuple(int(x) for x in sys.stdin.readline().split())

'''
ax+by < cx+dy
(a-c)x < (d-b)y
x/y < (d-b)/(a-c)
'''

test_cases = get_line()[0]
weights = []
ratios = []

cur_ratio = 1
def key_func(tpl):
    return tpl[0]*cur_ratio+tpl[1]

for l in range(test_cases):
    num_molecules = get_line()[0]
    weights[:] = []
    for i in range(num_molecules): weights.append(get_line())
    all_orders = set()
    
    ratios[:] = []
    for i in range(num_molecules):
        for j in range(num_molecules):
            if weights[i][0] != weights[j][0]:
                ratios.append((weights[j][1]-weights[i][1])/(weights[i][0]-weights[j][0]))
    ratios.append(1e-10)
    ratios.append(1e10)
    
    for ratio in ratios:
        if ratio > 1e-11:
            cur_ratio = ratio-1e-11
            new_order = tuple(sorted(weights, key=key_func))
            print(new_order)
            all_orders.add(new_order)
    sys.stdout.write("Case #"+str(l+1)+": "+str(len(all_orders))+"\n")