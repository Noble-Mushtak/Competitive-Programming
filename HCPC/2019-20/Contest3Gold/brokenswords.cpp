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

typedef int64_t num_swords;
typedef int64_t sword;

num_swords numSwords, numTBs, numLRs;
char swordS[10];

int main() {
    num_swords i;
    scanf("%" PRId64, &numSwords);
    REP(i, numSwords) {
        scanf("%s", swordS);
        numTBs += (swordS[0] == '0');
        numTBs += (swordS[1] == '0');
        numLRs += (swordS[2] == '0');
        numLRs += (swordS[3] == '0');
    }
    num_swords answer = std::min(numTBs/2, numLRs/2);
    num_swords numTBsLeft = numTBs-answer*2;
    num_swords numLRsLeft = numLRs-answer*2;
    printf("%" PRId64 " %" PRId64 " %" PRId64 "\n", answer, numTBsLeft, numLRsLeft);
    return 0;
}