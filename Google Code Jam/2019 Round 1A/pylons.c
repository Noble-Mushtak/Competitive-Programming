#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef const char *const_string;
typedef long long loc;
typedef loc pair[2];
typedef long long test_cases;

loc answer25[][2] = {{2, 3}, {1, 1}, {2, 4}, {1, 2}, {2, 5}, {1, 3}, {2, 1}, {1, 5}, {2, 2}, {1, 4}, {0, 0}};
loc answer34[][2] = {{2, 2}, {3, 4}, {1, 3}, {3, 2}, {1, 1}, {2, 3}, {3, 1}, {2, 4}, {1, 2}, {3, 3}, {2, 1}, {1, 4}, {0, 0}};
loc answer35[][2] = {{3, 2}, {1, 1}, {2, 3}, {3, 1}, {2, 4}, {1, 2}, {3, 3}, {1, 4}, {3, 5}, {2, 2}, {1, 5}, {2, 1}, {3, 4}, {1, 3}, {2, 5}, {0, 0}};
loc answer44[][2] = {{3, 2}, {2, 4}, {4, 3}, {2, 2}, {4, 1}, {3, 3}, {1, 4}, {4, 2}, {2, 1}, {3, 4}, {1, 1}, {2, 3}, {3, 1}, {1, 2}, {4, 4}, {1, 3}, {0, 0}};
loc answer45[][2] = {{1, 1}, {3, 2}, {2, 4}, {4, 3}, {1, 4}, {3, 3}, {1, 2}, {4, 1}, {2, 2}, {3, 4}, {1, 5}, {2, 3}, {3, 5}, {4, 2}, {1, 3}, {4, 4}, {2, 1}, {4, 5}, {3, 1}, {2, 5}, {0, 0}};
loc answer55[][2] = {{1, 1}, {3, 2}, {2, 4}, {4, 3}, {2, 2}, {3, 4}, {1, 3}, {4, 4}, {2, 3}, {4, 2}, {5, 4}, {2, 5}, {3, 3}, {1, 4}, {5, 3}, {4, 1}, {3, 5}, {5, 2}, {4, 5}, {3, 1}, {1, 5}, {2, 1}, {5, 5}, {1, 2}, {5, 1}, {0, 0}};
loc x, y;
bool switchCoords;

int main() {
    test_cases numTestCases, l;
    loc temp, prevRow, prevColumn, prevSum, prevDiff;
    pair *answer;
    scanf("%lli", &numTestCases);
    
    REPEAT(l, numTestCases) {
        scanf("%lli %lli", &x, &y);
        switchCoords = (x > y);
        if (switchCoords) temp = x, x = y, y = temp;
        if (x+y < 7) {
            printf("Case #%lli: IMPOSSIBLE\n", l+1);
            continue;
        }
        printf("Case #%lli: POSSIBLE\n", l+1);
        if ((x == 2) && (y == 5)) answer = answer25;
        if ((x == 3) && (y == 4)) answer = answer34;
        if ((x == 3) && (y == 5)) answer = answer35;
        if ((x == 4) && (y == 4)) answer = answer44;
        if ((x == 4) && (y == 5)) answer = answer45;
        if ((x == 5) && (y == 5)) answer = answer55;
        prevRow = prevColumn = prevSum = prevDiff = -10000;
        while (answer[0][0] != 0) {
            if (switchCoords) printf("%lli %lli\n", answer[0][1], answer[0][0]);
            else printf("%lli %lli\n", answer[0][0], answer[0][1]);
            answer++;
            if (answer[0][0] == prevRow) printf("%lli\n", l), exit(1);
            if (answer[0][1] == prevColumn) printf("%lli\n", l), exit(1);
            if (answer[0][0]+answer[0][1] == prevSum) printf("%lli\n", l), exit(1);
            if (answer[0][0]-answer[0][1] == prevDiff) printf("%lli\n", l), exit(1);
            prevRow = answer[0][0], prevColumn = answer[0][1];
            prevSum = prevRow+prevColumn, prevDiff = prevRow-prevColumn;
        }
    }
    
    exit(0);
}