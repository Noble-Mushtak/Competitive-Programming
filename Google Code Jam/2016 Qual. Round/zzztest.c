#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

FILE *in;

int main() {
    long i, j;
    //srand(time(0));
    printf("100\n");
    REPEAT(i, 100) {
        REPEAT(j, 100) printf("%c", ((rand() % 2) ? '+' : '-'));
        puts("");
    }
    exit(0);
}