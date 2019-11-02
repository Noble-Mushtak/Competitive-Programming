/*
   PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=380
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
#define GETINDS(ind) queue[ind][0]][queue[ind][1]
#define IFNOELSE(bool) ((bool) &&
#define ENDIFNOELSE )
typedef signed char byte;

typedef long elevation;
typedef long num_cells;
#define INFINITY 1000000001

FILE *in, *out;
elevation distanceFrom[500][500], heights[500][500], maxCost = -1;
num_cells rows, columns, waypoints[250000][2], numWaypoints, queue[2500000][2], queuePos;
bool added[500][500];

int main() {
    elevation store1;
    num_cells i, j, k, min, curX, curY, lower = INFINITY, upper = 0, allowed;
    bool store;
    
    in = fopen("ccski.in", "r");
    fscanf(in, "%hi %hi", &rows, &columns);
    REPEAT(i, rows) REPEAT(j, columns) {
        fscanf(in, "%li", heights[i]+j);
        if (heights[i][j] < lower) lower = heights[i][j];
        if (heights[i][j] > upper) upper = heights[i][j];
    }
    REPEAT(i, rows) REPEAT(j, columns) {
        fscanf(in, "%hhi", &store);
        if (store) {
            SET(waypoints[numWaypoints], i, j);
            numWaypoints++;
        }
    }
    fclose(in);
    
    upper -= lower, lower = 0;
    while (lower < upper) {
        allowed = (lower+upper)/2;
        SET(queue[0], waypoints[0][0],  waypoints[0][1]);
        queuePos = 1;
        REPEAT(j, rows) REPEAT(k, columns) distanceFrom[j][k] = INFINITY;
        memset(added, false, sizeof(added));
        added[GETINDS(0)] = true;
        distanceFrom[GETINDS(0)] = 0;
        while (queuePos) {
            curX = queue[0][0], curY = queue[0][1];
            queuePos--;
            if (queuePos) memmove(queue, queue+1, queuePos*sizeof(queue[0]));
            #define ADDINDS(x, y) ( \
                (store1 = heights[x][y] < heights[curX][curY] ? heights[curX][curY]-heights[x][y] : heights[x][y]-heights[curX][curY]), \
                IFNOELSE (!added[x][y] && store1 <= allowed) ( \
                    SET(queue[queuePos], x, y), \
                    (queuePos++), \
                    (added[x][y] = true) \
                ) ENDIFNOELSE \
            )
            if (curY) ADDINDS(curX, curY-1);
            if (curY+1 < columns) ADDINDS(curX, curY+1);
            if (curX) ADDINDS(curX-1, curY);
            if (curX+1 < rows) ADDINDS(curX+1, curY);
            #undef ADDINDS
        }
        store = true;
        REPEAT(j, numWaypoints) if (!added[waypoints[j][0]][waypoints[j][1]]) {
            store = false;
            break;
        }
        if (store) upper = allowed;
        else lower = allowed+1;
    }
        
    out = fopen("ccski.out", "w");
    fprintf(out, "%li\n", lower);
    fclose(out);
    
    exit(0);
}