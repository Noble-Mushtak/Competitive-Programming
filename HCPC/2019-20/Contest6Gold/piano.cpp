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
typedef int64_t num_pianos;
typedef int64_t num_tuners;
typedef int64_t day;

num_pianos numPianos;
num_tuners numTuners, numPairs;
std::list<num_pianos> workDays[200];
bool solved[200];

int main() {
    test_cases testCases;
    scanf(INT64, &testCases);
    while (testCases--) {
        num_pianos i;
        day j;
        scanf(INT64 " " INT64, &numPianos, &numTuners);
        numPairs = numTuners/2;
        REP(i, numPianos) {
            day beg, end;
            scanf(INT64 " " INT64, &beg, &end);
            for (j = beg; j <= end; j++) workDays[j].push(i);
        }
        for (j = 1; j <= 100; j++) if (((j % 7) != 6) && ((j % 7) != 0)) {
            for (auto it = workDays[j].begin(); it != workDays[j].end(); ++it) {
                if (solved[*it]) continue;
                solved[*it] = true;
            }
        }
        bool weekendsNeeded = false;
        for (j = 1; j <= 100; j++) if (((j % 7) == 6) || ((j % 7) == 0)) {
            for (auto it = workDays[j].begin(); it != workDays[j].end(); ++it) {
                if (!solved[*it]) weekendsNeeded = true;
                solved[*it] = true;
            }
        }
    }
    
    return 0;
}