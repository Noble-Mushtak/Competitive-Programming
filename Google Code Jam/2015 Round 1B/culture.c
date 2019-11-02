#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;
#define FASTIO(lvalue) (lvalue = getchar())
#define FASTEX(lvalue, char) (lvalue = lvalue*10+(char-'0'))
#define POPQUEUE(arr, len) memmove(arr, arr+1, len*sizeof(arr[0]))
#define REMOVEELEM(arr, off, len) memmove(arr+off, arr+(off+1), (len-off)*sizeof(arr[0]))
#define REMOVEELEMS(arr, off, len, num) memmove(arr+off, arr+(off+num), (len-off)*sizeof(arr[0]))
//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef byte test_cases;
typedef long long num;
typedef long long num_nums;
typedef byte digit;
typedef byte num_digits;

const num_nums NUM_POWS = 16;
num pow10s[16] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000}, goal;
num_nums answers[1000000] = {1}, answersLength = 1;

num flip(num test) {
    num newNum = 0, newTest = test;
    num_digits testDigits, curDigits;
    digit curDigitVal;
    REPEAT(testDigits, NUM_POWS) if (test < pow10s[testDigits]) break;
    for (curDigits = testDigits; curDigits > 0; curDigits--) {
        curDigitVal = newTest/pow10s[curDigits-1];
        newTest %= pow10s[curDigits-1];
        newNum += curDigitVal*pow10s[testDigits-curDigits];
    }
    return newNum;
}

int main() {
    char store;
    test_cases numTestCases = 0, l;
    num storeNum, flipped;
    while (FASTIO(store) != '\n') FASTEX(numTestCases, store);
    
    REPEAT(l, numTestCases) {
        goal = 0;
        while (FASTIO(store) != '\n') FASTEX(goal, store);
        for (; answersLength < goal; answersLength++) {
            storeNum = answersLength+1;
            flipped = flip(storeNum);
            if (flipped < storeNum && flip(flipped) == storeNum && answers[flipped-1] < answers[answersLength-1]) answers[answersLength] = answers[flipped-1]+1;
            else answers[answersLength] = answers[answersLength-1]+1;
        }
        printf("Case #%hhi: %lli\n", l+1, answers[goal-1]);
    }
    
    exit(0);
}
