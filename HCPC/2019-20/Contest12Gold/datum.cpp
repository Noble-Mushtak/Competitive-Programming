#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
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

typedef int64_t num;

num days[100] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
num month, day;
typedef const char *c_str;
c_str names[100] = {"Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday"};

int main() {
    scanf("%" PRId64 " %" PRId64, &day, &month);
    num sum = 0, i;
    for (i = 0; i < month-1; i++) sum += days[i];
    num answer = (sum+day) % 7;
    puts(names[answer]);
    return 0;
}