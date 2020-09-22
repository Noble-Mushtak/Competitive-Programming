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
    while (true) {
        int64_t init, num1, num2, num3;
        scanf("%" PRId64 " %" PRId64 " %" PRId64 " %" PRId64, &init, &num1, &num2, &num3);
        if ((init == 0) && (num1 == 0) && (num2 == 0) && (num3 == 0)) break;
        
        int64_t answer = 360*2+360;
        while (init != num1) init--, init %= 40, init += 40, init %= 40, answer += 360/40;
        while (init != num2) init++, init %= 40, answer += 360/40;
        while (init != num3) init--, init %= 40, init += 40, init %= 40, answer += 360/40;
        printf("%" PRId64 "\n", answer);
    }
    return 0;
}