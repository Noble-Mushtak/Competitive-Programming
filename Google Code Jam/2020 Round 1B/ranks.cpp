#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t test_cases;
typedef int64_t num;
typedef int64_t num_nums;

num maxNum;
num_nums repetitions, arrLength;
num *arr, *newArr, *tempArr, storeArr1[2500], storeArr2[2500];
const num_nums MAX_ANSWERS = 1000000;
num_nums numAnswers, answers[MAX_ANSWERS][2];
test_cases numTestCases;

int main() {
    scanf(INT64, &numTestCases);
    test_cases l;
    REP(l, numTestCases) {
        scanf(INT64 " " INT64, &maxNum, &repetitions);
        arrLength = repetitions*maxNum;
        arr = storeArr1, newArr = storeArr2;
        
        num_nums i;
        REP(i, arrLength) {
            arr[i] = (i % maxNum)+1;
        }
        
        for (numAnswers = 0; ; ++numAnswers) {
            num_nums inversionLocation = -1;
            for (i = arrLength-1; i > 0; --i) {
            //for (i = 1; i < arrLength; ++i) {
                if (arr[i] < arr[i-1]) {
                    inversionLocation = i;
                    break;
                }
            }
            if (inversionLocation == -1) break;
            if (numAnswers == MAX_ANSWERS) exit(1);

            num_nums fixLocation = -1;
            for (i = inversionLocation; i < arrLength; ++i) {
                if (arr[i] >= arr[inversionLocation-1]) {
                    fixLocation = i;
                    break;
                }
            }
            if (fixLocation == -1) break;
            
            REP(i, arrLength) {
                if (i < fixLocation-inversionLocation) newArr[i] = arr[inversionLocation+i];
                else if (i < fixLocation) newArr[i] = arr[i-(fixLocation-inversionLocation)];
                else newArr[i] = arr[i];
            }
            tempArr = arr;
            arr = newArr;
            newArr = tempArr;
            
            answers[numAnswers][0] = inversionLocation;
            answers[numAnswers][1] = fixLocation-inversionLocation;
        }

        printf("Case #" INT64 ": " INT64 "\n", l+1, numAnswers);
        REP(i, numAnswers) {
            printf(INT64 " " INT64 "\n", answers[i][0], answers[i][1]);
        }
    }
    
    return 0;
}