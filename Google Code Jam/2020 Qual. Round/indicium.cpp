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
typedef int64_t dimen;
typedef int64_t value;

test_cases numTestCases;
dimen sideLength;
value trace, answer[200][200];
std::set<dimen> columnsLeftInRow[200], rowsLeftByValue[200], columnsTakenByValue[200];

template <class T> void remove(std::set<T> &s, T element) {
    auto it = s.find(element);
    if (it == s.end()) {
        fputs("Could not find element!", stderr);
        exit(1);
    }
    s.erase(it);
}

template <class T> bool contains(std::set<T> &s, T element) {
    auto it = s.find(element);
    return (it == s.end());
}

void mark(value val, dimen row, dimen column) {
    remove(columnsLeftInRow[row], column);
    remove(rowsLeftByValue[val], row);
    columnsTakenByValue[val].insert(column);
    answer[row][column] = val;
}

void completePermutation(value val) {
    while (!rowsLeftByValue[val].empty()) {
        auto nextRowIt = rowsLeftByValue[val].begin();
        dimen nextRow = *nextRowIt;
        bool brokeOutOfLoop = false;
        for (auto columnIt = columnsLeftInRow[nextRow].begin(); columnIt != columnsLeftInRow[nextRow].end(); ++columnIt) {
            dimen nextColumn = *columnIt;
            if (contains(columnsTakenByValue[val], nextColumn)) continue;
            mark(val, nextRow, nextColumn);
            brokeOutOfLoop = true;
            break;
        }
        if (!brokeOutOfLoop) {
            fprintf(stderr, "Bad permutation for value " INT64 "!\n", val);
            exit(1);
        }
    }
}

int main() {
    test_cases l;
    scanf(INT64, &numTestCases);
    REP(l, numTestCases) {
        scanf(INT64 " " INT64, &sideLength, &trace);
        dimen i, j;
        REP(i, sideLength) {
            columnsLeftInRow[i].clear();
            rowsLeftByValue[i+1].clear();
            columnsTakenByValue[i+1].clear();
            REP(j, sideLength) {
                columnsLeftInRow[i].insert(j);
                rowsLeftByValue[i+1].insert(j);
            }
        }
        
        value smallerDiagElem = trace/sideLength;
        value biggerDiagElem = smallerDiagElem+1;
        dimen numBigs = trace % sideLength;
        dimen numSmalls = sideLength-numBigs;
        if ((numBigs != 1) && (numSmalls != 1)) {
            REP(i, sideLength) {
                if (i < numSmalls) mark(smallerDiagElem, i, i);
                else mark(biggerDiagElem, i, i);
            }
            completePermutation(smallerDiagElem);
            completePermutation(biggerDiagElem);
        } else {
            if ((smallerDiagElem == 1) || (biggerDiagElem == sideLength)) {
                printf("Case #" INT64 ": IMPOSSIBLE\n", l+1);
                continue;
            }
            REP(i, sideLength) {
                if (i == 0) mark(smallerDiagElem-1, 0, 0);
                else if (i < numSmalls) mark(smallerDiagElem, i, i);
                else if (i < sideLength-1) mark(biggerDiagElem, i, i);
                else mark(biggerDiagElem+1, i, i);
            }
            completePermutation(smallerDiagElem-1);
            completePermutation(smallerDiagElem);
            completePermutation(biggerDiagElem);
            completePermutation(biggerDiagElem+1);
        }
        
        REP(i, sideLength) completePermutation(i+1);
        printf("Case #" INT64 ": POSSIBLE\n", l+1);
        REP(i, sideLength) REP(j, sideLength) printf(INT64 "%c", answer[i][j], (j+1 == sideLength) ? '\n' : ' ');
    }
    
    return 0;
}