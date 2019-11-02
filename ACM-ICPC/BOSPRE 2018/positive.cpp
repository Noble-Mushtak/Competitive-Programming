#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cinttypes>

typedef int64_t num;

num gcd(num num1, num num2) {
    num remainder = num1, lastRemainder = num2, lastLastRemainder;
    while (remainder) {
        lastLastRemainder = lastRemainder, lastRemainder = remainder;
        remainder = lastLastRemainder % lastRemainder;
    }
    return lastRemainder;
}

num calcModuloInverse(num dividend, num MOD) {
    num lastRemainder = dividend, lastInverse = 1, remainder = MOD, inverse = 0, quotient, temp;
    while (remainder) {
        quotient = lastRemainder/remainder;
        temp = remainder, remainder = lastRemainder % remainder, lastRemainder = temp;
        temp = inverse, inverse = lastInverse-quotient*inverse, lastInverse = temp;
    }
    if (lastInverse < 0) lastInverse += MOD;
    return lastInverse;
}

num A, B, C, coeff1, coeff2, answer, x, y;
char testCase[10000];

int main() {
    while (true) {
        fgets(testCase, 10000, stdin);
        if (feof(stdin)) break;
        sscanf(testCase, "%" PRId64 " %" PRId64 " %" PRId64, &A, &B, &C);
        
        num gcdABC = gcd(gcd(A, B), C);
        coeff1 = A/gcdABC;
        coeff2 = B/gcdABC;
        answer = C/gcdABC;
        //printf("D %" PRId64 " | %" PRId64 " %" PRId64 " %" PRId64 "\n", gcdABC, coeff1, coeff2, answer);
        //printf("D %" PRId64 " %" PRId64 "\n", calcModuloInverse(coeff1, coeff2), calcModuloInverse(coeff2, coeff1));

        x = (calcModuloInverse(coeff1, coeff2)*answer) % coeff2;
        y = (calcModuloInverse(coeff2, coeff1)*answer) % coeff1;
        if (x == 0) x = coeff2;
        if (y == 0) y = coeff1;
        printf("%" PRId64 " * %" PRId64 " + %" PRId64 " * %" PRId64 " = %" PRId64 "\n", A, x, B, y, C);
        if ((A*x+B*y) != C) fprintf(stderr, "NO\n"), exit(1);
    }

    return 0;
}
