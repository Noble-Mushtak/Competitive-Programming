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

typedef int64_t time_amount;

void printNumber(int64_t num) {
    if (num < 10) printf("0" INT64, num);
    else printf(INT64, num);
}

int main() {
    time_amount begHours, begMinutes, begSeconds, endHours, endMinutes, endSeconds;
    scanf(INT64 ":" INT64 ":" INT64 " " INT64 ":" INT64 ":" INT64, &begHours, &begMinutes, &begSeconds, &endHours, &endMinutes, &endSeconds);
    time_amount begTotal = begHours*3600+begMinutes*60+begSeconds;
    time_amount endTotal = endHours*3600+endMinutes*60+endSeconds;
    if (endTotal <= begTotal) endTotal += 3600*24;
    time_amount difference = endTotal-begTotal;
    printNumber(difference/3600);
    putchar(':');
    printNumber((difference % 3600)/60);
    putchar(':');
    printNumber(difference % 60);
    putchar('\n');
    return 0;
}