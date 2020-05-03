#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t test_cases;
typedef int64_t num_pairs;
typedef int64_t num_bits;

num_bits numBits, samePairIndex, diffPairIndex;
num_pairs numPairs, numKnownPairs;
test_cases numTestCases;
bool samePairFound, diffPairFound, answer[200];

bool queryBit(num_bits queryIndex) {
    printf(INT64 "\n", queryIndex+1);
    fflush(stdout);
    char storeChar = '\0';
    while ((storeChar != '0') && (storeChar != '1') && (storeChar != 'N')) {
        storeChar = getchar();
    }
    if (storeChar == 'N') {
        fputs("ERROR: Invalid bit query", stderr);
        exit(1);
    }
    return storeChar == '1';
}

void queryNextPair() {
    answer[numKnownPairs] = queryBit(numKnownPairs);
    answer[numBits-1-numKnownPairs] = queryBit(numBits-1-numKnownPairs);
    if (answer[numKnownPairs] == answer[numBits-1-numKnownPairs]) {
        samePairFound = true;
        samePairIndex = numKnownPairs;
    } else {
        diffPairFound = true;
        diffPairIndex = numKnownPairs;
    }
    numKnownPairs++;
}

int main() {
    scanf(INT64 " " INT64, &numTestCases, &numBits);
    numPairs = numBits >> 1;
    
    test_cases l;
    REP(l, numTestCases) {
        samePairFound = diffPairFound = false;
        numKnownPairs = 0;
        
        num_bits i;
        REP(i, 5) queryNextPair();
        while (numKnownPairs < numPairs) {
            //fprintf(stderr, INT64 " " INT64 "\n", l+1, numKnownPairs);
            num_bits numQueriesLeft = 10;
            
            bool shouldComplement = false;
            if (samePairFound) {
                bool newBit = queryBit(samePairIndex);
                numQueriesLeft--;
                shouldComplement = (newBit != answer[samePairIndex]);
            }
            
            bool shouldReverse = shouldComplement;
            if (diffPairFound) {
                bool newBit = queryBit(diffPairIndex);
                numQueriesLeft--;
                shouldReverse ^= (newBit != answer[diffPairIndex]);
            }
            
            if (shouldComplement) {
                REP(i, numKnownPairs) {
                    answer[i] = !answer[i];
                    answer[numBits-1-i] = !answer[numBits-1-i];
                }
            }
            if (shouldReverse) {
                REP(i, numKnownPairs) {
                    bool temp = answer[i];
                    answer[i] = answer[numBits-1-i];
                    answer[numBits-1-i] = temp;
                }
            }
            
            while (numQueriesLeft >= 2) queryNextPair(), numQueriesLeft -= 2;
            while (numQueriesLeft > 0) queryBit(1), numQueriesLeft--;
        }
        
        REP(i, numBits) putchar(answer[i] ? '1' : '0');
        putchar('\n');
        fflush(stdout);
        char storeChar = '\0';
        while ((storeChar != 'Y') && (storeChar != 'N')) {
            storeChar = getchar();
        }
        if (storeChar == 'N') exit(0);
    }
    
    return 0;
}