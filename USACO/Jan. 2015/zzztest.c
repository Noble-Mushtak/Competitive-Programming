#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <math.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

int main() {
    long i;
    srand(time(0));
    printf("10\n");
    REPEAT(i, 10) printf("-%li %li %li\n", (rand() % 50)+1, i+1, (rand() % 10)+1);
    exit(0);
}