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

typedef int64_t dimen;
typedef int64_t num_stars;
typedef std::pair<dimen, dimen> point;

dimen numLines, lineLength;
num_stars answer, marked[5000][5000], stackSize;
char grid[5000][5000];
point stack[100000];

bool validPoint(dimen i, dimen j) {
    return (i >= 0) && (j >= 0) && (i < numLines) && (j < lineLength) && (grid[i][j] == '-');
}

void floodFill(dimen i, dimen j) {
    stackSize = 1;
    stack[0] = point(i, j);
    while (stackSize) {
        stackSize--;
        dimen curX = stack[stackSize].first, curY = stack[stackSize].second;
        marked[curX][curY] = answer;
        if (validPoint(curX-1, curY) && !marked[curX-1][curY]) stack[stackSize++] = point(curX-1, curY);
        if (validPoint(curX+1, curY) && !marked[curX+1][curY]) stack[stackSize++] = point(curX+1, curY);
        if (validPoint(curX, curY-1) && !marked[curX][curY-1]) stack[stackSize++] = point(curX, curY-1);
        if (validPoint(curX, curY+1) && !marked[curX][curY+1]) stack[stackSize++] = point(curX, curY+1);
    }
}

int main() {
    int64_t numCases = 0;
    while (true) {
        numCases++;
        dimen i, j;
        answer = 0;
        scanf("%" PRId64 " %" PRId64, &numLines, &lineLength);
        if (feof(stdin)) break;
        
        REP(i, numLines) {
            scanf("%s", grid[i]);
            REP(j, lineLength) marked[i][j] = 0;
        }
        
        REP(i, numLines) {
            REP(j, lineLength) if ((grid[i][j] == '-') && (marked[i][j] == 0)) answer++, floodFill(i, j);
        }
        printf("Case %" PRId64 ": %" PRId64 "\n", numCases, answer);
    }
    
    return 0;
}