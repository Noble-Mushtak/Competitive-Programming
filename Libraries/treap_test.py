import random
print("1000")
commands = ["S", "A", "R"]
for i in range(1000):
    command = random.randint(0, 2)
    if command == 2:
        print("R", random.randint(0, 10))
    else:
        print(commands[command], random.randint(0, 10), random.randint(0, 100))