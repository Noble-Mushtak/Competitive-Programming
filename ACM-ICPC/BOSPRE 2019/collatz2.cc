#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked

typedef int64_t num;

num f(num n) {
    if ((n % 2) == 0) return n/2;
    if ((n % 3) == 0) return n/3;
    return 5*n+1;
}

num testCase;
char inputLine[10000];

int main() {
    while (true) {
        fgets(inputLine, 10000, stdin);
        if (feof(stdin)) break;
        sscanf(inputLine, "%" PRId64, &testCase);
        num original = testCase;
        num answer = 0;
        while (testCase != 1) testCase = f(testCase), answer++;
        printf("%" PRId64 " %" PRId64 "\n", original, answer);
    }
    exit(0);
}