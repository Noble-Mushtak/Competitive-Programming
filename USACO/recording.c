/*
   PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=381
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

typedef short num_times;
typedef long time;

FILE *in, *out;
num_times length, answers[150][150], answer = 0;
time *times[150], timesMem[150][2];

int comparePrograms(const void *ptr1, const void *ptr2) {
    time *time1 = *(time**)ptr1, *time2 = *(time**)ptr2;
    if (time1[1] != time2[1]) return (time1[1] > time2[1])-(time1[1] < time2[1]);
    return (time1[0] > time2[0])-(time1[0] < time2[0]);
}

/*num_times calcAnswer(num_times startInd, num_times tune1, num_times tune2, bool onNext) {
    time start = -1, end, farthestEnd = -1;
    num_times i, j, added = 0, store, answer = -1;
    for (i = startInd; i < length; i++) {
        if (times[i][0] == start || (onNext && taken[i])) continue;
        start = times[i][0], end = times[i][1];
        if (farthestEnd != -1 && start > farthestEnd) break;
        if (farthestEnd < end) farthestEnd = end;
        added++, j = i;
        while (j < length && times[j][0] < end) j++;
        taken[i] = true;
        store = onNext ? calcAnswer(j, tune1, tune2+1, onNext) : calcAnswer(j, tune1+1, tune2, onNext);
        if (answer < store) answer = store;
        taken[i] = false;
        
    }
    if (!added && !onNext) return calcAnswer(0, tune1, 0, true);
    if (!added) return tune1+tune2;
    return answer;
}*/

int main() {
    num_times i;
    time store, track1 = 0, track2 = 0;
    
    in = fopen("recording.in", "r");
    fscanf(in, "%hi", &length);
    REPEAT(i, length) {
        times[i] = timesMem[i];
        fscanf(in, "%li %li", times[i]+0, times[i]+1);
    }
    fclose(in);
    
    qsort(times, length, sizeof(time*), comparePrograms);
    REPEAT(i, length) {
        store = times[i][0];
        if (store < track1) continue;
        else if (store < track2) {
            track1 = track2, track2 = times[i][1];
            answer++;
        } else {
            track2 = times[i][1];
            answer++;
        }
    }
    
    out = fopen("recording.out", "w");
    fprintf(out, "%hi\n", answer);
    fclose(out);
    
    exit(0);
}