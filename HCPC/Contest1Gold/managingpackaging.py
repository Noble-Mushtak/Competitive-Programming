import sys
lines = (line for line in sys.stdin.read().split("\n"))
not_beginning = False

def first_word(string):
    return string.split()[0]

while True:
    num_packages = int(next(lines))
    if num_packages == 0: break
    if not_beginning: print("")
    else: not_beginning = True
    
    names = {}
    inverse_names = []
    dependencies = []
    parents = []

    ordered_lines = []
    for i in range(num_packages):
        ordered_lines.append(next(lines))
    ordered_lines = sorted(ordered_lines, key=first_word)
    
    for i in range(num_packages):
        package_desc = ordered_lines[i].split()
        package_name = package_desc[0]
        inverse_names.append(package_name)
        names[package_name] = len(dependencies)
        dependencies.append(package_desc[1:])
    for i in range(num_packages):
        parents.append([names[package_name] for package_name in dependencies[i]])

    names_list = []
    not_in_list = list(range(num_packages))
    while True:
        if len(not_in_list) == 0:
            print("\n".join(names_list))
            break
            
        for i in not_in_list:
            if len(parents[i]) == 0:
                for j in range(num_packages):
                    try:
                        parents[j].remove(i)
                    except ValueError:
                        pass
                names_list.append(inverse_names[i])
                not_in_list.remove(i)
                break
        else:
            print("cannot be ordered")
            break