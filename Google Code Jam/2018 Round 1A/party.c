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

typedef long num_cashiers;
typedef long time;
typedef long num_items;
typedef long test_cases;

num_cashiers numSpots, numCashiers;
num_items numItems, maxPerCashier[1010], numPerCashier[1010];
time scanTimePerCashier[1010], constTimePerCashier[1010];

int main() {
    num_cashiers i;
    num_items numDistributed;
    test_cases numTestCases, z;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%li %li %li", &numSpots, &numItems, &numCashiers);
        REPEAT(i, numCashiers) scanf("%li %li %li", maxPerCashier+i, scanTimePerCashier+i, constTimePerCashier+i);
        
        
    }
    
    exit(0);
}