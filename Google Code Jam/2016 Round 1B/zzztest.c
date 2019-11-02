#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)

FILE *in;

int main() {
    long i;
    //srand(time(0));
    printf("1\n");
    REPEAT(i, 20) printf("ONE");
    REPEAT(i, 40) printf("ZERO");
    REPEAT(i, 100) printf("EIGHT");
    exit(0);
}