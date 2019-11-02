#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

FILE *in, *out;

int main() {
    in = fopen("exercise.in", "r");
    
    fclose(in);
    
    out = fopen("exercise.out", "w");
    
    fclose(out);
    
    exit(0);
}