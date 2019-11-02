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
typedef long num_cuts;
typedef long num_cells;
typedef long test_cases;

dimen numRows, numColumns, cutLocations[110];
num_cuts numHoriz, numVert;
num_cells cumGrid[110][110], subportions[110];
bool grid[110][110];
char storage[110];

int main() {
    dimen i, j;
    num_cells countInRow, curPortion, cellsPerPortion, cellsPerSubportion;
    num_cuts numPortions, numSubportions;
    test_cases numTestCases, z;
    bool newSubportion, failure;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%li %li %li %li", &numRows, &numColumns, &numHoriz, &numVert);
        REPEAT(i, numRows) {
            scanf("%s", storage);
            countInRow = 0;
            REPEAT(j, numColumns) {
                grid[i][j] = (storage[j] == '@');
                countInRow += grid[i][j];
                if (i == 0) cumGrid[i][j] = countInRow;
                else cumGrid[i][j] = cumGrid[i-1][j]+countInRow;
            }
        }
        if (cumGrid[numRows-1][numColumns-1] == 0) {
            printf("Case #%li: POSSIBLE\n", z+1);
            continue;
        }

        if ((cumGrid[numRows-1][numColumns-1] % (numHoriz+1)) > 0) {
            printf("Case #%li: IMPOSSIBLE\n", z+1);
            continue;
        }
        numPortions = curPortion = 0;
        cellsPerPortion = cumGrid[numRows-1][numColumns-1]/(numHoriz+1);
        REPEAT(i, numRows) {
            curPortion += cumGrid[i][numColumns-1];
            if (i > 0) curPortion -= cumGrid[i-1][numColumns-1];
            if (curPortion == cellsPerPortion) {
                cutLocations[numPortions++] = i;
                curPortion = 0;
            }
            else if (curPortion > cellsPerPortion) break;
        }
        if (i < numRows) {
            printf("Case #%li: IMPOSSIBLE\n", z+1);
            continue;
        }
        if (numPortions != numHoriz+1) exit(1);
        
        if ((cellsPerPortion % (numVert+1)) > 0) {
            printf("Case #%li: IMPOSSIBLE\n", z+1);
            continue;
        }        
        numSubportions = 0;
        memset(subportions, 0, sizeof(subportions));
        cellsPerSubportion = cellsPerPortion/(numVert+1);
        REPEAT(j, numColumns) {
            newSubportion = false, failure = false;
            REPEAT(i, numPortions) {
                subportions[i] += cumGrid[cutLocations[i]][j];
                if (j > 0) subportions[i] -= cumGrid[cutLocations[i]][j-1];
                if (i > 0) subportions[i] -= cumGrid[cutLocations[i-1]][j];
                if ((i > 0) && (j > 0)) subportions[i] += cumGrid[cutLocations[i-1]][j-1];
                //printf("%li %li %li %li\n", i, j, subportions[i], cellsPerSubportion);
                if ((subportions[i] == cellsPerSubportion) && !newSubportion && (i == 0)) newSubportion = true;
                else if (subportions[i] > cellsPerSubportion) {
                    failure = true;
                    break;
                }
                else if (newSubportion && (subportions[i] != cellsPerSubportion)) {
                    newSubportion = false;
                }
            }
            if (failure) {
                printf("Case #%li: IMPOSSIBLE\n", z+1);
                break;
            }
            if (newSubportion) numSubportions++, memset(subportions, 0, sizeof(subportions));
        }
        
        if (j == numColumns) {
            printf("Case #%li: POSSIBLE\n", z+1);
            if (numSubportions != numVert+1) exit(1);
        }
    }
    
    exit(0);
}