#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <vector>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef double ratio;
typedef int64_t num_nums;
typedef int64_t num;
typedef int64_t num_cuts;

ratio neededRatio;
num_nums numNums, answer = 1000;
num nums[10000];
num minElem, maxElem;
num_cuts cuts[10000];

num_nums findMinAndMax() {
    num_nums maxIndex = 0;
    num numCutsMaxElem = cuts[0];
    num_nums i;
    REP(i, numNums) {
        num_nums numPortions = cuts[i]+1;
        num curMinElem = nums[i]/numPortions;
        num curMaxElem = (nums[i]+numPortions-1)/numPortions;
        if (i == 0) minElem = curMinElem, maxElem = curMaxElem;
        else {
            if (minElem > curMinElem) minElem = curMinElem;
            if ((maxElem < curMaxElem) || ((maxElem == curMaxElem) && (cuts[i] < numCutsMaxElem))) maxElem = curMaxElem, maxIndex = i, numCutsMaxElem = cuts[i];
        }
    }
    return maxIndex;
}

int main() {
    scanf("%lf %" PRId64, &neededRatio, &numNums);
    num_nums i;
    REP(i, numNums) scanf("%" PRId64, nums+i), cuts[i] = 0;

    num_cuts answer;
    REP(answer, 500) {
        num_nums maxIndex = findMinAndMax();
        if (static_cast<ratio>(minElem)/static_cast<ratio>(maxElem) > neededRatio+.0001) break;
        cuts[maxIndex]++;
    }
    printf("%" PRId64 "\n", answer);
    
    return 0;
}