#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define SET(arr, e1, e2) ( \
     ((arr[0] = e1) || true) && \
     ((arr[1] = e2)) \
)
typedef signed char byte;

FILE *in, *out;
long answer, cows[100000][2], numCows, slowest, begin;

int main() {
    long i;
    
//#define RANDOMNUMS
#ifndef RANDOMNUMS
    in = fopen("cowjog.in", "r");
    fscanf(in, "%li", &numCows);
    REPEAT(i, numCows) fscanf(in, "%li %li", cows[i]+0, cows[i]+1);
    fclose(in);
#else
    srand(time(0));
    numCows = 100000;
    REPEAT(i, numCows) {
        cows[i][0] = i;
        cows[i][1] = i;
    }
#endif
    
    for (i = numCows-1; i >= 0; i--) {
        if (i == numCows-1 || cows[i][1] <= slowest) {
            slowest = cows[i][1];
            answer++;
        }
    }
    
    out = fopen("cowjog.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}