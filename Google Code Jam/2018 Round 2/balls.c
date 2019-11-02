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

typedef long dimen;
typedef long num_balls;
typedef long test_cases;

dimen numColumns, numRows, curPos, shift[110];
num_balls goal[110];
char row[110];

int main() {
    test_cases z, numTestCases;
    dimen i, j;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%li", &numColumns);
        REPEAT(i, numColumns) scanf("%li", goal+i);
        if ((goal[0] < 1) || (goal[numColumns-1] < 1)) {
            printf("Case #%li: IMPOSSIBLE\n", z+1);
            continue;
        }
        
        numRows = 1, curPos = 0;
        memset(shift, 0, sizeof(shift));
        goal[0]--, goal[numColumns-1]--;
        for (i = 1; i < numColumns-1; i++) {
            while (goal[curPos] == 0) curPos++;
            if (curPos >= numColumns) exit(1);
            shift[i] = curPos-i;
            if (abs(shift[i])+1 > numRows) numRows = abs(shift[i])+1;
            goal[curPos]--;
        }
        
        printf("Case #%li: %li\n", z+1, numRows);
        REPEAT(i, numRows) {
            REPEAT(j, numColumns) {
                if (i+1 == numRows) row[j] = '.';
                else if (numRows-i-1 <= shift[j]) row[j] = '\\';
                else if (i+1-numRows >= shift[j]) row[j] = '/';
                else row[j] = '.';
            }
            row[numColumns] = '\0';
            printf("%s\n", row);
        }
    }
    
    exit(0);
}