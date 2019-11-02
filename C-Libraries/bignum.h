/**
 * bignum (and others)
 *
 * typedefs:
 * scalar: Equivalent to a "digit" or "alphabet" for bignum.
 * num_scalars: Type for indexing the scalars in bignum.
 *
 * Constants:
 * ANDS: In binary, 30 contiguous 1s. This is used for modulo instead of the % operator, so one "digit" in a bignum can go from 0 to ANDS.
 *
 * Callable Functions:
 * bool lessThan(bignum num, bignum compare)
 * * Return true if num is less than compare.
 * void add(bignum num, bignum addend)
 * * Adds num and addend. Result is stored in num.
 * void subtract(bignum num, bignum subtrahend)
 * * Subtracts num by subtrahend. Result is stored in num.
 * void multiply(bignum num, scalar multiplier)
 * * Multiplies num by multiplier. Result is stored in num.
 * void divide(bignum num, scalar divisor)
 * * Divides num by scalar. Result is stored in num.
 * scalar divide(bignum num, bignum divisor)
 * * Divides num by divisor. Assumes that the ratio is less than 1000000 and rounds to the nearest integer.
 * scalar modulo(bignum num, scalar divisor)
 * * Finds the modulo of num mod divisor.
*/

#pragma once

#include <stdint.h>

typedef int64_t scalar;
typedef long num_scalars;
typedef scalar bignum[60000];
const scalar ANDS = (1 << 30)-1;

bool lessThan(bignum num, bignum compare) {
    num_scalars i;
    //First, compare the number of digits
    if (num[0] < compare[0]) return true;
    else if (num[0] > compare[0]) return false;
    //If the number of digits are the same, find the greatest-value unequal digits in the numbers
    for (i = num[0]; (i > 0) && (num[i] == compare[i]); i--);
    //Return if the digit in num is less than that in compare
    return num[i] < compare[i];
}

void add(bignum num, bignum addend) {
    scalar carry;
    num_scalars i, j;
    //Add a bunch of 0s to the front of num so that these digits can be used if the addition carries over
    for (i = num[0]+1; i <= addend[0]+1; i++) num[i] = 0;
    num[i] = 0;
    //Go through all the digits in addend from least-value to greatest-value
    for (i = 1; i <= addend[0]; i++) {
        //Add the digit to num, store the carry, and take the modulo
        num[i] += addend[i], carry = (num[i] >> 30), num[i] &= ANDS;
        //Keep carrying over the carry as necessary
        for (j = 1; carry > 0; j++) num[i+j] += carry, carry = (num[i+j] >> 30), num[i+j] &= ANDS;
        //Update the size of num
        if (num[i+j-1] && num[0] < i+j-1) num[0] = i+j-1;
    }
}

void subtract(bignum num, bignum subtrahend) {
    num_scalars i, j;
    //Go through all the digits in subtrahend from greatest-value to least-value
    for (i = subtrahend[0]; i >= 1; i--) {
        //Subtract the digit from num
        num[i] -= subtrahend[i];
        //Add any negative digits by 1 << 30 and subtract 1 from the next digit in order to borrow
        for (j = i; num[j] < 0; j++) num[j] += (1 << 30), num[j+1]--;
    }
    //Decrease size of num as necessary
    while (num[num[0]] == 0 && num[0] > 0) num[0]--;
}

bignum answer;
void multiply(bignum num, scalar multiplier) {
    num_scalars i;
    //Set answer to all 0s by default
    memset(answer, 0, (num[0]+2)*sizeof(scalar));
    //If multiplier is non-zero, go through the digits of num from least-value to greatest-value
    if (multiplier > 0) for (i = 1; i <= num[0]; i++) {
        //Multiply the digit of num by multiplier, add any carry over to the next digit, and take the modulo
        answer[i] += num[i]*multiplier, answer[i+1] += (answer[i] >> 30), answer[i] &= ANDS;
        //If needed, make the size of answer 1 more than the size of num
        if (i == num[0]) answer[0] = (answer[i+1] ? num[0]+1 : num[0]);
    }
    //Copy answer over to num
    memcpy(num, answer, (answer[0]+1)*sizeof(scalar));
}

bignum testBignum, testBignum2, testBignum3;
scalar divide(bignum num, bignum divisor) {
    scalar test, beg = 0, end = 1000000;
    //Do a binary search so that beg is the least number such that beg*divisor >= num
    while (beg < end) {
        test = (beg+end)/2;
        memcpy(testBignum, divisor, (divisor[0]+1)*sizeof(scalar)), multiply(testBignum, test);
        if (lessThan(testBignum, num)) beg = test+1;
        else end = test;
    }
    if (beg == 0) return 0;
    //testBigNum = (beg-1)*divisor
    memcpy(testBignum, divisor, (divisor[0]+1)*sizeof(scalar)), multiply(testBignum, beg-1);
    //testBignum2 = beg*divisor
    memcpy(testBignum2, divisor, (divisor[0]+1)*sizeof(scalar)), multiply(testBignum2, beg);
    //testBignum3 = num
    memcpy(testBignum3, num, (num[0]+1)*sizeof(scalar));
    //testBignum2 = beg*divisor-num, testBignum3 = num-(beg-1)*divisor
    subtract(testBignum2, num), subtract(testBignum3, testBignum);
    //If num is closer to (beg-1)*divisor than beg*divisor, return beg-1
    if (lessThan(testBignum3, testBignum2)) return beg-1;
    //If num is closer to beg*divisor than (beg-1)*divisior (or is halfway in between the two), return beg
    else return beg;
}

void divide(bignum num, scalar divisor) {
    scalar store;
    num_scalars i;
    //Go through the digits of num from greatest-value to least-value
    for (i = num[0]; i >= 1; i--) {
        //Divide this digit by the divisor, but store any remainder lost to division
        store = num[i] % 10, num[i] /= 10;
        //If necessary, add the remainder to the digit preceding this one
        if (i > 1) num[i-1] += (store << 30);
    }
    //Decrease the size of num as necessary
    if (!num[num[0]]) num[0]--;
}

scalar modulo(bignum num, scalar divisor) {
    scalar answer = 0, power = 1;
    num_scalars i;
    //For each digit in num, add answer by the digit times the appropriate power of 2^30 and then update power for the next digit
    for (i = 1; i <= num[0]; i++) answer += (num[i]*power % divisor), answer %= divisor, power <<= 30, power %= divisor;
    return answer;
}