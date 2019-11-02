#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <cmath>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

/*
theta=2atan(r/h)
arc angle=pi/4-2atan(r/h)
arc length = (2pi-(pi/4-2atan(r/h)))*r
line length = sqrt(h*h-r*r)
*/

typedef int64_t dimen;
typedef long double real;

int main() {
    while (true) {
        dimen radiusI, heightI, percentageI;
        scanf("%" PRId64 " %" PRId64 " %" PRId64, &radiusI, &heightI, &percentageI);
        if ((radiusI == 0) && (heightI == 0) && (percentageI == 0)) break;
        real radius = radiusI, height = heightI, percentage = percentageI;
        real theta = 2*asin(radius/height);
        real arcAngle = M_PI-theta;
        real arcLength = (2*M_PI-arcAngle)*radius;
        real lineLength = 2*sqrt(height*height-radius*radius);
        printf("%.2lf\n", static_cast<double>((1+percentage/100.0)*(arcLength+lineLength)));
    }
    return 0;
}