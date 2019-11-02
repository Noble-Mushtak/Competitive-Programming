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

typedef long test_cases;
typedef long location;
typedef long num_signs;
typedef struct {
    location front, back;
} location_tuple;
typedef struct {
    num_signs start, end;
} sign_range;

num_signs numSigns, maxIntervalSize, numIntervals;
location signs[100000], frontNum[100000], backNum[100000];
sign_range intervals[100];

sign_range findInterval(num_signs start, num_signs end, location front, location back) {
    while ((start > 0) && ((signs[start-1]+frontNum[start-1] == front) || (signs[start-1]-backNum[start-1] == back))) start--;
    while ((end < numSigns-1) && ((signs[end+1]+frontNum[end+1] == front) || (signs[end+1]-backNum[end+1] == back))) end++;
    sign_range store;
    store.start = start, store.end = end;
    return store;
}

int main() {
    num_signs i, j, k;
    sign_range storeRange;
    test_cases numTestCases, z;
    location_tuple storeLocations[4];
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%li", &numSigns);
        REPEAT(i, numSigns) scanf("%li %li %li", signs+i, frontNum+i, backNum+i);
        maxIntervalSize = numIntervals = 0;
        REPEAT(i, numSigns-1) {
            storeLocations[0].front = signs[i]+frontNum[i], storeLocations[0].back = signs[i]-backNum[i];
            storeLocations[1].front = signs[i]+frontNum[i], storeLocations[1].back = signs[i+1]-backNum[i+1];
            storeLocations[2].front = signs[i+1]+frontNum[i+1], storeLocations[2].back = signs[i]-backNum[i];
            storeLocations[3].front = signs[i+1]+frontNum[i+1], storeLocations[3].back = signs[i+1]-backNum[i+1];
            REPEAT(j, 4) {
                storeRange = findInterval(i, i+1, storeLocations[j].front, storeLocations[j].back);
                if (storeRange.end-storeRange.start+1 > maxIntervalSize) {
                    maxIntervalSize = storeRange.end-storeRange.start+1;
                    //printf("%li %li\n", storeRange.start, storeRange.end);
                    numIntervals = 1;
                    intervals[0] = storeRange;
                } else if (storeRange.end-storeRange.start+1 == maxIntervalSize) {
                    REPEAT(k, numIntervals) if ((intervals[k].start == storeRange.start) && (intervals[k].end == storeRange.end)) break;
                    if (k == numIntervals) intervals[numIntervals++] = storeRange;
                }
            }
        }
        if (numSigns == 1) maxIntervalSize = numIntervals = 1;
        
        printf("Case #%li: %li %li\n", z+1, maxIntervalSize, numIntervals);
    }
    
    exit(0);
}