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

typedef int64_t coord;
typedef int64_t answer;
typedef int64_t num_guesses;

const coord MAX_COORD = 1000000000;
coord minRadius, maxRadius;
num_guesses guessesLeft = 300;

char response[1000];
answer testPoint(coord x, coord y) {
    --guessesLeft;
    
    printf(INT64 " " INT64 "\n", x, y);
    //fprintf(stderr, INT64 " " INT64 "\n", x, y);
    fflush(stdout);
    scanf("%s", response);
    if (response[0] == 'C') return 2; //CENTER
    if (response[0] == 'H') return 1; //HIT
    if (response[0] == 'M') return 0; //MISS
    exit(0); //WRONG
}

void solveTestCase() {
    guessesLeft = 300;
    
    coord minX = minRadius-MAX_COORD, maxX = MAX_COORD-minRadius;
    coord minY = minRadius-MAX_COORD, maxY = MAX_COORD-minRadius;
    while (true) {
        if ((maxX-minX+1)*(maxY-minY+1) <= guessesLeft) {
            for (coord testX = minX; testX <= maxX; testX++) {
                for (coord testY = minY; testY <= maxY; testY++) {
                    answer curAns = testPoint(testX, testY);
                    if (curAns == 2) return;
                }
            }
            exit(1);
        }
        
        coord midX = (minX+maxX)/2;
        coord midY = (minY+maxY)/2;
        answer curAns = testPoint(midX, midY);
        if (curAns == 2) return;

        if (minX != maxX) {
            coord testX = midX-minRadius;
            answer curAns = testPoint(testX, midY);
            if (curAns == 2) return;
            if (curAns == 1) maxX = midX-1;
            else minX = midX;
        }
        if (minY != maxY) {
            coord testY = midY-minRadius;
            answer curAns = testPoint(midX, testY);
            if (curAns == 2) return;
            if (curAns == 1) maxY = midY-1;
            else minY = midY;
        }
    }
}

typedef int64_t test_cases;

test_cases numTestCases;

int main() {
    scanf(INT64 " " INT64 " " INT64, &numTestCases, &minRadius, &maxRadius);
    while (numTestCases--) solveTestCase();
    return 0;
}