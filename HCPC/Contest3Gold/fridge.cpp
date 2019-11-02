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

typedef int64_t num_chars;

num_chars numChars, counts[10];
char input[2000];

int main() {
    num_chars i;
    scanf("%s", input);
    numChars = strlen(input);
    REP(i, numChars) counts[input[i]-'0']++;
    num_chars minCount = 10000;
    num_chars answer = -1;
    REP(i, 10) {
        if ((counts[i] < minCount) || ((counts[i] == minCount) && (answer == 0))) {
            minCount = counts[i];
            answer = i;
        }
    }
    
    if (answer == 0) {
        putchar('1');
    }
    REP(i, minCount+1) putchar(answer+'0');
    putchar('\n');
    
    return 0;
}