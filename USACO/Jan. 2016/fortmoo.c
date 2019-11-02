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

typedef long dimen;
typedef long area;

FILE *in, *out;
area answer = 0;
dimen width, length, maxLeft[200][200], maxUp[200][200], maxRight[200][200], maxDown[200][200];
bool grid[200][200];
char row[201];

int main() {
    dimen i, j, i2, j2;
    char store;
    
    in = fopen("fortmoo.in", "r");
    fscanf(in, "%li %li", &width, &length);
    REPEAT(i, width) {
        fscanf(in, "%s", row);
        REPEAT(j, length) grid[i][j] = (row[j] == '.');
    }
    fclose(in);
    /*REPEAT(i, width) {
        REPEAT(j, length) putchar(grid[i][j] ? '.' : 'X');
        puts("");
    }*/

    REPEAT(i, width) {
        REPEAT(j, length) {
            if (!j) maxLeft[i][j] = grid[i][j] ? 1 : 0;
            else maxLeft[i][j] = grid[i][j] ? maxLeft[i][j-1]+1 : 0;
        }
        for (j = length-1; j >= 0; j--) {
            if (j+1 == length) maxRight[i][j] = grid[i][j] ? 1 : 0;
            else maxRight[i][j] = grid[i][j] ? maxRight[i][j+1]+1 : 0;
        }
    }
    REPEAT(j, length) {
        REPEAT(i, width) {
            if (!i) maxUp[i][j] = grid[i][j] ? 1 : 0;
            else maxUp[i][j] = grid[i][j] ? maxUp[i-1][j]+1 : 0;
        }
        for (i = width-1; i >= 0; i--) {
            if (i+1 == width) maxDown[i][j] = grid[i][j] ? 1 : 0;
            else maxDown[i][j] = grid[i][j] ? maxDown[i+1][j]+1 : 0;
        }
    }
    
    REPEAT(i, width) REPEAT(j, length) for (i2 = i; i2 < width; i2++) for (j2 = j; j2 < length; j2++) if (maxRight[i][j] > j2-j && maxLeft[i2][j2] > j2-j && maxDown[i][j] > i2-i && maxUp[i2][j2] > i2-i && (i2-i+1)*(j2-j+1) > answer) answer = (i2-i+1)*(j2-j+1)/*, printf("C: %li %li %li %li\n", i, j, i2, j2); else if (i == 3 && j == 3 && i2 == 4 && j2 == 5) printf("#: %li %li %li %li\n", maxRight[i][j], maxDown[i][j], maxLeft[i2][j2], maxUp[i2][j2])*/;
    
    out = fopen("fortmoo.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}