#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
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

typedef int64_t num;
typedef int64_t num_nums;

num_nums numNums;
num arr[200000], threshold;

int main() {
    num_nums i;
    scanf("%" PRId64 " %" PRId64, &numNums, &threshold);
    REP(i, numNums) scanf("%" PRId64, arr+i);
    std::sort(arr, arr+numNums);

    num answer;
    for (answer = 1; answer < numNums; answer++) {
        if (arr[answer]+arr[answer-1] > threshold) break;
    }
    printf("%" PRId64 "\n", answer);
    
    return 0;
}