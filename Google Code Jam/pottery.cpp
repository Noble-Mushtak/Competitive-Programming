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

static inline std::vector<day> peekToken(num_vases curVase) {
    day curDay;
    scanf(INT64, &curDay);
    if (curDay == -1) exit(1);
    //fprintf(stderr, INT64 "\n", curDay);

    printf(INT64 " " INT64 "\n", curVase, (int64_t)0);
    fflush(stdout);

    num_tokens curNumTokens, i;
    std::vector<day> answer;
    scanf(INT64, &curNumTokens);
    REP(i, curNumTokens) {
        day storeDay;
        scanf(INT64, &storeDay);
        answer.push_back(storeDay);
    }
    return answer;
}

int main() {
    scanf(INT64, &numTestCases);
    while (numTestCases--) {
        day curDay, i, j;
        REP(i, 100-(20-CONTROL)-3*CONTROL2-1) {
            scanf(INT64, &curDay);
            if (curDay == -1) exit(1);
            //fprintf(stderr, INT64 "\n", curDay);
            
            printf(INT64 " " INT64 "\n", (i % CONTROL)+1, 100-i/CONTROL);
            fflush(stdout);
        }
        
        std::vector<info_pair> pairs;
        REP(i, 20-CONTROL) {
            num_vases curVase = i+CONTROL+1;
            num_tokens curTokens = peekToken(curVase).size();
            pairs.push_back(info_pair(curTokens, SIGN*curVase));
        }

        std::sort(pairs.begin(), pairs.end());
        REP(i, 3) REP(j, CONTROL2) putToken(SIGN*pairs[i+1].second);
        /* putToken(SIGN*pairs[1].second);
        putToken(SIGN*pairs[1].second);
        putToken(SIGN*pairs[2].second);
        putToken(SIGN*pairs[2].second);
        putToken(SIGN*pairs[3].second);
        putToken(SIGN*pairs[3].second);
        if (pairs[3].first <= pairs[0].first+1) putToken(SIGN*pairs[3].second);
        else putToken(SIGN*pairs[2].second); // */

        num_vases answer = SIGN*pairs[0].second;
        REP(i, pairs.size()) {
            fprintf(stderr, INT64 " " INT64 " " INT64 "\n", i, pairs[i].first, SIGN*pairs[i].second);
            fflush(stderr);
        }
        putToken(answer);
    }
    
    return 0;
}