#include <stdio.h>
#include <stdlib.h>
#include "struct_string.h"

void test_str_vsscanf(String str, char *format, ...) {
    va_list args;
    va_start(args, format);
    str_vsscanf(str, format, args);
    va_end(args);
}

int main() {
    String str1 = make_str("Testing strings! Testing strings for reals!"), str2 = convert_string_to_str("Testing strings for life!"), str3 = convert_string_to_str("Testing");
    int test[2];
    
    test[0] = printf_str(str1), putchar('\n');
    printf("%li %i %li\n", str1.length, test[0], str1.size);
    
    str_scanf(convert_string_to_str("2"), "%i", test+0);
    test_str_vsscanf(convert_string_to_str("3"), "%i", test+1);
    printf("%i %i\n", test[0], test[1]);
    
    printf_str(add_strs(str1, str2)), putchar('\n');
    add_str_to_str(&str1, str2);
    printf_str(str1), putchar('\n');
    add_string_to_str(&str1, "Hello!");
    printf_str(str1), putchar('\n');
    
    printf_str(substr(&str1, 1, 3)), putchar('\n');
    printf_str(str_slice(&str1, 1, 3, 2)), putchar('\n');
    printf("%li %li %li %li\n", str_index(&str1, str3), str_string_index(&str1, "Testing"), str_rindex(&str1, str3), str_string_rindex(&str1, "Testing"));
    
    exit(0);
}