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

/*
R_1, 2R_1, 4R_1, 8R_1, ...
R_2, R_2, 2R_2, 2R_2, 4R_2, 4R_2, ...
R_3, R_3, R_3, 2R_3, 2R_3, 2R_3, 4R_3, 4R_3, 4R_3, ...

Day n: There are 2^(floor(n/x))*R_x X-Day rings
*/

typedef long long num_rings;
typedef long long test_cases;

num_rings answers[6], storeSum;

int main() {
    test_cases numTestCases, l;
    scanf("%lli %lli", &numTestCases, &l);
    
    REPEAT(l, numTestCases) {
        puts("200");
        fflush(stdout);
        scanf("%lli", &storeSum);
        answers[5] = (storeSum >> 33) & 0x7f;
        answers[4] = (storeSum >> 40) & 0x7f;
        answers[3] = (storeSum >> 50) & 0x7f;
        puts("40");
        fflush(stdout);
        scanf("%lli", &storeSum);
        storeSum -= answers[5] << 6;
        storeSum -= answers[4] << 8;
        storeSum -= answers[3] << 10;
        answers[2] = (storeSum >> 13) & 0x7f;
        answers[1] = (storeSum >> 20) & 0x7f;
        answers[0] = (storeSum >> 40) & 0x7f;
        printf("%lli %lli %lli %lli %lli %lli\n", answers[0], answers[1], answers[2], answers[3], answers[4], answers[5]);
        fflush(stdout);
        scanf("%lli", &storeSum);
        if (storeSum == -1) exit(0);
    }
    
    exit(0);
}