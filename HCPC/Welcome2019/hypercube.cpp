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

typedef int64_t num_bits;

num_bits findIndex(num_bits codeLength, char *code) {
    if (codeLength == 1) return code[0]-'0';
    if (code[0] == '0') return findIndex(codeLength-1, code+1);
    else return (static_cast<int64_t>(1) << codeLength)-findIndex(codeLength-1, code+1)-1;
}

num_bits numBits;
char code1[100], code2[100];

int main() {
    scanf("%" PRId64 " %s %s", &numBits, code1, code2);
    printf("%" PRId64 "\n", findIndex(numBits, code2)-findIndex(numBits, code1)-1);
    return 0;
}