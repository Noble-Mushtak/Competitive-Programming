/*
    PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=492
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

typedef short coordinate;
typedef short num_checkpoints;
typedef long distance;

FILE *in, *out;
num_checkpoints total, skippable;
coordinate checkpoints[500][2];
distance distances[500][500], answer, answers[501][500];

int main() {
    distance store;
    num_checkpoints i, j, l, skipped, cur, track;
    long n[2];
    
    in = fopen("marathon.in", "r");
    fscanf(in, "%hi %hi", &total, &skippable);
    REPEAT(i, total) fscanf(in, "%hi %hi", checkpoints[i]+0, checkpoints[i]+1);
    fclose(in);
    
    #define DISTANCE(arr1, arr2) (abs(arr1[0]-arr2[0])+abs(arr1[1]-arr2[1]))
    REPEAT(i, total) {
        REPEAT(j, i) distances[i][j] = distances[j][i] = DISTANCE(checkpoints[i], checkpoints[j]);
        distances[i][i] = 0;
    }
    #undef DISTANCE
    
    if (skippable >= total-2) answer = distances[0][total-1];
    else {
        REPEAT(i, 501) REPEAT(j, 500) answers[i][j] = -1;
        answers[0][0] = 0;
        REPEAT(i, skippable+1) REPEAT(j, total) for (l = j+1; l < total && i+(l-j-1) <= skippable; l++) {
            skipped = i+(l-j-1);
            cur = l;
            store = answers[i][j]+distances[j][l];
            if (answers[skipped][cur] == -1 || answers[skipped][cur] > store) answers[skipped][cur] = store;
        }
        answer = answers[skippable][total-1];
    }
    
    out = fopen("marathon.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}