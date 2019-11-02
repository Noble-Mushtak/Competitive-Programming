#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num;
typedef int64_t num_nums;

num_nums numNums, numPairs;
num pairs[500][2];

int main() {
    num_nums i;
    scanf("%" PRId64 " %" PRId64, &numNums, &numPairs);
    REP(i, numPairs) {
        scanf("%" PRId64 " %" PRId64, pairs[i]+0, pairs[i]+1);
        pairs[i][0]--, pairs[i][1]--;
    }
    
    num_nums arr, answer = 0;
    REP(arr, (1 << numNums)) {
        bool valid = true;
        REP(i, numPairs) valid = valid && !(((arr >> pairs[i][0]) & 1) & ((arr >> pairs[i][1]) & 1));
        answer += valid;
    }
    printf("%" PRId64 "\n", answer);
    
    return 0;
}