#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)

FILE *in;

int main() {
    long i;
    //srand(time(0));
    printf("1000\n");
    REPEAT(i, 1000) printf("%li%c", rand(), i+1 == 1000 ? '\n' : ' ');
    exit(0);
}