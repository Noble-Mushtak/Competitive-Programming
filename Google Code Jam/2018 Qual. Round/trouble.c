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

typedef long num;
typedef long num_nums;
typedef long test_cases;

num arr[100010];
num_nums arrLength, evenIndices[100010], numEvens, oddIndices[100010], numOdds;

int main() {
    test_cases numTestCases, z;
    num_nums i;
    num first, second;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%li", &arrLength);
        numEvens = numOdds = 0;
        REPEAT(i, arrLength) {
            if (i & 1) oddIndices[numOdds++] = i;
            else evenIndices[numEvens++] = i;
            scanf("%li", arr+i);
        }
        int compareIndices(const void *ptr1, const void *ptr2) {
            num_nums index1 = *(num_nums*)ptr1, index2 = *(num_nums*)ptr2;
            return arr[index1]-arr[index2];
        }
        qsort(evenIndices, numEvens, sizeof(num_nums), compareIndices);
        qsort(oddIndices, numOdds, sizeof(num_nums), compareIndices);
        REPEAT(i, arrLength-1) {
            if (i & 1) first = arr[oddIndices[i/2]], second = arr[evenIndices[i/2+1]];
            else first = arr[evenIndices[i/2]], second = arr[oddIndices[i/2]];
            if (first > second) break;
        }
        if (i == arrLength-1) printf("Case #%li: OK\n", z+1);
        else printf("Case #%li: %li\n", z+1, i);
    }
    
    exit(0);
}