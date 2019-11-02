/*
    PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=513
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;

typedef byte num_fields;
typedef byte field;
typedef short dist;
typedef short num_paths;

FILE *in, *out;
dist bessDists[100][100], elseDists[100][100];
num_paths length;
num_fields numFields;
bool bessPosses[100][10001], elsePosses[100][10001];

void solve(dist dists[100][100], bool posses[100][10001]) {
    field i, k;
    dist j;
    //posses[a][b] is true iff source can reach a in path of b length
    //Can reach beginning instantly
    posses[0][0] = true;
    REPEAT(i, numFields) REPEAT(j, 100*numFields+1) if (posses[i][j]) {
        //Set new possibilities to true
        for (k = i+1; k < numFields; k++) if (dists[i][k]) {
            posses[k][j+dists[i][k]] = true;
        }
    }
}

int main() {
    dist i;
    num_paths l;
    field store[2];
    dist storeBessDist, storeElseDist;
    bool possible;
    
    in = fopen("meeting.in", "r");
    fscanf(in, "%hhi %hi", &numFields, &length);
    //Get all paths
    REPEAT(l, length) {
        fscanf(in, "%hhi %hhi %hi %hi", store+0, store+1, &storeBessDist, &storeElseDist);
        //Conversion to 0-based indexing
        store[0]--, store[1]--;
        bessDists[store[0]][store[1]] = storeBessDist, elseDists[store[0]][store[1]] = storeElseDist;
    }
    fclose(in);
    
    //Get solutions for both Bess and Elsie
    solve(bessDists, bessPosses);
    solve(elseDists, elsePosses);
    
    //Output least common solution
    //Output "IMPOSSIBLE" if none
    out = fopen("meeting.out", "w");
    possible = false;
    REPEAT(i, 100*numFields+1) if (bessPosses[numFields-1][i] && elsePosses[numFields-1][i]) {
        fprintf(out, "%hi\n", i);
        possible = true;
        break;
    }
    if (!possible) fprintf(out, "IMPOSSIBLE\n");
    fclose(out);
    
    exit(0);
}