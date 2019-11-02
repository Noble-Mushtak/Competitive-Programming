#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <queue>
#include <cmath>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_nums;
typedef int64_t num;
typedef long double real;

struct shape {
   bool isCircle;
   num radius;
   real squareRadius;
   shape(bool c, num r, real s) : isCircle(c), radius(r), squareRadius(s) {}
   
   real getNum() const {
       return isCircle ? radius : squareRadius;
   }

   bool operator<(const shape other) const {
       return getNum() < other.getNum();
   }
};

num_nums numPlots, numCircles, numSquares;
std::priority_queue<num> plots;
std::priority_queue<shape> houses;

int main() {
    scanf("%" PRId64 " %" PRId64 " %" PRId64, &numPlots, &numCircles, &numSquares);
    num_nums i;
    REP(i, numPlots) {
        num storePlot;
        scanf("%" PRId64, &storePlot);
        plots.push(storePlot);
    }
    REP(i, numCircles) {
        num storeRadius;
        scanf("%" PRId64, &storeRadius);
        houses.push(shape(true, storeRadius, storeRadius));
    }
    REP(i, numSquares) {
        num storeSide;
        scanf("%" PRId64, &storeSide);
        real storeReal = storeSide/std::sqrt(2);
        houses.push(shape(false, storeReal, storeReal));
    }
    num_nums answer = 0;
    while (true) {
        while (!houses.empty() && !plots.empty() && (houses.top().isCircle ? (houses.top().radius >= plots.top()) : (houses.top().squareRadius >= plots.top()))) houses.pop();
        if (houses.empty() || plots.empty()) break;
        answer++;
        houses.pop();
        plots.pop();
    }
    printf("%" PRId64 "\n", answer);
    return 0;
}
