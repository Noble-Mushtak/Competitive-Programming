/*
    PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=493
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

typedef long num_cows;
typedef long long data;
typedef long minutes;

FILE *in, *out;
minutes time;
num_cows length, groups;
data cows[100000][2], cur;

int main() {
    num_cows i;
    
    in = fopen("cowjog.in", "r");
    fscanf(in, "%li %li", &length, &time);
    REPEAT(i, length) fscanf(in, "%lli %lli", cows[length-i-1]+0, cows[length-i-1]+1);
    fclose(in);
    
    groups = 1;
    cur = cows[0][0]+time*cows[0][1];
    REPEAT(i, length-1) if (cur > cows[i+1][0]+time*cows[i+1][1]) {
        groups++;
        cur = cows[i+1][0]+time*cows[i+1][1];
    }
    
    out = fopen("cowjog.out", "w");
    fprintf(out, "%li\n", groups);
    fclose(out);
    
    exit(0);
}