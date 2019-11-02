/*
    https://code.google.com/codejam/contest/5304486/dashboard#s=p0
*/

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

typedef long test_cases;
typedef long dimen;
typedef struct {
    dimen x, y;
} point;
typedef struct {
    point min, max;
} rect;
typedef long num_chars;

dimen length, height;
rect cakePieces[26];
char grid[26][26];
bool present[26];

int main() {
    dimen i, j, j2;
    num_chars k;
    test_cases numTestCases, l;
    scanf("%li", &numTestCases);
    
    REPEAT(l, numTestCases) {
        scanf("%li %li", &height, &length);
        memset(grid, 0, sizeof(grid));
        memset(present, false, sizeof(present));
        REPEAT(i, height) {
            scanf("%s", grid[i]);
            REPEAT(j, length) {
                if (grid[i][j] == '?') grid[i][j] = '\0';
                else {
                    present[grid[i][j]-'A'] = true;
                    cakePieces[grid[i][j]-'A'].min.x = cakePieces[grid[i][j]-'A'].max.x = j;
                    cakePieces[grid[i][j]-'A'].min.y = cakePieces[grid[i][j]-'A'].max.y = i;
                }
            }
        }
        REPEAT(k, 26) if (present[k]) {
            while ((cakePieces[k].max.y+1 < height) && !grid[cakePieces[k].max.y+1][cakePieces[k].min.x]) {
                cakePieces[k].max.y++;
                grid[cakePieces[k].max.y][cakePieces[k].min.x] = k+'A';
            }
            while ((cakePieces[k].min.y > 0) && !grid[cakePieces[k].min.y-1][cakePieces[k].min.x]) {
                cakePieces[k].min.y--;
                grid[cakePieces[k].min.y][cakePieces[k].min.x] = k+'A';
            }
        }
        REPEAT(j, length) if (!grid[0][j]) {
            if (j == 0) {
                for (j2 = 0; !grid[0][j2]; j2++);
                REPEAT(i, height) grid[i][j] = grid[i][j2];
            }
            else REPEAT(i, height) grid[i][j] = grid[i][j-1];
        }
        printf("Case #%li:\n", l+1);
        REPEAT(i, height) printf("%s\n", grid[i]);
    }
    
    exit(0);
}