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
location signs[100000], frontNum[100000], backNum[100000], frontRange[100000], backRange[100000];
sign_range intervals[100000], frontIntervals[100000], backIntervals[100000];

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
    location front1, front2, back1, back2;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%li", &numSigns);
        REPEAT(i, numSigns) {
            scanf("%li %li %li", signs+i, frontNum+i, backNum+i);
            if (i == 0) {
                frontRange[i] = backRange[i] = 0;
                frontIntervals[0].start = frontIntervals[0].end = backIntervals[0].start = backIntervals[0].end = 0;
            } else {
                if (signs[i]+frontNum[i] == signs[i-1]+frontNum[i-1]) frontRange[i] = frontRange[i-1], frontIntervals[frontRange[i]].end++;
                else frontRange[i] = frontRange[i-1]+1, frontIntervals[frontRange[i]].start = i, frontIntervals[frontRange[i]].end = i;
                if (signs[i]-backNum[i] == signs[i-1]-backNum[i-1]) backRange[i] = backRange[i-1], backIntervals[backRange[i]].end++;
                else backRange[i] = backRange[i-1]+1, backIntervals[backRange[i]].start = i, backIntervals[backRange[i]].end = i;
            }
        }
        maxIntervalSize = numIntervals = 0;
        REPEAT(i, numSigns-1) {
            if (frontRange[i] != frontRange[i+1]) {
                storeRange.start = frontIntervals[frontRange[i]].start;
                storeRange.end = backIntervals[backRange[i+1]].end;
                if (storeRange.end-storeRange.start+1 > maxIntervalSize) {
                    maxIntervalSize = storeRange.end-storeRange.start+1;
                    //printf("F %li %li\n", storeRange.start, storeRange.end);
                    numIntervals = 1;
                    intervals[0] = storeRange;
                } else if (storeRange.end-storeRange.start+1 == maxIntervalSize) {
                    //printf("%li %li\n", storeRange.start, storeRange.end);
                    REPEAT(k, numIntervals) if ((intervals[k].start == storeRange.start) && (intervals[k].end == storeRange.end)) break;
                    if (k == numIntervals) intervals[numIntervals++] = storeRange;
                }
            }
            if (backRange[i] != backRange[i+1]) {
                storeRange.start = backIntervals[backRange[i]].start;
                storeRange.end = frontIntervals[frontRange[i+1]].end;
                if (storeRange.end-storeRange.start+1 > maxIntervalSize) {
                    maxIntervalSize = storeRange.end-storeRange.start+1;
                    //printf("B %li %li\n", storeRange.start, storeRange.end);
                    numIntervals = 1;
                    intervals[0] = storeRange;
                } else if (storeRange.end-storeRange.start+1 == maxIntervalSize) {
                    //printf("%li %li\n", storeRange.start, storeRange.end);
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