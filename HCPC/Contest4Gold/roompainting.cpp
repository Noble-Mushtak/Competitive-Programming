#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <set>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num;
typedef int64_t num_nums;

num_nums numPaintCans, numColors;
std::set<num> paintCans;

int main() {
    scanf("%" PRId64 " %" PRId64, &numPaintCans, &numColors);
    num_nums i;
    REP(i, numPaintCans) {
        num paintCan;
        scanf("%" PRId64, &paintCan);
        paintCans.insert(paintCan);
    }
    
    num answer = 0;
    REP(i, numColors) {
        num color;
        scanf("%" PRId64, &color);
        answer += *paintCans.lower_bound(color)-color;
    }
    printf("%" PRId64 "\n", answer);
    
    return 0;
}