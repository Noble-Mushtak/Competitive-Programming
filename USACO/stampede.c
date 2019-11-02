/*
    PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=511
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

typedef long num_cows;
typedef long event;
typedef event* event_ptr;

FILE *in, *out;
num_cows length, numSeen, numCurrent;
event storage[100000][2], seen[100000], current[50000];
event_ptr cows[100000];

int compareCows(const void *ptr1, const void *ptr2) {
    event *pair1 = *(event**)ptr1, *pair2 = *(event**)ptr2;
    return (pair1[0] > pair2[0])-(pair1[0] < pair2[0]);
}

int main() {
    event store[3], min;
    num_cows i, j, k;
    bool storeBool;
    
    in = fopen("stampede.in", "r");
    //Get number of cows
    fscanf(in, "%li", &length);
    REPEAT(i, 2*length) cows[i] = storage[i];
    //Get cow data
    REPEAT(i, length) {
        fscanf(in, "%li %li %li", store+0, store+1, store+2);
	//cows will enter x=0 at -r*(x-1) and leave at -r*x
	store[0] *= -store[2];
	cows[2*i][0] = store[0]-store[2], cows[2*i][1] = store[1];
	cows[2*i+1][0] = store[0], cows[2*i+1][1] = -store[1];
    }
    //Two events for every cow
    length *= 2;
    fclose(in);
    
    //Sort cows by first priority time and second priority 
    qsort(cows, length, sizeof(event*), compareCows);
    REPEAT(i, length) {
        //Erase and add y-coordinates at current time
        for (j = i; j < length && cows[i][0] == cows[j][0]; j++) {
	    //printf("%li %li\n", cows[j][0], cows[j][1]);
	    if (cows[j][1] > 0) current[numCurrent++] = cows[j][1];
	    else REPEAT(k, numCurrent) if (-cows[j][1] == current[k]) {
	        memmove(current+k, current+k+1, (numCurrent-k-1)*sizeof(event));
		numCurrent--;
		break;
            }
	}
	//printf("%li\n", j);
	//Add closest cow if exists and not already included
	if (numCurrent) {
	    min = current[0];
	    REPEAT(k, numCurrent) if (min > current[k]) min = current[k];
	    storeBool = true;
	    REPEAT(k, numSeen) if (seen[k] == min) {
	        storeBool = false;
		break;
	    }
	    if (storeBool) seen[numSeen++] = min;
	}
	//Jump i to above all events at current time
	i = j-1;
    }
    
    //Print answer
    out = fopen("stampede.out", "w");
    fprintf(out, "%li\n", numSeen);
    fclose(out);
    
    exit(0);
}