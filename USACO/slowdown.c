/*
    PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=379
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

typedef long measure;
typedef short num_measures;
typedef double exact_measure;

int compareMeasures(const void *ptr1, const void *ptr2) {
    measure store1 = *(measure*)ptr1, store2 = *(measure*)ptr2;
    return (store1 > store2)-(store1 < store2);
}

FILE *in, *out;
measure times[10000], dists[10000], slowness = 1;
num_measures total, timesLength = 0, distsLength = 0, timesVisited = 0, distsVisited = 0;
exact_measure timePassed = 0, curDist = 0;

int main() {
    num_measures i;
    measure store, storeTime, storeDist;
    char st[2];
    
    in = fopen("slowdown.in", "r");
    fscanf(in, "%hi", &total);
    REPEAT(i, total) {
        fscanf(in, "%s %li", st, &store);
        if (st[0] == 'T') times[timesLength++] = store;
        else dists[distsLength++] = store;
    }
    fclose(in);
    
    qsort(times, timesLength, sizeof(measure), compareMeasures);
    qsort(dists, distsLength, sizeof(measure), compareMeasures);
    REPEAT(i, total) {
        storeTime = times[timesVisited], storeDist = dists[distsVisited];
        if ((distsVisited == distsLength) ||(timesVisited != timesLength && storeTime < timePassed+(storeDist-curDist)*slowness)) {
            timesVisited++;
            curDist += (storeTime-timePassed)/slowness;
            timePassed = storeTime;
            slowness++;
        } else {
            distsVisited++;
            timePassed += (storeDist-curDist)*slowness;
            curDist = storeDist;
            slowness++;
        }
    }
    timePassed += (1000-curDist)*slowness;
    
    out = fopen("slowdown.out", "w");
    fprintf(out, "%li\n", (long) round(timePassed));
    fclose(out);
    
    exit(0);
}