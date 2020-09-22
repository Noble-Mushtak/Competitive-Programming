import sys

lines = sys.stdin.read().split("\n")
for line in lines:
    num1, num2 = [int(x) for x in line.split()]
    if num1 == 0 and num2 == 0: break
    str1 = str(num1)
    str2 = str(num2)
    answer_str = str(num1*num2)
    header = "+"+((len(str1)+1)*3+len(str1))*"-"+"+"
    print(header)
    spaces = "   "
    second_line = "|"+spaces+spaces.join(list(str1))+spaces+"|"
    print(second_line)
    inter_line = "| "+"+"+"+".join(["---"]*len(str1))+"+"+" |"
    for i, digit in enumerate(str2):
        print(inter_line)
        inter1 = " /|"
        digit1s = [str((int(digit)*int(cur_digit)) // 10) for cur_digit in str1]
        char = " "
        if len(answer_str) > len(str1)+len(str2)-i: char = "/"
        line1 = "|"+char+"|"+inter1.join(digit1s)+inter1+" |"
        print(line1)
        inter_line2 = "| |"+"|".join([" / "]*len(str1))+"|"+digit+"|"
        print(inter_line2)
        inter2 = "|/ "
        digit2s = [str((int(digit)*int(cur_digit)) % 10) for cur_digit in str1]
        char = " "
        if len(answer_str) >= len(str1)+len(str2)-i: char = answer_str[len(answer_str)-(len(str1)+len(str2)-i-1)-1]
        line2 = "|"+char+inter2+inter2.join(digit2s)+"| |"
        print(line2)
    print(inter_line)
    char = " "
    if len(answer_str) > len(str1): char = "/"
    print("|"+char+" "+" / ".join([answer_str[len(answer_str)-i-1] for i in reversed(range(len(str1)))])+"    |")
    print(header)