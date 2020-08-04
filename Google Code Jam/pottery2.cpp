/*
    https://codingcompetitions.withgoogle.com/codejam/round/0000000000051679/00000000001461c8
*/

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
typedef int64_t day;
typedef int64_t num_tokens;
typedef int64_t num_vases;

test_cases numTestCases;
const num_vases CONTROL = 16;
const num_vases CONTROL2 = 3;
const num_vases SIGN = -1;

typedef std::pair<num_tokens, num_vases> info_pair;

static inline void putToken(num_vases curVase) {
    day curDay;
    scanf(INT64, &curDay);
    if (curDay == -1) exit(1);
    //fprintf(stderr, INT64 "\n", curDay);

    printf(INT64 " " INT64 "\n", curVase, (int64_t)100);
    fflush(stdout);
}

int main() {
    scanf(INT64, &numTestCases);
    while (numTestCases--) {
        day i;
        REP(i, 80) peekToken(1);
        REP(i, 20) putToken(i+1);
    }
    
    return 0;
}