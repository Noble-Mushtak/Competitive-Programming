#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <set>
#include <queue>

typedef int64_t num_items;

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_nums;
typedef int64_t num;

num arr[2000];
num_nums numQueries, numNums;
std::set<num> sums;

int main() {
    int64_t numCases = 0;
    while (true) {
        numCases++;
        scanf("%" PRId64, &numNums);
        if (feof(stdin)) break;
        printf("Case %" PRId64 ":\n", numCases);
        sums.clear();

        num_nums i, j;
        REP(i, numNums) scanf("%" PRId64, arr+i);
        REP(i, numNums) REP(j, numNums) if (j != i) sums.insert(arr[i]+arr[j]);
        
        scanf("%" PRId64, &numQueries);
        REP(i, numQueries) {
            num query;
            scanf("%" PRId64, &query);
            auto itLow = sums.lower_bound(query);
            num low = (itLow == sums.begin()) ? 100000000 : *std::prev(itLow);
            auto itHigh = sums.upper_bound(query);
            num high = (itHigh == sums.end()) ? 100000000 : *itHigh;
            //printf("%" PRId64 " %" PRId64 "\n", low, high);
            num answer = low;
            if (std::abs(query-high) < std::abs(query-answer)) answer = high;
            if (itHigh != sums.begin()) {
                num thirdAnswer = *std::prev(itHigh);
                if (std::abs(query-thirdAnswer) < std::abs(query-answer)) answer = thirdAnswer;
            }
            printf("Closest sum to %" PRId64 " is %" PRId64 ".\n", query, answer);
        }
    }
    return 0;
}