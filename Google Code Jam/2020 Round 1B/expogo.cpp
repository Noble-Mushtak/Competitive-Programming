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
typedef int64_t coord;
typedef int64_t num_chars;

coord curX, curY;
test_cases numTestCases;
char answer[100000];
num_chars answerLength;

int main() {
    test_cases l;
    scanf("%" PRId64, &numTestCases);
    REP(l, numTestCases) {
        scanf("%" PRId64 " %" PRId64, &curX, &curY);
        
        for (answerLength = 0; (curX != 0) || (curY != 0); answerLength++) {
            if ((curX & 1) ^ (curY & 1)) {
                if (curX & 1) {
                    if ((curX == 1) && (curY == 0)) {
                        answer[answerLength] = 'E', curX--;
                    } else if ((curX == -1) && (curY == 0)) {
                        answer[answerLength] = 'W', curX++;
                    } else if (((curX/2) & 1) ^ ((curY/2) & 1)) {
                        if (curX < 0) answer[answerLength] = 'W', curX++;
                        else answer[answerLength] = 'E', curX--;
                    } else {
                        if (curX < 0) answer[answerLength] = 'E', curX--;
                        else answer[answerLength] = 'W', curX++;
                    }
                } else {
                    if ((curY == 1) && (curX == 0)) {
                        answer[answerLength] = 'N', curY--;
                    } else if ((curY == -1) && (curX == 0)) {
                        answer[answerLength] = 'S', curY++;
                    } else if (((curX/2) & 1) ^ ((curY/2) & 1)) {
                        if (curY < 0) answer[answerLength] = 'S', curY++;
                        else answer[answerLength] = 'N', curY--;
                    } else {
                        if (curY < 0) answer[answerLength] = 'N', curY--;
                        else answer[answerLength] = 'S', curY++;
                    }
                }
                curX /= 2;
                curY /= 2;
                //printf("T " INT64 " " INT64 "\n", curX, curY);
            } else {
                printf("Case #" INT64 ": IMPOSSIBLE\n", l+1);
                break;
            }
        }
        if ((curX == 0) && (curY == 0)) {
            answer[answerLength] = '\0';
            printf("Case #" INT64 ": %s\n", l+1, answer); // */
            
            /* printf("Case #" INT64 ": ");
            num_chars i;
            REP(i, answerLength) putchar(answer[answerLength-i-1]);
            putchar('\n'); // */
        }
    }
    return 0;
}