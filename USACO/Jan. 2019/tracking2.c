#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

typedef long long num;
typedef long long num_nums;

FILE *in, *out;
const num MOD = 1000000007;
const num MAX = 1000000000;
num_nums totalNums, minIntervalLength, numIntervals, intervalStart[100010], intervalValue[100010], intervalLength[100010];
num maxMin[100010], answer = 1;

num calcModuloExp(num base, num exp, num mod) {
    //For long long
    num result = 1, cur = base;
    inline num multiply(num num1, num num2) {
        num innerResult = 0, innerCur = num1;
        while (num2) {
            if (num2 & 1) innerResult += innerCur, innerResult %= mod;
            innerCur += innerCur, innerCur %= mod, num2 >>= 1;
        }
        return innerResult;
    }
    while (exp) {
        if (exp & 1) result = multiply(result, cur);
        cur = multiply(cur, cur), exp >>= 1;
    }
    return result;
}

int main() {
    num_nums i, j, k, intersectionLength, totalIntersection, firstIntersection, lastIntersection, tempAnswer;
    num temp, sign;
    
    in = fopen("tracking2.in", "r");
    fscanf(in, "%lli %lli", &totalNums, &minIntervalLength);
    REPEAT(i, totalNums-minIntervalLength+1) {
        fscanf(in, "%lli", &temp);
        if ((numIntervals == 0) || (temp != intervalValue[numIntervals-1])) {
            intervalStart[numIntervals] = i;
            intervalValue[numIntervals] = temp;
            intervalLength[numIntervals] = minIntervalLength;
            numIntervals++;
        }
        else intervalLength[numIntervals-1]++;
        for (j = i; j < i+minIntervalLength; j++) maxMin[j] = max(maxMin[j], temp);
    }
    fclose(in);

    REPEAT(i, numIntervals) {
        totalIntersection = 0;
        for (j = i; j < i+intervalLength[i]; j++) totalIntersection += (maxMin[j] == intervalValue[i]);
        tempAnswer = calcModuloExp(MAX-intervalValue[i]+1, totalIntersection, MOD);
        sign = 1;
        REPEAT(j, intervalLength[i]-minIntervalLength+1) {
            intersectionLength = minIntervalLength-j;
            if (intersectionLength <= 0) break;
            sign *= -1;
            REPEAT(k, intervalLength[i]-minIntervalLength-j+1) {
                if (k == 0) {
                    if (j == 0) {
                        firstIntersection = 0;
                        for (j = i; j < i+intersectionLength; j++) firstIntersection += (maxMin[j] == intervalValue[i]);
                    }
                    else firstIntersection -= (maxMin[i+j] == intervalValue[i]);
                    lastIntersection = firstIntersection;
                }
                else lastIntersection += (maxMin[i+j+k-1+intersectionLength] == intervalValue[i])-(maxMin[i+j+k-1] == intervalValue[i]);
                tempAnswer += sign*calcModuloExp(MAX-intervalValue[i], lastIntersection, MOD);
                tempAnswer += MOD;
                tempAnswer %= MOD;
            }
        }
        answer *= tempAnswer;
        answer %= MOD;
    }
    if (minIntervalLength == 1) answer = 1;
    
    out = fopen("tracking2.out", "w");
    fprintf(out, "%lli\n", answer);
    fclose(out);
    
    exit(0);
}