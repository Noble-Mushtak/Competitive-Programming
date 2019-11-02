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

num_nums testCases, length;
std::priority_queue<num, std::vector<num>, std::greater<num>> arr1;
std::priority_queue<num> arr2;

int main() {
    scanf("%" PRId64, &testCases);
    num_nums l;
    REP(l, testCases) {
        scanf("%" PRId64, &length);
        num_nums i;
        REP(i, length) {
            num newNum;
            scanf("%" PRId64, &newNum);
            arr1.push(newNum);
        }
        REP(i, length) {
            num newNum;
            scanf("%" PRId64, &newNum);
            arr2.push(newNum);
        }
        num sum = 0;
        REP(i, length) {
            sum += arr1.top()*arr2.top();
            arr1.pop();
            arr2.pop();
        }
        printf("Case #%" PRId64 ": %" PRId64 "\n", l+1, sum);
    }
    return 0;
}