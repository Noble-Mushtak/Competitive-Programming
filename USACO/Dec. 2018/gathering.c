#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

typedef long num_cows;
typedef long num_pairs;

FILE *in, *out;
num_cows numCows, prev[3010], next[3010];
num_pairs numPairs;
bool answer[3010];

int main() {
    num_cows i, store1, store2;
    
    in = fopen("gathering.in", "r");
    fscanf(in, "%li %li", &numCows, &numPairs);
    REPEAT(i, numCows-1) {
        fscanf(in, "%li %li", &store1, &store2);
        prev[store2] = store1, next[store1] = store2;
    }
    REPEAT(i, numPairs) {
        fscanf(in, "%li %li", &store1, &store2);
        if (store1 < store2) while (store1) answer[store1-1] = true, store1 = prev[store1];
        else while (store1) answer[store1-1] = true, store1 = next[store2];
    }
    fclose(in);
    
    out = fopen("gathering.out", "w");
    REPEAT(i, numCows) fprintf(out, "%c\n", answer[i] ? '0' : '1');
    fclose(out);
    
    exit(0);
}