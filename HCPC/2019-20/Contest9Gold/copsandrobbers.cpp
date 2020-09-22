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

typedef int64_t dimen;
typedef int64_t cost;
dimen numColumns, numRows;
const cost INFINITY = 1000000000;
cost grid[100][100];
bool outOfBounds(dimen i, dimen j) {
    if (i < 0) return true;
    if (i >= numColumns) return true;
    if (j < 0) return true;
    if (j >= numRows) return true;
    return false;
}
cost costAtCell(dimen i, dimen j) {
    if (outOfBounds(i, j)) return INFINITY;
    return grid[i][j];
}

cost answer;
typedef int64_t mode;
const mode LEFT = 0;
const mode UP = 1;
const mode RIGHT = 2;
const mode DOWN = 3;
const mode LEFT_UP = 4;
const mode LEFT_DOWN = 5;
const mode RIGHT_DOWN = 6;
const mode RIGHT_UP = 7;
cost newCosts[100][100];
void traverse(dimen i, dimen j, mode curMode) {
    if (outOfBounds(i, j)) return;
    if (curMode == LEFT) {
        newCost[i][j] = costAtCell(i, j-1)+costAtCell(i-1, j)+costAtCell(i, j+1)-costAtCell(i, j);
        traverse(i, j-1, LEFT_UP);
        traverse(i-1, j, LEFT);
        
    }
}

int main() {
    
    return 0;
}