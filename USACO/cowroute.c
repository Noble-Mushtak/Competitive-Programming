/*
    PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=512
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define SET(arr, e1, e2) ( \
    (arr[0] = e1), \
    (arr[1] = e2) \
)
typedef signed char byte;

typedef short city;
typedef short num_cities;
typedef short num_flights;
typedef long long cost;
typedef cost costs[2];

FILE *in, *out;
num_cities numCities;
costs paths[1000][1000], pathsFromStart[1000];
num_flights length;
city start, end, flight[100];
bool visited[1000];

int main() {
    num_flights l;
    num_cities i, j, k;
    costs storeCosts;
    city min;
    //Fill paths and pathsFromStart with infinity
    memset(paths, 0x3F, sizeof(paths));
    memset(pathsFromStart, 0x3F, sizeof(pathsFromStart));
    //No cities have been visited yet
    memset(visited, false, sizeof(visited));
    
    in = fopen("cowroute.in", "r");
    fscanf(in, "%hi %hi %hi", &start, &end, &length);
    //Conversion to 0-based indexing
    start--, end--;
    REPEAT(l, length) {
        fscanf(in, "%lli %lli", storeCosts+0, storeCosts+1);
	REPEAT(j, storeCosts[1]) {
	    //Update costs of cities if lesser cost or equal cost and lesser length
	    fscanf(in, "%hi", flight+j);
	    //Calculate numCities (use 1-based indexing so numCities is higher than all cities)
	    if (flight[j] > numCities) numCities = flight[j];
	    //Conversion to 0-base indexing
	    flight[j]--;
	    REPEAT(k, j) if (storeCosts[0] < paths[flight[k]][flight[j]][0] || (storeCosts[0] == paths[flight[k]][flight[j]][0] && j-k < paths[flight[k]][flight[j]][1])) SET(paths[flight[k]][flight[j]], storeCosts[0], (j-k));
	}
    }
    fclose(in);
    
    //All cities can instantly reach themselves
    REPEAT(i, numCities) SET(paths[i][i], 0, 0);
    
    //Dijkstra's Algorithm
    //start can instantly visit itself
    SET(pathsFromStart[start], 0, 0);
    //To compare costs (true iff cost1 < cost2)
    #define COMPARECOSTS(cost1, cost2) (cost1[0] < cost2[0] || (cost1[0] == cost2[0] && cost1[1] < cost2[1]))
    REPEAT(i, numCities) {
        min = -1;
	REPEAT(j, numCities) if (!visited[j] && (min == -1 || COMPARECOSTS(pathsFromStart[j], pathsFromStart[min]))) min = j;
	
	//Visit min city
	visited[min] = true;
	REPEAT(j, numCities) {
	    SET(storeCosts, pathsFromStart[min][0], pathsFromStart[min][1]);
	    storeCosts[0] += paths[min][j][0];
	    storeCosts[1] += paths[min][j][1];
	    if (COMPARECOSTS(storeCosts, pathsFromStart[j])) SET(pathsFromStart[j], storeCosts[0], storeCosts[1]);
	}
    }
    
    //Write output
    //"-1 -1" if end is not reachable from start
    out = fopen("cowroute.out", "w");
    if (pathsFromStart[end][1] <= length) fprintf(out, "%lli %lli\n", pathsFromStart[end][0], pathsFromStart[end][1]);
    else fprintf(out, "-1 -1\n");
    fclose(out);
    
    exit(0);
}