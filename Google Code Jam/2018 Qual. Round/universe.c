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
typedef long damage;
typedef long num_commands;

damage threshold;
char commands[100];
num_commands numCommands, answer;

int main() {
    test_cases numTestCases, z;
    num_commands i, swapIndex;
    damage curDamage, shotValue;
    char tempChar;
    scanf("%li", &numTestCases);

    REPEAT(z, numTestCases) {
        scanf("%li %s", &threshold, commands);
        numCommands = strlen(commands), answer = 0;
        while (true) {
            shotValue = 1, curDamage = 0, swapIndex = -1;
            REPEAT(i, numCommands) {
                if (commands[i] == 'C') shotValue *= 2;
                if (commands[i] == 'S') {
                    if ((i > 0) && (commands[i-1] == 'C')) swapIndex = i;
                    curDamage += shotValue;
                }
            }
            if (curDamage <= threshold) {
                printf("Case #%li: %li\n", z+1, answer);
                break;
            }
            if (swapIndex == -1) {
                printf("Case #%li: IMPOSSIBLE\n", z+1);
                break;
            }
            tempChar = commands[swapIndex-1];
            commands[swapIndex-1] = commands[swapIndex];
            commands[swapIndex] = tempChar;
            answer++;
        }
    }
    
    exit(0);
}