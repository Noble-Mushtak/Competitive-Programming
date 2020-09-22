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

typedef int64_t num_minutes;
typedef int64_t num_submissions;

num_submissions numCorrect = 0;
num_minutes curTime, penalty[200], solved[200];
char result[10], problemNumber[10];

int main() {
    while (true) {
        scanf("%" PRId64, &curTime);
        if (curTime == -1) break;
        scanf("%s %s", problemNumber, result);
        problemNumber[0] -= 'A';
        if (solved[problemNumber[0]] > 0) continue;
        if (result[0] == 'r') solved[problemNumber[0]] = curTime;
        else penalty[problemNumber[0]] += 20;
    }
    num_submissions i;
    num_minutes answer = 0;
    REP(i, 200) if (solved[i] > 0) answer += penalty[i]+solved[i], numCorrect++;
    printf("%" PRId64 " %" PRId64 "\n", numCorrect, answer);
    
    return 0;
}