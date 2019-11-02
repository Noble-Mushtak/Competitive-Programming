#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef long long num_queries;
typedef long long num_cells;

num_queries numQueries;
num_cells sideLength, directionsLength;
char oldDirections[100010], newDirections[100010];

int main() {
    num_cells i;
    num_queries l;
    scanf("%lli", &numQueries);    

    REPEAT(l, numQueries) {
        scanf("%lli %s", &sideLength, oldDirections);
        directionsLength = strlen(oldDirections);
        REPEAT(i, directionsLength) newDirections[i] = (oldDirections[i] == 'S') ? 'E' : 'S';
        newDirections[directionsLength] = 0;
        printf("Case #%lli: %s\n", l+1, newDirections);
    }
    
    exit(0);
}