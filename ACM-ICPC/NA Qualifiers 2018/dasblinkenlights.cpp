#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>

#define REPEAT(token, num) for (token = 0; token < num; token++)

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num;

num gcd(num num1, num num2) {
    num remainder = num1, lastRemainder = num2, lastLastRemainder;
    while (remainder) {
        lastLastRemainder = lastRemainder, lastRemainder = remainder;
        remainder = lastLastRemainder % lastRemainder;
    }
    return lastRemainder;
}

num first, second, third, answer;

int main() {
    scanf("%" PRId64 " %" PRId64 " %" PRId64, &first, &second, &third);
    answer = first*second/gcd(first, second);
    if (answer <= third) puts("yes");
    else puts("no");
    
    exit(0);
}