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

typedef short num_points;
typedef long dimen;
typedef struct {
    dimen x, y;
} point;

FILE *in, *out;
dimen maxDist1 = 0, maxDist2 = 0, dists[200], sumDists, sumDistsSoFar[200];
num_points numPoints;
point verticies[200];

int main() {
    char store;
    num_points i, nextI;
    dimen minX, maxX, minY, maxY, temp;
    
    in = fopen("lightsout.in", "r");
    fscanf(in, "%hi", &numPoints);
    REPEAT(i, numPoints) fscanf(in, "%li %li", &(verticies[i].x), &(verticies[i].y));
    fclose(in);

    REPEAT(i, numPoints) {
        if (i+1 == numPoints) nextI = 0;
        else nextI = i+1;
        minX = verticies[i].x, maxX = verticies[nextI].x;
        if (maxX < minX) temp = maxX, maxX = minX, minX = temp;
        minY = verticies[i].y, maxY = verticies[nextI].y;
        if (maxY < minY) temp = maxY, maxY = minY, minY = temp;
        dists[i] = maxX-minX+maxY-minY;
        sumDistsSoFar[i] = sumDists;
        sumDists += dists[i];
    }
    REPEAT(i, numPoints-1) {
        if (sumDists-2*sumDistsSoFar[i+1] > maxDist1) maxDist1 = sumDists-2*sumDistsSoFar[i+1];
        else if (2*sumDistsSoFar[i+1]-sumDists > maxDist2) maxDist2 = 2*sumDistsSoFar[i+1]-sumDists;
    }
    
    out = fopen("lightsout.out", "w");
    fprintf(out, "%li\n", ((maxDist1 < maxDist2) ? maxDist1 : maxDist2));
    fclose(out);
    
    exit(0);
}