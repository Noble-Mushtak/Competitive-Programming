def gen_gray_codes(n):
    if n == 1: return ["0", "1"]
    little_code = gen_gray_codes(n-1)
    return ["0"+code for code in little_code]+["1"+code for code in reversed(little_code)]

def find_index(code):
    if code == "0": return 0
    if code == "1": return 1
    
    if code[0] == "0": return find_index(code[1:])
    if code[0] == "1":
        return 2**(len(code)-1)+2**(len(code)-1)-find_index(code[1:])-1

print(gen_gray_codes(2))
print(gen_gray_codes(3))

for code in gen_gray_codes(10): print(find_index(code))