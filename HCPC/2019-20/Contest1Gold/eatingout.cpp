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

int main() {
    int64_t numThings, num1, num2, num3;
    scanf("%" PRId64 " %" PRId64 " %" PRId64 " %" PRId64, &numThings, &num1, &num2, &num3);
    if ((numThings*2) < (num1+num2+num3)) puts("impossible");
    else puts("possible");
    return 0;
}