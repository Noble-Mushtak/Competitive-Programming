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

/*
mA+X=A -> (m-1)A=-X -> A=X/(1-m)
*/

int main() {
    int64_t slope, yIntercept;
    scanf("%" PRId64 " %" PRId64, &yIntercept, &slope);
    if (slope == 1) puts((yIntercept == 0) ? "ALL GOOD" : "IMPOSSIBLE");
    else printf("%.6lf\n", static_cast<double>(yIntercept)/static_cast<double>(1-slope));
    return 0;
}