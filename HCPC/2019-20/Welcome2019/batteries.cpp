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

typedef int64_t guess;
typedef int64_t num_guesses;

guess initialGuess;
num_guesses answer = 1;

int main() {
    while (true) {
        scanf("%" PRId64, &initialGuess);
        if (initialGuess == 0) break;
        answer = 1;
        int64_t newGuess = initialGuess-1;
        while (newGuess > 0) newGuess -= answer, answer++;
        printf("%" PRId64 "\n", answer-1);
    }
    
    return 0;
}