#include <stdio.h>
#include <stdlib.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;
#define FASTIO(lvalue, file) (lvalue = fgetc(file))
#define FASTEX(lvalue, char) (lvalue = lvalue*10+(char-'0'))
#define POPQUEUE(arr, len) memmove(arr, arr+1, len*sizeof(arr[0]))
#define REMOVEELEM(arr, off, len) memmove(arr+off, arr+(off+1), (len-off)*sizeof(arr[0]))
#define REMOVEELEMS(arr, off, len, num) memmove(arr+off, arr+(off+num), (len-off)*sizeof(arr[0]))
#define SET(arr, e1, e2) ( \
    (arr[0] = e1), \
    (arr[1] = e2) \
)
#define MOD 1000000007

typedef long modulo;
typedef byte dimen;
typedef short entry;

FILE *in, *out;
dimen width = 0, length = 0, maxDimen;
//maxEntry not used
entry grid[100][100], maxEntry = 0;
modulo answers[100][100];

int main() {
    dimen i, j, i2, j2, offsetX, offsetY;
    char store;
    
    in = fopen("hopscotch.in", "r");
    while (FASTIO(store, in) != ' ') FASTEX(width, store);
    while (FASTIO(store, in) != ' ') FASTEX(length, store);
    maxDimen = width > length ? width : length;
    while (FASTIO(store, in) != '\n') FASTEX(maxEntry, store);
    REPEAT(i, width) REPEAT(j, length) {
        while (FASTIO(store, in) != ((j+1 == length) ? '\n' : ' ')) FASTEX(grid[i][j], store);
    }
    fclose(in);
    
    REPEAT(i, maxDimen) {
        if (!i) {
            answers[width-1][length-1] = 1;
            continue;
        }
        offsetX = (width < i+1) ? 0 : width-i-1;
        offsetY = (length < i+1) ? 0 : length-i-1;
        //printf("%i %i\n", offsetX, offsetY);
        if (width >= i+1) for (j = offsetX; j < width; j++) {
            /*y is offsetY*/
            for (i2 = j+1; i2 < width; i2++) for (j2 = offsetY+1; j2 < length; j2++) if (grid[j][offsetY] != grid[i2][j2]) answers[j][offsetY] += answers[i2][j2], answers[j][offsetY] %= MOD;
        }
        if (length >= i+1) for (j = offsetY+1; j < length; j++) {
            /*x is offsetX*/
            for (i2 = offsetX+1; i2 < width; i2++) for (j2 = j+1; j2 < length; j2++) if (grid[offsetX][j] != grid[i2][j2]) answers[offsetX][j] += answers[i2][j2], answers[offsetX][j] %= MOD;
        }
    }
    
    out = fopen("hopscotch.out", "w");
    fprintf(out, "%li\n", answers[0][0]);
    fclose(out);
    
    exit(0);
}