from __future__ import print_function
import sys

lines = sys.stdin.read().split("\n")
variables = []
for i in range(26): variables.append(0)
def get_var(letter):
    try:
        return int(letter)
    except:
        return variables[ord(letter)-ord("A")]

def convert(num):
    num = num % (2**32)
    if num >= 2**31: num -= 2**32
    return num

def divide(num1, num2):
    is_negative = (num1 < 0) ^ (num2 < 0)
    result = abs(num1)//abs(num2)
    if is_negative: result *= -1
    return result

keys = []
code = {}
for line in lines:
    if line == "": continue
    tokens = line.split(" ")
    num = int(tokens[0])
    keys.append(num)
    
    command = tokens[1]
    if command == "LET":
        variable = ord(tokens[2])-ord("A")
        if len(tokens) == 7:
            if tokens[5] == "+":
                code[num] = (0, variable,
                             (lambda a: lambda b: lambda: convert(get_var(a)+get_var(b)))(tokens[4])(tokens[6]))
            elif tokens[5] == "-":
                code[num] = (0, variable,
                             (lambda a: lambda b: lambda: convert(get_var(a)-get_var(b)))(tokens[4])(tokens[6]))
            elif tokens[5] == "*":
                code[num] = (0, variable,
                             (lambda a: lambda b: lambda: convert(get_var(a)*get_var(b)))(tokens[4])(tokens[6]))
            elif tokens[5] == "/":
                code[num] = (0, variable,
                             (lambda a: lambda b: lambda: convert(divide(get_var(a), get_var(b))))(tokens[4])(tokens[6]))
            else:
                sys.exit(1)
        else:
            code[num] = (0, variable, (lambda a: lambda: get_var(a))(tokens[4]))
    elif command == "PRINT":
        if tokens[2][0] == "\"":
            string = " ".join(tokens[2:])[1:-1]
            code[num] = (1, (lambda a: lambda: print(a, end=""))(string))
        else:
            code[num] = (1, (lambda a: lambda: print(get_var(a), end=""))(tokens[2]))
    elif command == "PRINTLN":
        if tokens[2][0] == "\"":
            string = " ".join(tokens[2:])[1:-1]
            code[num] = (1, (lambda a: lambda: print(a))(string))
        else:
            code[num] = (1, (lambda a: lambda: print(get_var(a)))(tokens[2]))
    elif command == "IF":
        condition = tokens[2:-3]
        new_label = int(tokens[-1])
        if condition[1] == "=":
            code[num] = (2, (lambda a: lambda b: lambda: get_var(a) == get_var(b))(condition[0])(condition[2]), new_label)
        elif condition[1] == ">":
            code[num] = (2, (lambda a: lambda b: lambda: get_var(a) > get_var(b))(condition[0])(condition[2]), new_label)
        elif condition[1] == "<":
            code[num] = (2, (lambda a: lambda b: lambda: get_var(a) < get_var(b))(condition[0])(condition[2]), new_label)
        elif condition[1] == "<>":
            code[num] = (2, (lambda a: lambda b: lambda: get_var(a) != get_var(b))(condition[0])(condition[2]), new_label)
        elif condition[1] == "<=":
            code[num] = (2, (lambda a: lambda b: lambda: get_var(a) <= get_var(b))(condition[0])(condition[2]), new_label)
        elif condition[1] == ">=":
            code[num] = (2, (lambda a: lambda b: lambda: get_var(a) >= get_var(b))(condition[0])(condition[2]), new_label)
        else:
            sys.exit(1)
    else:
        sys.exit(1)

keys = sorted(keys)
key_index = 0
while key_index < len(keys):
    cur_key = keys[key_index]
    cur_code = code[cur_key]
    changed_key = False
    if cur_code[0] == 0:
        variables[cur_code[1]] = cur_code[2]()
    if cur_code[0] == 1:
        cur_code[1]()
    if cur_code[0] == 2:
        if cur_code[1]():
            key_index = keys.index(cur_code[2])
            changed_key = True
    if not changed_key: key_index += 1