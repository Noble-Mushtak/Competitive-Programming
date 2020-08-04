#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; ++token)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t test_cases;
typedef int64_t num;

test_cases numTestCases;
num leftPile, rightPile;
num MAX_ANSWER = 2000000000LL;

num findBiggestSumUnder(num query) {
    // n(n+1)/2 <= query
    // n(n+1) <= 2*query
    num left = 1, right = MAX_ANSWER;
    while (left < right) {
        num mid = (left+right)/2;
        if (mid*(mid+1) > 2*query) right = mid;
        else left = mid+1;
    }
    return right-1;
}

num findBiggestDoubleSumUnder(num query, num start) {
    // n(start+(n-1)) <= query
    num left = 0, right = MAX_ANSWER;
    while (left < right) {
        num mid = (left+right)/2;
        if (mid*(start+mid-1) > query) right = mid;
        else left = mid+1;
    }
    return right-1;
}

int main() {
    test_cases l;
    scanf(INT64, &numTestCases);
    REP(l, numTestCases) {
        scanf(INT64 " " INT64, &leftPile, &rightPile);
        
        num startFrom = 1;
        if (rightPile > leftPile) {
            num completed = findBiggestSumUnder(rightPile-leftPile);
            rightPile -= completed*(completed+1)/2;
            startFrom = completed+1;
        } else if (leftPile > rightPile) {
            num completed = findBiggestSumUnder(leftPile-rightPile);
            leftPile -= completed*(completed+1)/2;
            startFrom = completed+1;
        }

        num startFromEven = (startFrom & 1) ? (startFrom+1) : startFrom;
        num startFromOdd = (startFrom & 1) ? startFrom : (startFrom+1);
        num firstTerm1, firstTerm2;
        if ((rightPile <= leftPile) ^ (startFrom & 1)) {
            //Take evens from left, odds from right
            firstTerm1 = startFromEven;
            firstTerm2 = startFromOdd;
        } else {
            firstTerm1 = startFromOdd;
            firstTerm2 = startFromEven;
            //Take evens from right, odds from left
        }
        num numTerms1 = findBiggestDoubleSumUnder(leftPile, firstTerm1);
        num answer1 = firstTerm1+2*(numTerms1-1);
        num numTerms2 = findBiggestDoubleSumUnder(rightPile, firstTerm2);
        num answer2 = firstTerm2+2*(numTerms2-1);
        
        if (answer2 > answer1+1) answer2 = answer1+1;
        else if (answer1 > answer2+1) answer1 = answer2+1;
        PRINTF(INT64 " " INT64 " | " INT64 " " INT64 "\n", firstTerm1, firstTerm2, answer1, answer2);
        
        if (answer1 >= firstTerm1) leftPile -= (answer1+firstTerm1)/2*((answer1-firstTerm1)/2+1);
        if (answer2 >= firstTerm2) rightPile -= (answer2+firstTerm2)/2*((answer2-firstTerm2)/2+1);
        printf("Case #" INT64 ": " INT64 " " INT64 " " INT64 "\n", l+1, std::max(answer1, answer2), leftPile, rightPile);
    }
    
    return 0;
}