#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

int main() {
    long i, j;
    printf("25 25\nA 1\n");
    REPEAT(i, 25) REPEAT(j, 25) printf("%c %li\n", 'A'+i, j+1);
    exit(0);
}