#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

int main() {
    long i;
    char *hello = "abcde";
    REPEAT(i, 1000000) putchar(hello[i % 5]);
    printf("\n%s\n", hello);
    exit(0);
}