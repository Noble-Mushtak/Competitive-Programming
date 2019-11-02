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
typedef long num_people;
typedef long party;
typedef long num_parties;

num_parties numParties, numMaxParties;
num_people parties[26];
num_people maxPeople, secondMaxPeople;
party maxParties[26];

int main() {
    test_cases numTestCases, z;
    party i;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        printf("Case #%li:", z+1);
        scanf("%li", &numParties);
        REPEAT(i, numParties) scanf("%li", parties+i);
        while (true) {
            maxPeople = 0, numMaxParties = 0, secondMaxPeople = 0;
            REPEAT(i, numParties) {
                if (parties[i] > maxPeople) {
                    secondMaxPeople = maxPeople;
                    maxPeople = parties[i];
                    numMaxParties = 1;
                    maxParties[0] = i;
                }
                else if (parties[i] == maxPeople) maxParties[numMaxParties++] = i;
                else secondMaxPeople = max(parties[i], secondMaxPeople);
            }
            if (maxPeople == 0) break;
            
            putchar(' ');
            putchar('A'+maxParties[0]), parties[maxParties[0]]--;
            if (!(numMaxParties & 1)) putchar('A'+maxParties[1]), parties[maxParties[1]]--;
        }
        putchar('\n');
    }
    
    exit(0);
}


