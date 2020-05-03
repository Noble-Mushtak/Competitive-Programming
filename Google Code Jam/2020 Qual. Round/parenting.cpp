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

typedef int64_t time_;
typedef int64_t num_events;
struct event {
    time_ start, end;
    num_events index;
};
typedef int64_t test_cases;

bool operator<(event e1, event e2) {
    if (e1.start != e2.start) return e1.start < e2.start;
    return e1.end < e2.end;
}

num_events numEvents;
event events[2000];
test_cases numTestCases;
char answer[2000];

int main() {
    test_cases l;
    scanf(INT64, &numTestCases);
    REP(l, numTestCases) {
        scanf(INT64, &numEvents);
        num_events i;
        REP(i, numEvents) {
            scanf(INT64 " " INT64, &(events[i].start), &(events[i].end));
            events[i].index = i;
        }
        std::sort(events, events+numEvents);
        
        time_ cBusyUntil = 0, jBusyUntil = 0;
        REP(i, numEvents) {
            if (cBusyUntil <= events[i].start) {
                answer[events[i].index] = 'C';
                cBusyUntil = events[i].end;
            } else if (jBusyUntil <= events[i].start) {
                answer[events[i].index] = 'J';
                jBusyUntil = events[i].end;
            } else {
                break;
            }
        }
        answer[numEvents] = '\0';
        
        printf("Case #" INT64 ": ", l+1);
        if (i < numEvents) puts("IMPOSSIBLE");
        else puts(answer);
    }
    
    return 0;
}