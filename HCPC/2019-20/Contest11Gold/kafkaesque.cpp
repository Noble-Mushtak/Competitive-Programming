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

int main() {
    num curNum, lastNum = 0;
    scanf("%" PRId64, &numNums);
    num_nums answer = 1;
    while (numNums--) {
        scanf("%" PRId64, &curNum);
        if (curNum < lastNum) answer++;
        lastNum = curNum;
    }
    printf("%" PRId64 "\n", answer);
    
    return 0;
}