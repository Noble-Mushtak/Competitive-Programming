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
typedef int64_t num_nums;

num width;
num_nums numPartitions, numNums;
num arr[1000];
std::set<num> allAnswers;

int main() {
    num_nums i, j;
    scanf("%" PRId64 " %" PRId64, &width, &numPartitions);
    REP(i, numPartitions) scanf("%" PRId64, arr+(i+1));
    arr[0] = 0, arr[numPartitions+1] = width;
    numNums = numPartitions+2;
    
    REP(i, numNums) REP(j, i) {
        allAnswers.insert(arr[i]-arr[j]);
    }
    for (auto it = allAnswers.begin(); it != allAnswers.end(); ++it) {
        printf("%" PRId64 "%c", *it, (std::next(it) == allAnswers.end()) ? '\n' : ' ');
    }
    
    return 0;
}