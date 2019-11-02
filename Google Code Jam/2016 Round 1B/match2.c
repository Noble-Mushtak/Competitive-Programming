#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

typedef short test_cases;
typedef short num_chars;
typedef long long number;

num_chars length;
char originalCoders[20], originalJammers[20], coders[20], jammers[20], desirableCoders[20], desirableJammers[20];
number codersValue, jammersValue, minDifference, diff, desirableCodersValue, desirableJammersValue;

int main() {
    test_cases numTestCases, caseNumber;
    num_chars i[6], j;
    scanf("%hi", &numTestCases);

    REPEAT(caseNumber, numTestCases) {
        scanf("%s %s", coders, jammers);
        //printf("%s %s\n", coders, jammers);
        length = (num_chars)strlen(coders);
        REPEAT(j, 3) coders[length+j] = jammers[length+j] = '\0';
        memcpy(originalCoders, coders, sizeof(originalCoders)), memcpy(originalJammers, jammers, sizeof(originalJammers));
        minDifference = 1001;
        REPEAT(i[0], ((originalCoders[0] == '?') ? 10 : 1)) {
            if (originalCoders[0] == '?') coders[0] = i[0]+'0';
            REPEAT(i[1], ((originalCoders[1] == '?') ? 10 : 1)) {
                if (originalCoders[1] == '?') coders[1] = i[1]+'0';
                REPEAT(i[2], ((originalCoders[2] == '?') ? 10 : 1)) {
                    if (originalCoders[2] == '?') coders[2] = i[2]+'0';
                    REPEAT(i[3], ((originalJammers[0] == '?') ? 10 : 1)) {
                        if (originalJammers[0] == '?') jammers[0] = i[3]+'0';
                        REPEAT(i[4], ((originalJammers[1] == '?') ? 10 : 1)) {
                            if (originalJammers[1] == '?') jammers[1] = i[4]+'0';
                            REPEAT(i[5], ((originalJammers[2] == '?') ? 10 : 1)) {
                                if (originalJammers[2] == '?') jammers[2] = i[5]+'0';
                                //if (caseNumber == 0) printf("%s %s\n", coders, jammers);
                                codersValue = jammersValue = 0;
                                REPEAT(j, length) {
                                    codersValue *= 10;
                                    codersValue += coders[j];
                                    jammersValue *= 10;
                                    jammersValue += jammers[j];
                                }
                                diff = codersValue-jammersValue;
                                if (jammersValue > codersValue) diff *= -1;
                                if ((diff < minDifference) || ((diff == minDifference) && ((codersValue < desirableCodersValue) || ((codersValue == desirableCodersValue) && (jammersValue < desirableJammersValue))))) {
                                    minDifference = diff;
                                    desirableCodersValue = codersValue;
                                    desirableJammersValue = jammersValue;
                                    memcpy(desirableCoders, coders, sizeof(desirableCoders));
                                    memcpy(desirableJammers, jammers, sizeof(desirableJammers));
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("Case #%hi: %s %s\n", caseNumber+1, desirableCoders, desirableJammers);
    }

    exit(0);
}