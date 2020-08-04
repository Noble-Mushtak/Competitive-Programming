#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; ++token)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t test_cases;
typedef int64_t num_vertices;
typedef int64_t dimen;
struct point {
    dimen x, y;
};

test_cases numTestCases;
num_vertices numVertices;
point points[1000];

dimen sgn(dimen val) {
    return (0 < val) - (val < 0);
}

int main() {
    test_cases l;
    scanf(INT64, &numTestCases);
    REP(l, numTestCases) {
        scanf(INT64, &numVertices);
        num_vertices i;
        REP(i, numVertices) {
            scanf(INT64 " " INT64, &(points[i].x), &(points[i].y));
        }

        num_vertices start, end, i1, i2, maxAnswer = 0;
        REP(start, numVertices) {
            REP(end, numVertices) {
                if (start == end) continue;
                
                std::set<num_vertices> inContactWith;
                inContactWith.insert(start);
                inContactWith.insert(end);
                dimen correctY = points[start].y-points[end].y;
                dimen correctX = points[start].x-points[end].x;
                
                REP(i1, numVertices) {
                    REP(i2, numVertices) {
                        if (i1 == i2) continue;
                        dimen testY = points[i1].y-points[i2].y;
                        dimen testX = points[i1].x-points[i2].x;
                        if ((sgn(correctY) == sgn(testY)) &&
                            (sgn(correctX) == sgn(testX)) &&
                            //correctY/correctX = testY/testX
                            ((correctY*testX) == (correctX*testY))) {
                           inContactWith.insert(i1);
                           inContactWith.insert(i2);
                        }
                    }
                }
                
                maxAnswer = std::max(maxAnswer, (num_vertices)inContactWith.size());
            }
        }
        
        printf("Case #" INT64 ": " INT64 "\n", l+1, std::min(numVertices, maxAnswer+2));
    }
    
    return 0;
}