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
typedef long long weight;
typedef long long fraction;
typedef long long num_weights;
typedef long long num_ratios;

num_weights numMolecules;
weight molecules[400][2];
fraction curRatio[2], minRatio[2], maxRatio[2], zero[2], continuedFraction[100000];
num_ratios numRatios, length;
bool flag;

int compareRatios(const void *ptr1, const void *ptr2) {
    fraction *ratio1 = (fraction*)ptr1, *ratio2 = (fraction*)ptr2;
    //r1[0]/r1[1] < r2[0]/r2[1] -> r1[0]*r2[1]-r1[1]*r2[0] < 0
    fraction key = ratio1[0]*ratio2[1]-ratio1[1]*ratio2[0];
    if (key == 0) return 0;
    return (key > 0) ? 1 : -1;
}

typedef fraction num;
num gcd(num num1, num num2) {
    num remainder = num1, lastRemainder = num2, lastLastRemainder;
    while (remainder) {
        lastLastRemainder = lastRemainder, lastRemainder = remainder;
        remainder = lastLastRemainder % lastRemainder;
    }
    return lastRemainder;
}

/*
ax+by < cx+dy
(a-c)x < (d-b)y
d-b > 0 -> (a-c)/(d-b) < y/x
d-b < 0 -> (a-c)/(d-b) > y/x
*/

int main() {
    num_weights i, j;
    num_ratios k;
    test_cases numTestCases, l;
    fraction temp, store1, store2;
    scanf("%lli", &numTestCases);
    zero[0] = 0, zero[1] = 1;
    
    REPEAT(l, numTestCases) {
        minRatio[0] = 1000000000, minRatio[1] = 1;
        maxRatio[0] = -1, maxRatio[1] = 1;
        scanf("%lli", &numMolecules);
        REPEAT(i, numMolecules) scanf("%lli %lli", molecules[i]+0, molecules[i]+1);
        
        flag = false;
        REPEAT(i, numMolecules) {
            REPEAT(j, i) {
                curRatio[0] = molecules[j][0]-molecules[i][0];
                curRatio[1] = molecules[i][1]-molecules[j][1];
                if (curRatio[1] == 0) {
                    if (molecules[j][1] > molecules[i][1]) {
                        flag = true;
                        break;
                    }
                } else {
                    if (curRatio[1] < 0) {
                        curRatio[0] *= -1;
                        curRatio[1] *= -1;
                        if (curRatio[0] <= 0) {
                            printf("%lli %lli | %lli %lli | %lli %lli\n", j, i, molecules[j][0], molecules[j][1], molecules[i][0], molecules[i][1]);
                            flag = true;
                            break;
                        }
                        if (compareRatios(curRatio, minRatio) < 0) minRatio[0] = curRatio[0], minRatio[1] = curRatio[1];
                    } else {
                        if (compareRatios(curRatio, maxRatio) > 0) maxRatio[0] = curRatio[0], maxRatio[1] = curRatio[1];
                    }
                }
            }
            if (flag) break;
        }
        if (flag) printf("Case #%lli: IMPOSSIBLE\n", l+1);
        else if (compareRatios(maxRatio, minRatio) >= 0) printf("Case #%lli: IMPOSSIBLE\n", l+1);
        else {
            //printf("%lli %lli | %lli %lli\n", minRatio[0], minRatio[1], maxRatio[0], maxRatio[1]);
            if (compareRatios(zero, maxRatio) > 0) maxRatio[0] = 0;
            if (maxRatio[0] == 0) {
                store1 = minRatio[0]/minRatio[1];
                if (store1 == 0) {
                    curRatio[0] = 1;
                    curRatio[1] = minRatio[1]/minRatio[0];
                } else if (minRatio[0] == minRatio[1]) {
                    curRatio[0] = 1, curRatio[1] = 2;
                } else {
                    curRatio[0] = 1, curRatio[1] = 1;
                }
            }
            else {
                length = 0;
                while (true) {
                    store1 = (minRatio[1] == 0) ? 1000000001 : minRatio[0]/minRatio[1];
                    store2 = (maxRatio[1] == 0) ? 1000000001 : maxRatio[0]/maxRatio[1];
                    if (store1 == store2) continuedFraction[length++] = store1;
                    else {
                        curRatio[0] = min(store1, store2)+1, curRatio[1] = 1;
                        break;
                    }
                    minRatio[0] %= minRatio[1];
                    maxRatio[0] %= maxRatio[1];
                    temp = minRatio[0], minRatio[0] = minRatio[1], minRatio[1] = temp;
                    temp = maxRatio[0], maxRatio[0] = maxRatio[1], maxRatio[1] = temp;
                }
                for (i = length-1; i >= 0; i--) {
                    temp = curRatio[0], curRatio[0] = curRatio[1], curRatio[1] = curRatio[0];
                    curRatio[0] += continuedFraction[i]*curRatio[1];
                    temp = gcd(curRatio[0], curRatio[1]);
                    curRatio[0] /= temp;
                    curRatio[1] /= temp;
                }
            }
            printf("Case #%lli: %lli %lli\n", l+1, curRatio[1], curRatio[0]);
        }
    }
    
    exit(0);
}