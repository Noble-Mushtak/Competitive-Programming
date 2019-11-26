import sys

lines = (line for line in sys.stdin.read().split("\n"))
while True:
    domain_line = next(lines)
    if domain_line == "": break
    domain_objs = domain_line.split()[1:]
    
    codomain_line = next(lines)
    codomain_objs = codomain_line.split()[1:]

    is_function = True
    mapping = {}
    image = set()
    is_injective = True
    
    num_pairs = int(next(lines))
    for i in range(num_pairs):
        pair_line = next(lines).split()
        input = pair_line[0]
        output = pair_line[2]
        if input in mapping:
            is_function = False
        mapping[input] = output
        if output in image:
            is_injective = False
        image.add(output)
    if not is_function:
        print("not a function")
    else:
        is_surjective = len(image) == len(codomain_objs)
        if (not is_injective) and (not is_surjective):
            print("neither injective nor surjective")
        elif is_injective and (not is_surjective):
            print("injective")
        elif (not is_injective) and is_surjective:
            print("surjective")
        else:
            print("bijective")