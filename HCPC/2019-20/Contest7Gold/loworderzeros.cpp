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

typedef int64_t num_nums;
typedef int64_t num;

num_nums numFactors(num test, num factor) {
    num_nums answer = 0;
    while ((test % factor) == 0) test /= factor, answer += 1;
    return answer;
}

num instaPow(num base, num exp) {
    num result = 1, cur = base, MOD = 10;
    while (exp) {
        if (exp & 1) result *= cur, result %= MOD;
        cur *= cur, cur %= MOD, exp >>= 1;
    }
    return result;
}

num arr[1000010], answers[1000010];
num_nums num2s, num5s, min2and5s, no2and5s = 1;

int main() {
    for (num testCase = 1; testCase <= 1000000; testCase++) {
        num2s += numFactors(testCase, 2);
        num5s += numFactors(testCase, 5);
        num newNum = testCase;
        while ((newNum % 2) == 0) newNum /= 2;
        while ((newNum % 5) == 0) newNum /= 5;
        no2and5s *= newNum;
        no2and5s %= 10;
        min2and5s = std::min(num2s, num5s);
        answers[testCase] = (no2and5s*instaPow(2, num2s-min2and5s)*instaPow(5, num5s-min2and5s)) % 10;
        //printf(INT64 " " INT64 " " INT64 " " INT64 " " INT64 "\n", no2and5s, num2s, num5s, instaPow(2, num2s-min2and5s), instaPow(5, num2s-min2and5s));
        //printf(INT64 " " INT64 "\n", testCase, answers[testCase]);
    }
    while (true) {
        num cur;
        scanf(INT64, &cur);
        if (cur == 0) break;
        printf(INT64 "\n", answers[cur]);
    }
    return 0;
}