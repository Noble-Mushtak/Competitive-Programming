#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_minutes;
typedef int64_t num_times;

char timeString[10];
num_times numTimes;
num_minutes allTheTimes[1000];

void printNumber(num_minutes numMins) {
    if (numMins < 10) printf("0%" PRId64, numMins);
    else printf("%" PRId64, numMins);
}

void printTime(num_minutes numMins) {
    num_minutes numHours = numMins/60, numMinutes = numMins % 60;
    if (numHours >= 12) {
        printf("%" PRId64 ":", ((numHours == 12) ? 12 : (numHours-12)));
        printNumber(numMinutes);
        puts(" p.m.");
    } else {
        printf("%" PRId64 ":", ((numHours == 0) ? 12 : numHours));
        printNumber(numMinutes);
        puts(" a.m.");
    }
}

int main() {
    bool beg = true;
    num_times i;
    while (true) {
        scanf("%" PRId64, &numTimes);
        if (numTimes == 0) break;
        if (!beg) puts("");
        else beg = false;

        num_minutes numHours, numMinutes;
        REP(i, numTimes) {
            scanf("%" PRId64 ":%" PRId64 " %s", &numHours, &numMinutes, timeString);
            if (numHours == 12) numHours -= 12;
            if (timeString[0] == 'p') numHours += 12;
            allTheTimes[i] = numHours*60+numMinutes;
        }
        std::sort(allTheTimes, allTheTimes+numTimes);
        REP(i, numTimes) printTime(allTheTimes[i]);
    }

    return 0;
}