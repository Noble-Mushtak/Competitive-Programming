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

typedef long num_points;
typedef long dimen;
typedef struct {
    dimen x, y;
} point;

FILE *in, *out;
num_points fieldSize, startX[100000], startY[100000], storage1[100000], storage2[100000], *tempPtr, *curAnswers, *prevAnswers;
dimen xs[100000], ys[100000], xTo[1000000], yTo[1000000], numXs, numYs, minDist;
point field[100000], fieldSortedByX[100000], fieldSortedByY[100000];

int main() {
    char store;
    num_points i, beg, mid, end, otherCornerUp, otherCornerRight, oppositeCorner, maxCorner;
    dimen a, b;
    
    in = fopen("balancing.in", "r");
    fscanf(in, "%li", &fieldSize);
    REPEAT(i, fieldSize) fscanf(in, "%li %li", &(field[i].x), &(field[i].y)), xs[i] = field[i].x, ys[i] = field[i].y;
    fclose(in);

    inline int compareDimens(const void *ptr1, const void *ptr2) {
        dimen dimen1 = *(dimen*)ptr1, dimen2 = *(dimen*)ptr2;
        return (dimen1 > dimen2)-(dimen1 < dimen2);
    }
    qsort(xs, fieldSize, sizeof(dimen), compareDimens), qsort(ys, fieldSize, sizeof(dimen), compareDimens);
    REPEAT(i, fieldSize) {
        if (!i || xs[i] != xs[i-1]) xTo[xs[i]] = numXs++;
        if (!i || ys[i] != ys[i-1]) yTo[ys[i]] = numYs++;
    }
    REPEAT(i, fieldSize) field[i].x = xTo[field[i].x], field[i].y = yTo[field[i].y]/*, printf("%li %li\n", field[i].x, field[i].y)*/;

    inline int comparePointsByX(const void *ptr1, const void *ptr2) {
        point point1 = *(point*)ptr1, point2 = *(point*)ptr2;
        int store = (point1.x > point2.x)-(point1.x < point2.x);
        if (store) return store;
        else return (point1.y > point2.y)-(point1.y < point2.y);
    }
    inline int comparePointsByY(const void *ptr1, const void *ptr2) {
        point point1 = *(point*)ptr1, point2 = *(point*)ptr2;
        return (point1.y > point2.y)-(point1.y < point2.y);
    }
    memcpy(fieldSortedByX, field, sizeof(field)), memcpy(fieldSortedByY, field, sizeof(field));
    qsort(fieldSortedByX, fieldSize, sizeof(point), comparePointsByX), qsort(fieldSortedByY, fieldSize, sizeof(point), comparePointsByY);
    REPEAT(i, fieldSize) {
        if (!i || fieldSortedByX[i].x != fieldSortedByX[i-1].x) startX[fieldSortedByX[i].x] = i;
        if (!i || fieldSortedByY[i].y != fieldSortedByY[i-1].y) startY[fieldSortedByY[i].y] = i;
    }
    startX[numXs] = startY[numYs] = fieldSize;

    minDist = fieldSize+1;
    REPEAT(a, numXs) {
        if (!a) curAnswers = storage1, prevAnswers = storage2;
        else tempPtr = curAnswers, curAnswers = prevAnswers, prevAnswers = tempPtr;
        REPEAT(b, numYs) {
            if (b < fieldSortedByX[startX[a]].y) curAnswers[b] = prevAnswers[b];
            else {
                beg = startX[a], end = startX[a+1]-1;
                while (beg <= end) {
                    mid = (beg+end)/2;
                    if (fieldSortedByX[mid].y <= b && (mid+1 == startX[a+1] || fieldSortedByX[mid+1].y > b)) break;
                    else if (fieldSortedByX[mid].y <= b) beg = mid+1;
                    else end = mid-1;
                }
                if (beg > end) printf("ERROR: %li %li\n", beg, end), exit(1);
                curAnswers[b] = prevAnswers[b]+mid-startX[a]+1;
            }
            maxCorner = curAnswers[b];
            otherCornerUp = startY[b+1]-curAnswers[b];
            if (otherCornerUp > maxCorner) maxCorner = otherCornerUp;
            otherCornerRight = startX[a+1]-curAnswers[b];
            if (otherCornerRight > maxCorner) maxCorner = otherCornerRight;
            oppositeCorner = fieldSize-otherCornerUp-otherCornerRight-curAnswers[b];
            if (oppositeCorner > maxCorner) maxCorner = oppositeCorner;
            if (maxCorner < minDist) minDist = maxCorner;
            //printf("%li %li | %li %li %li %li\n", a, b, curAnswers[b], otherCornerUp, otherCornerRight, oppositeCorner);
        }
    }
    
    out = fopen("balancing.out", "w");
    fprintf(out, "%li\n", minDist);
    fclose(out);
    
    exit(0);
}