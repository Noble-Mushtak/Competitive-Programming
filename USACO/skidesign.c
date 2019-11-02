/*
  PROB: http://usaco.org/index.php?page=viewproblem2&cpid=376
*/

#include <stdlib.h>
#include <stdio.h>
typedef unsigned char bool;
#define true 1
#define false 0
#define REPEAT(token, num) for (token = 0; token < num; token++)

#define MAXHILLS 1000
FILE *in, *out;
long answer = 0, cost;
int hills[MAXHILLS], numHills, s, b, i, j, store;

int smallest(int *arr, int length) {

    int index = -1;
    REPEAT(i, length) if (index == -1 || arr[i] < arr[index]) index = i;
    return arr[index];
}
int biggest(int *arr, int length) {
    int index = -1;
    REPEAT(i, length) if (index == -1 || arr[i] > arr[index]) index = i;
    return arr[index];
}

int main() {
    in = fopen("skidesign.in", "r");
    fscanf(in, "%i\n", &numHills);
    REPEAT(i, numHills) fscanf(in, "%i\n", hills+i);
    fclose(in);
    
    s = smallest(hills, numHills);
    b = biggest(hills, numHills);
    for (i = s; i < b-17; i++) {
        cost = 0;
        REPEAT(j, numHills) {
            store = hills[j] < i ? i-hills[j] : hills[j] > i+17 ? hills[j]-(i+17) : 0;
            cost += store*store;
        }
        if (i == s || cost < answer) answer = cost;
    }
    
    out = fopen("skidesign.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    exit(0);
}