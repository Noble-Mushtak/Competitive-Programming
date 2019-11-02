#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef signed char byte;
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline void POPQUEUE(void *arr, size_t length, size_t itemSize) { memmove(arr, arr+itemSize, length*itemSize); }
static inline void REMOVEELEM(void *arr, size_t offset, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+1)*itemSize), (length-offset)*itemSize); }
static inline void REMOVEELEMS(void *arr, size_t offset, size_t numElems, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+numElems)*itemSize), (length-offset)*itemSize); }

typedef long fullness;

FILE *in, *out;
fullness maxPossible, answer, orange, lemon;
bool possible[5000000];

int main() {
    char store;
    fullness i;
    
    in = fopen("feast.in", "r");
    fscanf(in, "%li %li %li", &maxPossible, &orange, &lemon);
    fclose(in);

    possible[0] = true;
    REPEAT(i, maxPossible) if (possible[i]) {
        possible[i/2] = true;
        if (i+orange <= maxPossible) possible[i+orange] = true, ((answer < i+orange) ? (answer = i+orange) : 0);
        if (i+lemon <= maxPossible) possible[i+lemon] = true, ((answer < i+lemon) ? (answer = i+lemon) : 0);
    }
    REPEAT(i, maxPossible) if (possible[i]) {
        if (i+orange <= maxPossible) possible[i+orange] = true, ((answer < i+orange) ? (answer = i+orange) : 0);
        if (i+lemon <= maxPossible) possible[i+lemon] = true, ((answer < i+lemon) ? (answer = i+lemon) : 0);
    }
    
    out = fopen("feast.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}