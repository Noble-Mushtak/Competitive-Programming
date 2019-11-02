#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <array>
#include <algorithm>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num;
typedef int64_t num_nums;

int main() {
    std::array<num, 5> list;
    num_nums i, j;
    REP(i, 5) scanf("%" PRId64, &(list[i]));
    while (true) {
        REP(i, 4) {
            if (list[i] > list[i+1]) {
                num temp = list[i];
                list[i] = list[i+1];
                list[i+1] = temp;
                REP(j, 5) printf("%" PRId64 "%c", list[j], (j+1 == 5) ? '\n' : ' ');
                bool good = true;
                REP(j, 5) if (list[j] != j+1) good = false;
                if (good) exit(0);
            }
        }
    }
    return 0;
}