#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
static inline double min(double length1, double length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef long test_cases;
typedef long dist;
typedef double speed;
typedef double time;
typedef long num_horses;

num_horses numHorses;
dist endPosition;
speed minSpeed;

int main() {
    test_cases numTestCases, z;
    dist startingPosition;
    speed curSpeed;
    time endTime;
    num_horses i;
    
    scanf("%li", &numTestCases);
    REPEAT(z, numTestCases) {
        scanf("%li %li", &endPosition, &numHorses);
        minSpeed = DBL_MAX;
        REPEAT(i, numHorses) {
            scanf("%li %lf", &startingPosition, &curSpeed);
            endTime = ((double)(endPosition-startingPosition))/curSpeed;
            minSpeed = min(minSpeed, ((double)endPosition)/endTime);
        }
        printf("Case #%li: %.7lf\n", z+1, minSpeed);
    }
    
    exit(0);
}