#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=nativ\
e")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <cmath>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked

typedef int64_t num_months;
typedef int64_t num_queries;
typedef double rate;
typedef double money;

num_months numMonths;
num_queries numQueries;
money amounts[300], deposits[300], withdrawals[300];
int64_t factor = 10000000;

money calcRate(num_months beg, num_months end, rate r) {
    money curMoney = amounts[beg];
    num_months curMonth;
    for (curMonth = beg; curMonth < end; curMonth++) curMoney = (1+r/100.0)*(cu\
rMoney+deposits[curMonth]-withdrawals[curMonth]);
    return curMoney;
}

rate solveForAnnual(rate monthly) {
    return 100.0*(std::pow(1+monthly/100.0, 12)-1.0);
}

char name[10000], inputLine[10000];

int main() {
    while (true) {
        fgets(name, 10000, stdin);
       if (feof(stdin)) break;

        num_months i;
        fgets(inputLine, 10000, stdin);
        sscanf(inputLine, "%" PRId64 " %" PRId64, &numMonths, &numQueries);
        REP(i, numMonths) {
            fgets(inputLine, 10000, stdin);
            sscanf(inputLine, "%lf %lf %lf", amounts+i, deposits+i, withdrawals+i);
        }

        printf(name);
        while (numQueries--) {
            num_months beg, end;
            fgets(inputLine, 10000, stdin);
            sscanf(inputLine, "%" PRId64 " %" PRId64, &beg, &end);
            beg--, end--;
            rate left = -2*factor, right = 2*factor;
            while (left < right) {
                rate mid = (left+right)/2;
                if (calcRate(beg, end, mid/(factor/10.0)) < amounts[end]) left = mid+1;
                else right = mid;
            }
            printf("%" PRId64 " %" PRId64 " %.2lf\n", beg+1, end+1, solveForAnnual(left/(factor/10.0)));
        }
    }

    exit(0);
}