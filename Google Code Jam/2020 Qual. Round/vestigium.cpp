#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t test_cases;
typedef int64_t num;
typedef int64_t num_nums;

num_nums dimension;
num matrix[200][200];
test_cases numTestCases;

int main() {
    test_cases l;
    scanf(INT64, &numTestCases);
    REP(l, numTestCases) {
        scanf(INT64, &dimension);
        
        num trace = 0;
        num_nums i, j;
        REP(i, dimension) {
            REP(j, dimension) {
                scanf(INT64, matrix[i]+j);
                if (i == j) trace += matrix[i][j];
            }
        }

        num_nums numRowsBad = 0;
        REP(i, dimension) {
            std::set<num> numsSoFar;
            REP(j, dimension) {
                if (numsSoFar.find(matrix[i][j]) != numsSoFar.end()) {
                    numRowsBad++;
                    break;
                }
                numsSoFar.insert(matrix[i][j]);
            }
        }

        num_nums numColumnsBad = 0;
        REP(j, dimension) {
            std::set<num> numsSoFar;
            REP(i, dimension) {
                if (numsSoFar.find(matrix[i][j]) != numsSoFar.end()) {
                    numColumnsBad++;
                    break;
                }
                numsSoFar.insert(matrix[i][j]);
            }
        }
        
        printf("Case #" INT64 ": " INT64 " " INT64 " " INT64 "\n", l+1, trace, numRowsBad, numColumnsBad);
    }
    
    return 0;
}