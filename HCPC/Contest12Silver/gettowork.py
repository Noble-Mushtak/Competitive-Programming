from __future__ import print_function
import sys

lines = (line for line in sys.stdin.read().split("\n"))
test_cases = int(next(lines))
for z in range(test_cases):
    main_line = next(lines).split()
    num_towns = int(main_line[0])
    main_town = int(main_line[1])

    num_employees = int(next(lines))
    employee_map = {}
    for j in range(num_employees):
        new_line = next(lines).split()
        cur_town = int(new_line[0])
        num_passengers = int(new_line[1])
        if cur_town not in employee_map:
            employee_map[cur_town] = [num_passengers]
        else:
            employee_map[cur_town].append(num_passengers)
            
    answers = []
    for i in range(1, num_towns+1):
        if (i == main_town) or (i not in employee_map):
            answers.append(0)
            continue
        else:
            all_cars = list(sorted(employee_map[i], reverse=True))
            num_cars = 0
            while len(all_cars) > 0:
                num_passengers = all_cars[0]
                if num_passengers == 0:
                    break
                num_cars += 1
                all_cars = all_cars[1:]
                for y in range(num_passengers-1):
                    if len(all_cars) > 0:
                        all_cars = all_cars[:-1]
            if len(all_cars) > 0:
                answers.append(-1)
            else:
                answers.append(num_cars)
    if min(answers) == -1: answer_str = "IMPOSSIBLE"
    else: answer_str = " ".join([str(n) for n in answers])
    print("Case #"+str(z+1)+": "+answer_str)