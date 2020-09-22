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

typedef int64_t dimen;
typedef std::pair<dimen, dimen> point;
typedef int64_t num_points;

std::set<point> allPoints;
num_points numPairs, numPoints;

bool isPresent(dimen x, dimen y) {
    return allPoints.find(point(x, y)) != allPoints.end();
}

int main() {
    num_points i;
    scanf("%" PRId64, &numPoints);
    REP(i, numPoints) {
        dimen storeX, storeY;
        scanf("%" PRId64 " %" PRId64, &storeX, &storeY);
        allPoints.insert(point(storeX, storeY));
    }
    for (auto it = allPoints.begin(); it != allPoints.end(); ++it) {
        dimen storeX = it->first, storeY = it->second;
        numPairs += isPresent(storeX-2018, storeY);
        numPairs += isPresent(storeX+2018, storeY);
        numPairs += isPresent(storeX, storeY-2018);
        numPairs += isPresent(storeX, storeY+2018);
        numPairs += isPresent(storeX-1118, storeY-1680);
        numPairs += isPresent(storeX+1118, storeY-1680);
        numPairs += isPresent(storeX-1118, storeY+1680);
        numPairs += isPresent(storeX+1118, storeY+1680);
        numPairs += isPresent(storeX-1680, storeY-1118);
        numPairs += isPresent(storeX+1680, storeY-1118);
        numPairs += isPresent(storeX-1680, storeY+1118);
        numPairs += isPresent(storeX+1680, storeY+1118);
    }
    printf("%" PRId64 "\n", numPairs/2);
    
    return 0;
}