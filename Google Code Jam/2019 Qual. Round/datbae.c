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

typedef long long loc;
typedef long long num_locs;
typedef long long num_queries;

enum constants { NUM_CALLS = 4 };
num_queries numTestCases, numQueries;
num_locs numComputers, numMissing, numFound, numDetermined;
loc lastFiveBits[1050], base, missing[1050];
char query[1050], results[NUM_CALLS][1050];
bool existing[1050];

int main() {
    loc storeLoc;
    num_locs i;
    num_queries j, l;
    scanf("%lli", &numTestCases);
    
    REPEAT(l, numTestCases) {
        scanf("%lli %lli %lli", &numComputers, &numMissing, &numQueries);
        numFound = numComputers-numMissing;
        REPEAT(i, numComputers) existing[i] = false;
        REPEAT(j, NUM_CALLS) {
            REPEAT(i, numComputers) query[i] = ((i >> j) & 1)+'0';
            query[numComputers] = 0;
            printf("%s\n", query);
            fflush(stdout);
            scanf("%s", results[j]);
        }
        
        base = 0;
        REPEAT(i, numFound) {
            lastFiveBits[i] = 0;
            REPEAT(j, NUM_CALLS) lastFiveBits[i] += (results[j][i]-'0') << j;
            if ((i > 0) && (lastFiveBits[i] <= lastFiveBits[i-1])) base += 1 << NUM_CALLS;
            existing[base+lastFiveBits[i]] = true;
        }
        numDetermined = 0;
        REPEAT(i, numComputers) {
            if (!existing[i]) missing[numDetermined++] = i;
        }
        if (numDetermined != numMissing) {
            printf("ERROR: Found %lli missing instead of %lli\n", numDetermined, numMissing);
            exit(1);
        }
        REPEAT(i, numMissing) printf("%lli%c", missing[i], (i+1 == numMissing) ? '\n' : ' ');
        fflush(stdout);
        scanf("%lli", &storeLoc);
        if (storeLoc == -1) exit(0);
    }
    
    exit(0);
}