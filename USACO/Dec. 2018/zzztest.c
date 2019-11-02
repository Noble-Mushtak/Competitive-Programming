#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

int main() {
    long i, j, k;
    printf("10000 10000 1000\n");
    REPEAT(i, 1000) {
        j = rand() % 10000, k = rand() % 10000;
        printf("%li %li %li %li %li\n", j, k, (rand() % (10000-j))+(j+1), (rand() % (10000-k))+(k+1), i+2);
        //printf("%li %li %li %li %li\n", 5*i+1, 5*i+1, 5*i+2, 5*i+2, i+2);
    }
    exit(0);
}