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

typedef long long num;
typedef long long num_nums;

num_nums numQueries, numLength, secondNumLength;
char digits[110], secondNum[110];

int main() {
    num_nums l, i;
    scanf("%lli", &numQueries);
    
    REPEAT(l, numQueries) {
        scanf("%s", digits);
        numLength = strlen(digits), secondNumLength = 0;
        REPEAT(i, numLength) {
            if (digits[i] == '4') {
                digits[i] = '3';
                secondNum[secondNumLength++] = '1';
            } else if (secondNumLength > 0) secondNum[secondNumLength++] = '0';
        }
        secondNum[secondNumLength] = 0;
        printf("Case #%lli: %s %s\n", l+1, digits, secondNum);
    }
    
    exit(0);
}