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

typedef long long test_cases;
typedef long long sword;
typedef long long num_swords;

sword charles[100010], charlesMax[100010], delila[100010], delilaMax[100010], tolerance;
num_swords numSwords, answer;

int main() {
    test_cases numTestCases, l;
    num_swords i, j;
    scanf("%lli", &numTestCases);
    
    REPEAT(l, numTestCases) {
        scanf("%lli %lli", &numSwords, &tolerance);
        REPEAT(i, numSwords) scanf("%lli", charles+i);
        REPEAT(i, numSwords) scanf("%lli", delila+i);
        answer = 0;
        REPEAT(i, numSwords) {
            REPEAT(j, i) charlesMax[j] = max(charles[i], charlesMax[j]);
            REPEAT(j, i) delilaMax[j] = max(delila[i], delilaMax[j]);
            charlesMax[i] = charles[i];
            delilaMax[i] = delila[i];
            REPEAT(j, i+1) {
                answer += max(charlesMax[j]-delilaMax[j], delilaMax[j]-charlesMax[j]) <= tolerance;
            }
            printf("%lli %lli\n", i, answer);
        }
        printf("Case #%lli: %lli\n", l+1, answer);
    }
    
    exit(0);
}