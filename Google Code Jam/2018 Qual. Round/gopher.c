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

typedef long num_cells;
typedef long dimen;
typedef struct {
    dimen x, y;
} coord;
typedef long test_cases;

coord minCorner, maxCorner;
num_cells target, have;
bool filled[1010][1010];

int main() {
    test_cases numTestCases, z;
    dimen i, j, indent, storeJ, chosenI, chosenJ;
    num_cells count, maxCount;
    coord newCell;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%li", &target);;
        memset(filled, false, sizeof(filled));
        have = 0;
        minCorner.x = maxCorner.x = minCorner.y = maxCorner.y = 500;
        while (true) {
            maxCount = 0;
            for (indent = 1; indent >= 0; indent--) {
                for (i = max(minCorner.x, minCorner.x+indent); i <= min(maxCorner.x-indent, maxCorner.x); i++) {
                    for (j = max(minCorner.x, minCorner.y+indent); j <= min(maxCorner.y-indent, maxCorner.y); j++) {
                        count = !filled[i][j];
                        if (j > minCorner.y) {
                            storeJ = j-1;
                            if (i > minCorner.x) count += !filled[i-1][storeJ];
                            count += !filled[i][storeJ];
                            if (i < maxCorner.x) count += !filled[i+1][storeJ];
                        }
                            storeJ = j;
                            if (i > minCorner.x) count += !filled[i-1][storeJ];
                            count += !filled[i][storeJ];
                            if (i < maxCorner.x) count += !filled[i+1][storeJ];
                        if (j < maxCorner.y) {
                            storeJ = j+1;
                            if (i > minCorner.x) count += !filled[i-1][storeJ];
                            count += !filled[i][storeJ];
                            if (i < maxCorner.x) count += !filled[i+1][storeJ];
                        }
                        if (count > maxCount) {
                            //fprintf(stderr, "%li %li %li\n", count, i, j);
                            maxCount = count;
                            chosenI = i;
                            chosenJ = j;
                        }
                    }
                }
                if (maxCount > 0) break;
            }

            i = chosenI, j = chosenJ;
            if (maxCount == 0) {
                if (maxCorner.x-minCorner.x < maxCorner.y-minCorner.y) {
                    if (maxCorner.x-500 < 500-minCorner.x) i = maxCorner.x, maxCorner.x++;
                    else i = minCorner.x, minCorner.x--;
                    j = (minCorner.y+maxCorner.y)/2;
                } else {
                    if (maxCorner.y-500 < 500-minCorner.y) j = maxCorner.y, maxCorner.y++;
                    else j = minCorner.y, minCorner.y--;
                    i = (minCorner.x+maxCorner.x)/2;
                }
            }
            {
                fprintf(stderr, "%li %li %li %li\n", minCorner.x, maxCorner.x, minCorner.y, maxCorner.y);
                if ((maxCorner.x-minCorner.x+1)*(maxCorner.y-minCorner.y+1) > have) {
                    if (maxCorner.x-minCorner.x >= 2) i = max(minCorner.x+1, min(maxCorner.x-1, i));
                    if (maxCorner.y-minCorner.y >= 2) j = max(minCorner.y+1, min(maxCorner.y-1, j));
                }
                i = max(2, min(999, i));
                j = max(2, min(999, j));
                printf("%li %li\n", i, j);
                fprintf(stderr, "%li %li\n", i, j);
                fflush(stdout);
                scanf("%li %li", &newCell.x, &newCell.y);
                if ((newCell.x == 0) && (newCell.y == 0)) break;
                if ((newCell.x == -1) && (newCell.y == -1)) exit(0);
                
                if (have == 0) minCorner.x = maxCorner.x = newCell.x, minCorner.y = maxCorner.y = newCell.y;
                else {
                    minCorner.x = min(minCorner.x, newCell.x);
                    maxCorner.x = max(maxCorner.x, newCell.x);
                    minCorner.y = min(minCorner.y, newCell.y);
                    maxCorner.y = max(maxCorner.y, newCell.y);
                }
                
                if (!filled[newCell.x][newCell.y]) have++;
                filled[newCell.x][newCell.y] = true;
                fprintf(stderr, "%li %li %li %li\n", newCell.x, newCell.y, have, (maxCorner.x-minCorner.x+1)*(maxCorner.y-minCorner.y+1));
            }
        }
    }
    
    exit(0);
}