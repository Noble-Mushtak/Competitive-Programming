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

typedef int64_t num_chars;

char string[1000];
num_chars numChars;

int main() {
    scanf("%s", string);
    numChars = strlen(string);
    num_chars testLen;
    num_chars minMods = 1000000;
    for (testLen = numChars; testLen <= 2*numChars; testLen++) {
        num_chars curChar, mods = 0;
        for (curChar = (testLen+1)/2; curChar < testLen; curChar++) if ((curChar >= numChars) || (string[curChar] != string[testLen-curChar-1])) mods++;
        minMods = std::min(mods, minMods);
    }
    printf(INT64 "\n", minMods);
    
    return 0;
}