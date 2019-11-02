/*
    https://codejam.withgoogle.com/codejam/contest/4304486/dashboard
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef signed char byte;
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
static inline void POPQUEUE(void *arr, size_t length, size_t itemSize) { memmove(arr, arr+itemSize, length*itemSize); }
static inline void REMOVEELEM(void *arr, size_t offset, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+1)*itemSize), (length-offset)*itemSize); }
static inline void REMOVEELEMS(void *arr, size_t offset, size_t numElems, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+numElems)*itemSize), (length-offset)*itemSize); }
//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef byte test_cases;
typedef short num_chars;

num_chars queryLength, firstCharIndex;
char query[1001], answer[2002];

int main() {
    test_cases numTestCases, caseNumber;
    num_chars i;
    scanf("%hhi", &numTestCases);

    REPEAT(caseNumber, numTestCases) {
        scanf("%s", query);
        queryLength = (num_chars) strlen(query);
        
        REPEAT(i, queryLength) {
            if (i == 0) answer[firstCharIndex = 1001] = query[i];
            else if (query[i] < answer[firstCharIndex]) answer[firstCharIndex+i] = query[i];
            else answer[--firstCharIndex] = query[i];
        }
        answer[firstCharIndex+queryLength] = '\0';
        printf("Case #%hhi: %s\n", caseNumber+1, answer+firstCharIndex);
    }

    exit(0);
}