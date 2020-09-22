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

typedef int64_t num_nums;
typedef int64_t num;

num_nums numNums;
num arr[100];

int main() {
    num_nums i;
    scanf("%" PRId64, &numNums);
    REP(i, numNums) scanf("%" PRId64, arr+i);
    num_nums answer = 1;
    num curMax = 1000000000;
    REP(i, numNums-2) {
        num newMax = std::max(arr[i], arr[i+2]);
        if (newMax < curMax) {
            answer = i+1;
            curMax = newMax;
        }
    }
    printf("%" PRId64 " %" PRId64 "\n", answer, curMax);
    
    return 0;
}