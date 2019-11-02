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
#define DISTANCE(arr1, arr2) (abs(arr1[0]-arr2[0])+abs(arr1[1]-arr2[1]))
typedef signed char byte;

FILE *in, *out;
short points[100000][2];
long numPoints, answer, distance, distances[99999], normalDistance;

int main() {
    long i, j;

#ifndef RANDOMNUMS   
    in = fopen("marathon.in", "r");
    fscanf(in, "%li", &numPoints);
    REPEAT(i, numPoints) fscanf(in, "%hi %hi\n", points[i]+0, points[i]+1);
    fclose(in);
#else
    numPoints = 100000;
    srand(time(0));
    REPEAT(i, numPoints) {
        points[i][0] = rand() % 1000;
        points[i][1] = rand() % 1000;
    }
#endif
    
    REPEAT(i, numPoints-1) {
        distances[i] = DISTANCE(points[i], points[i+1]);
        normalDistance += distances[i];
    }
    REPEAT(i, numPoints-2) {
        distance = normalDistance-distances[i]-distances[i+1]+DISTANCE(points[i], points[i+2]);
        if (!i || distance < answer) answer = distance;
    }
    
    out = fopen("marathon.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}