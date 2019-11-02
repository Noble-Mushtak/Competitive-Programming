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

typedef long num_balls;
typedef long num_jugglers;
typedef long test_cases;
typedef struct {
    num_balls red, blue;
} config;

num_balls red, blue, level;
num_jugglers answer, maximum[510][510], listSize;
config list[252000];

int main() {
    test_cases z, numTestCases;
    num_jugglers i, j, oldListSize, curMax;
    num_balls possRed, possBlue, maxRed, maxBlue;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%li %li", &red, &blue);
        answer = 0, level = 1;
        while ((red > 0) || (blue > 0)) {
            if (red+blue < level) {
                red -= red, blue -= blue;
            } else {
                memset(maximum, 0, sizeof(maximum));
                listSize = 1, list[0].red = 0, list[0].blue = 0, curMax = 0;
                REPEAT(i, level+1) {
                    oldListSize = listSize;
                    REPEAT(j, oldListSize) {
                        possRed = list[j].red+i;
                        possBlue = list[j].blue+(level-i);
                        if ((possRed <= red) && (possBlue <= blue)) {
                            if (maximum[possRed][possBlue] == 0) {
                                list[listSize].red = possRed;
                                list[listSize].blue = possBlue;
                                listSize++;
                            }
                            maximum[possRed][possBlue] = max(maximum[possRed][possBlue], maximum[list[j].red][list[j].blue]+1);
                            if (maximum[possRed][possBlue] >= curMax) {
                                maxRed = possRed;
                                maxBlue = possBlue;
                                curMax = maximum[possRed][possBlue];
                            }
                        }
                    }
                }
                //printf("%li %li %li\n", level, maxRed, maxBlue);
                red -= maxRed, blue -= maxBlue, answer += maximum[maxRed][maxBlue];
                level++;
            }
        }
        printf("Case #%li: %li\n", z+1, answer);
    }
    
    exit(0);
}