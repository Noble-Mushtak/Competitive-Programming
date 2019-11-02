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

typedef int64_t dimen;
typedef int64_t num_lanes;

int64_t mod(int64_t num1, int64_t num2) {
    int64_t answer = num1 % num2;
    if (answer < 0) answer += num2;
    return answer;
}

num_lanes numLanes, curLane, numDirecs;
dimen width, curPos;
dimen offset[1000], spaces[1000], speeds[1000];
char direcs[1000];

int main() {
    scanf("%" PRId64 " %" PRId64, &numLanes, &width);
    curLane = numLanes;
    num_lanes i, j;
    REP(i, numLanes) {
        scanf("%" PRId64 " %" PRId64 " %" PRId64, offset+i, spaces+i, speeds+i);
        if (i & 1) offset[i] = (width-1-offset[i]) % spaces[i];
    }
    scanf("%" PRId64 " %s", &curPos, direcs);
    
    numDirecs = strlen(direcs);
    REP(i, numDirecs) {
        if (direcs[i] == 'U') curLane--;
        if (direcs[i] == 'D') curLane++;
        if (direcs[i] == 'L') curPos--;
        if (direcs[i] == 'R') curPos++;
        if (curLane < 0) {
            puts("safe");
            exit(0);
        }
        if (curLane < numLanes) {
            dimen k;
            for (k = 1; k <= speeds[curLane]; k++) if (mod(curPos, spaces[curLane]) == mod(offset[curLane]+((curLane & 1) ? -1 : 1)*k, spaces[curLane])) {
                puts("squish");
                exit(0);
            }
            if ((mod(curPos, spaces[curLane]) == offset[curLane]) && (speeds[curLane] > 0)) {
                if ((direcs[i] == 'L') && ((curLane & 1) == 0)) {
                    puts("squish");
                    exit(0);
                }
                if ((direcs[i] == 'R') && (curLane & 1)) {
                    puts("squish");
                    exit(0);
                }
            }
            if ((mod(curPos, spaces[curLane]) == offset[curLane]) & (speeds[curLane] == 0)) {
                puts("squish");
                exit(0);
            }
        }
        REP(j, numLanes) offset[j] += ((j & 1) ? -1 : 1)*speeds[j], offset[j] = mod(offset[j], spaces[j]);
    }
    puts("squish");
    
    return 0;
}