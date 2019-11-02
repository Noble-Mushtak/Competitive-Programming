#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
/*#define SET(arr, e1, e2) ( \
     ((arr[0] = e1) || true) && \
     ((arr[1] = e2)) \
)*/
typedef signed char byte;

FILE *in, *out;
short numCells = 0;
byte beginCells[2500][2], rows, columns;
char store;
bool clearCells[50][50], isHorizontal;

int main() {
    short i, j;
    
    in = fopen("crosswords.in", "r");
    fscanf(in, "%hi %hi\n", &rows, &columns);
    REPEAT(i, rows) REPEAT(j, columns) {
        fscanf(in, "%c", &store);
        if (store == '\n') fscanf(in, "%c", &store);
        clearCells[i][j] = (store == '.');
    }
    fclose(in);
    
    REPEAT(i, rows) REPEAT(j, columns) if (clearCells[i][j]) {
        if ((columns > j+2 && (j == 0 || !clearCells[i][j-1]) && clearCells[i][j+1] && clearCells[i][j+2]) || (rows > i+2 && (i == 0 || !clearCells[i-1][j]) && clearCells[i+1][j] && clearCells[i+2][j])) {
            beginCells[numCells][0] = i+1;
            beginCells[numCells][1] = j+1;
            numCells++;
        }
    }
    
    out = fopen("crosswords.out", "w");
    fprintf(out, "%hi\n", numCells);
    REPEAT(i, numCells) fprintf(out, "%hhi %hhi\n", beginCells[i][0], beginCells[i][1]);
    fclose(out);
    
    exit(0);
}