/*
    https://code.google.com/codejam/contest/10224486/dashboard#s=p0
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
typedef long num_rounds;
typedef long choice;
typedef long num_choices;

num_rounds numRounds;
choice backwards[3][2] = {{0, 1}, {1, 2}, {0, 2}};
num_choices answerComps[13][3][3] = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}, requestedComp[3];
char answers[13][3][600000] = {{"P", "R", "S"}};

int main() {
    num_rounds i;
    num_choices j, k;
    choice c1, c2, storeChoice;
    test_cases numTestCases, l;
    scanf("%li", &numTestCases);

    REPEAT(i, 12) {
        REPEAT(j, 3) {
            c1 = backwards[j][0], c2 = backwards[j][1];
            if (strcmp(answers[i][c1], answers[i][c2]) > 0) c1 = backwards[j][1], c2 = backwards[j][0];
            strcpy(answers[i+1][j], answers[i][c1]);
            strcpy(answers[i+1][j]+strlen(answers[i][c1]), answers[i][c2]);
            REPEAT(k, 3) answerComps[i+1][j][k] = answerComps[i][c1][k]+answerComps[i][c2][k];
        }
        //printf("%s %s %s\n", answers[i+1][0], answers[i+1][1], answers[i+1][2]);
    }

    REPEAT(l, numTestCases) {
        scanf("%li %li %li %li", &numRounds, requestedComp+1, requestedComp+0, requestedComp+2);
        REPEAT(j, 3) {
            REPEAT(k, 3) if (answerComps[numRounds][j][k] != requestedComp[k]) break;
            if (k == 3) {
                printf("Case #%li: %s\n", l+1, answers[numRounds][j]);
                break;
            }
        }
        if (j == 3) printf("Case #%li: IMPOSSIBLE\n", l+1);
    }
    
    exit(0);
}