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
    int64_t numBridges, numKnights, numPerGroup;
    scanf("%" PRId64 " %" PRId64 " %" PRId64, &numBridges, &numKnights, &numPerGroup);
    int64_t numGroups = numKnights/numPerGroup;
    int64_t numBridgesLeft = numBridges-1;
    printf("%" PRId64 "\n", (numBridgesLeft+numGroups-1)/numGroups);
    return 0;
}