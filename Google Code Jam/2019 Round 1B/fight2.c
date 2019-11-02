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

typedef long long num;
typedef long long num_nums;
typedef long long test_cases;

num charles[100010], delila[100010], charlesMax[100010], delilaMax[100010], charlesIntervals[500], delilaIntervals[500], charlesUpdates[500], delilaUpdates[500], tolerance;
num_nums numSwords, intervals[500], numIntervals, lastAnswer, fairFight[100010], fairFightIntervals[500], fairFightUpdates[500], answer;

num sqrt_(num n) {
    num beg = 0, end = n, mid;
    while (beg < end) {
        mid = (beg+end)/2;
        if (mid*mid == n) return mid;
        else if (mid*mid < n) beg = mid+1;
        else end = mid;
    }
    return beg;
}

num_nums findInterval(num n) {
    num beg = 0, end = numIntervals-1, mid;
    while (beg <= end) {
        mid = (beg+end)/2;
        if ((intervals[mid] <= n) && (n < intervals[mid+1])) return mid;
        else if (n < intervals[mid]) end = mid-1;
        else beg = mid+1;
    }
    fprintf(stderr, "ERROR IN BINARY SEARCH\n");
    exit(1);
}

num_nums getRealValue(num *arr, num *updatesArr, num_nums index) {
    return max(arr[index], updatesArr[findInterval(index)]);
}

num_nums findUpdateStart(num *arr, num *updatesArr, num n, num_nums max) {
    num beg = 0, end = max-1, mid;
    while (beg <= end) {
        mid = (beg+end)/2;
        if ((getRealValue(arr, updatesArr, mid) < n) && ((mid == 0) || (getRealValue(arr, updatesArr, mid-1) >= n))) return mid;
        else if (getRealValue(arr, updatesArr, mid) < n) end = mid-1;
        else beg = mid+1;
    }
    return max;
}

num_nums updateArr(num *arr, num *intervalsArr, num *updatesArr, num_nums i, num val) {
    num_nums updateStart = findUpdateStart(arr, updatesArr, val, i);
    num_nums firstInterval = findInterval(updateStart);
    num_nums lastInterval = findInterval(i);
    num_nums k;
    
    num oldUpdate = updatesArr[firstInterval];
    for (k = intervals[firstInterval]; k <= ((firstInterval == lastInterval) ? i : intervals[firstInterval+1]); k++) {
        if (k < updateStart) arr[k] = max(arr[k], oldUpdate);
        else arr[k] = max(arr[k], val);
    }
    intervalsArr[firstInterval] = max(intervalsArr[firstInterval], val);
    updatesArr[firstInterval] = 0;
    
    for (k = firstInterval+1; k < lastInterval; k++) updatesArr[k] = max(updatesArr[k], val);
    
    if (firstInterval != lastInterval) {
        for (k = intervals[lastInterval]; k <= i; k++) arr[k] = max(arr[k], val);
        intervalsArr[lastInterval] = val;
        updatesArr[lastInterval] = 0;
    }
    
    return updateStart;
}

int main() {
    test_cases numTestCases, l;
    num_nums i, sqrtLength, firstInterval, lastInterval, k, updateStart, isFairFight, oldUpdate;
    scanf("%lli", &numTestCases);
    
    REPEAT(l, numTestCases) {
        scanf("%lli %lli", &numSwords, &tolerance);
        REPEAT(i, numSwords) scanf("%lli", charles+i);
        REPEAT(i, numSwords) scanf("%lli", delila+i);
        
        sqrtLength = sqrt_(numSwords);
        intervals[0] = 0;
        while ((numIntervals == 0) || (intervals[numIntervals] < numSwords)) {
            numIntervals++;
            intervals[numIntervals] = intervals[numIntervals-1]+sqrtLength;
            intervals[numIntervals] = min(numSwords, intervals[numIntervals]);
        }
        REPEAT(i, numIntervals) {
            charlesMax[i] = delilaMax[i] = fairFight[i] = 0;
            charlesIntervals[i] = delilaIntervals[i] = fairFightIntervals[i] = 0;
            charlesUpdates[i] = delilaUpdates[i] = 0;
            fairFightUpdates[i] = -1;
        }
        answer = 0;
        
        REPEAT(i, numSwords) {
            updateStart = updateArr(charlesMax, charlesIntervals, charlesUpdates, i, charles[i]);
            updateStart = updateArr(delilaMax, delilaIntervals, delilaUpdates, i, delila[i]);
            
            firstInterval = findInterval(updateStart), lastInterval = findInterval(i);
            isFairFight = max(charles[i]-delila[i], delila[i]-charles[i]) <= tolerance;
            
            oldUpdate = fairFightUpdates[firstInterval];
            fairFightIntervals[firstInterval] = 0;
            for (k = intervals[firstInterval]; k <= ((firstInterval == lastInterval) ? i : intervals[firstInterval+1]); k++) {
                if ((k < updateStart) && (oldUpdate != -1)) fairFight[k] = oldUpdate;
                else fairFight[k] = isFairFight;
                fairFightIntervals[firstInterval] += fairFight[k];
            }
            fairFightUpdates[firstInterval] = -1;
            
            for (k = firstInterval+1; k < lastInterval; k++) fairFightUpdates[k] = isFairFight;
            
            if (firstInterval != lastInterval) {
                fairFightIntervals[lastInterval] = 0;
                for (k = intervals[lastInterval]; k <= i; k++) {
                    fairFight[k] = isFairFight;
                    fairFightIntervals[lastInterval] += fairFight[k];
                }
                fairFightUpdates[lastInterval] = -1;
            }
            for (k = 0; k <= lastInterval; k++) answer += fairFightIntervals[k];
        }
        printf("Case #%lli: %lli\n", l+1, answer);
    }
    
    exit(0);
}