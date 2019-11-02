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

typedef long long test_cases;
typedef long long num_stalls;

num_stalls numStalls, numPeople, *divisions, *stallsInDivision, *otherDivisions, *otherStallsInDivision, storage1[2], storage2[2], storage3[2], storage4[2], numDivisions, numOtherDivisions;

static inline num_stalls indexOf(num_stalls *arr, num_stalls length, num_stalls query) {
    num_stalls i;
    REPEAT(i, length) if (arr[i] == query) return i;
    return -1;
}

int main() {
    test_cases numTestCases, z;
    num_stalls *temp, i, j, subdivision1, subdivision2;
    scanf("%lli", &numTestCases);
    divisions = storage1, stallsInDivision = storage2, otherDivisions = storage3, otherStallsInDivision = storage4;
    
    REPEAT(z, numTestCases) {
        scanf("%lli %lli", &numStalls, &numPeople);
        numDivisions = 1, divisions[0] = numStalls, stallsInDivision[0] = 1;
        while (numPeople > 0) {
            numOtherDivisions = 0;
            REPEAT(i, numDivisions) {
                numPeople -= stallsInDivision[i];
                subdivision1 = (divisions[i]-1)/2;
                subdivision2 = divisions[i]-1-subdivision1;
                if (numPeople <= 0) {
                    printf("Case #%lli: %lli %lli\n", z+1, subdivision2, subdivision1);
                    break;
                }
                inline void insertDivision(num_stalls subdivision) {
                    if (subdivision == 0) return;
                    j = indexOf(otherDivisions, numOtherDivisions, subdivision);
                    if (j >= 0) otherStallsInDivision[j] += stallsInDivision[i];
                    else {
                        otherDivisions[numOtherDivisions] = subdivision;
                        otherStallsInDivision[numOtherDivisions++] = stallsInDivision[i];
                    }
                }
                insertDivision(subdivision2), insertDivision(subdivision1);
            }
            temp = divisions, divisions = otherDivisions, otherDivisions = temp;
            temp = stallsInDivision, stallsInDivision = otherStallsInDivision, otherStallsInDivision = temp;
            numDivisions = numOtherDivisions;
        }
    }
    
    exit(0);
}