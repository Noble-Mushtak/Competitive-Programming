#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef signed char byte;
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline void POPQUEUE(void *arr, size_t length, size_t itemSize) { memmove(arr, arr+itemSize, length*itemSize); }
static inline void REMOVEELEM(void *arr, size_t offset, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+1)*itemSize), (length-offset)*itemSize); }
static inline void REMOVEELEMS(void *arr, size_t offset, size_t numElems, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+numElems)*itemSize), (length-offset)*itemSize); }

FILE *in, *out;
typedef long dimen;
typedef long num_points;
typedef long long num_crosses;
typedef long time;
typedef struct {
    dimen x, y;
} point;

FILE *in, *out;
time numDays, growBack;
point positions[100000];
num_crosses answer = 0;

int main() {
    time i, j;
    dimen min, max, temp;
    
    in = fopen("mowing.in", "r");
    fscanf(in, "%li %li", &numDays, &growBack);
    REPEAT(i, numDays) fscanf(in, "%li %li", &(positions[i].x), &(positions[i].y));
    fclose(in);

    REPEAT(i, numDays) for (j = i+growBack; j < numDays; j++) {
        if (positions[i].x == positions[i+1].x && positions[j].y == positions[j+1].y) {
            min = positions[j].x, max = positions[j+1].x;
            if (max < min) temp = min, min = max, max = temp;
            if (min < positions[i].x && positions[i].x < max) answer += 1/*, printf("%li %li\n", i, j)*/;
        }
        if (positions[i].y == positions[i+1].y && positions[j].x == positions[j+1].x) {
            min = positions[j].y, max = positions[j+1].y;
            if (max < min) temp = min, min = max, max = temp;
            if (min < positions[i].y && positions[i].y < max) answer += 1/*, printf("%li %li\n", i, j)*/;
        }
    }
    
    out = fopen("mowing.out", "w");
    fprintf(out, "%lli\n", answer);
    fclose(out);
    
    exit(0);
}