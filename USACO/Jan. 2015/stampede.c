#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define SET(arr, e1, e2) ( \
    (arr[0] = e1), \
    (arr[1] = e2) \
)
typedef signed char byte;

typedef long time;
typedef long data;
typedef long num_cows;

FILE *in, *out;
num_cows length, answer;
time cows[50000][2];
data posY[50000];
bool covered[50000];

int main() {
    data pos, speed;
    num_cows i, j;
    bool add;
    
    in = fopen("stampede.in", "r");
    fscanf(in, "%li", &length);
    REPEAT(i, length) {
        fscanf(in, "%li %li %li", &pos, posY+i, &speed);
        SET(cows[i], -speed*(pos+1), -speed*pos);
    }
    fclose(in);
    
    answer = length;
    #define SUBSET(i, j) (!covered[i] && cows[j][0] >= cows[i][0] && cows[j][1] <= cows[i][1])
    REPEAT(i, length) REPEAT(j, i) if (posY[i] < posY[j] ? SUBSET(i, j) : SUBSET(j, i)) {
        answer--;
        if (posY[i] < posY[j]) covered[j] = true; 
        else covered[i] = true;
    }
    #undef SUBSET
    
    out = fopen("stampede.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}