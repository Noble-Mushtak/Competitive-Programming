#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef signed char byte;
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline void POPQUEUE(void *arr, size_t length, size_t itemSize) { memmove(arr, arr+itemSize, length*itemSize); }
static inline void REMOVEELEM(void *arr, size_t offset, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+1)*itemSize), (length-offset)*itemSize); }
static inline void REMOVEELEMS(void *arr, size_t offset, size_t numElems, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+numElems)*itemSize), (length-offset)*itemSize); }

typedef short dimen;
typedef struct {
    dimen x;
    dimen y;
} point;
typedef long num_points;
typedef byte type;
typedef long dist;

FILE *in, *out;
dimen width, length;
type grid[1000][1000];
point up[1000][1000], down[1000][1000], left[1000][1000], right[1000][1000], queue[1000000];
num_points queueLength;
dist distUp[1000][1000], distDown[1000][1000], distLeft[1000][1000], distRight[1000][1000], minDist[1000][1000], answer = -1;
bool smellOn[1000][1000], visited[1000][1000];

void dijkstra(bool favorSmell) {
    num_points l, curIndex;
    point curVertex, curNeighbor;
    bool afterSmell;
    memset(visited, false, sizeof(visited));
    minDist[0][0] = 0, smellOn[0][0] = false, queue[0].x = 0, queue[0].y = 0, queueLength = 1;
    while (queueLength) {
        curVertex = queue[0], curIndex = 0;
        for (l = 1; l < queueLength; l++) if (minDist[curVertex.x][curVertex.y] > minDist[queue[l].x][queue[l].y] || ((favorSmell || minDist[curVertex.x][curVertex.y] == minDist[queue[l].x][queue[l].y]) && smellOn[queue[l].x][queue[l].y] && !smellOn[curVertex.x][curVertex.y])) curVertex = queue[l], curIndex = l;
        queue[curIndex] = queue[--queueLength];
        //printf("%hi %hi %hhi\n", curVertex.x, curVertex.y, smellOn[curVertex.x][curVertex.y]);
        if (curVertex.x+1 == length && curVertex.y+1 == length) {
            if (answer < 0 || minDist[curVertex.x][curVertex.y] < answer) answer = minDist[curVertex.x][curVertex.y];
            break;
        }
        
        if (distUp[curVertex.x][curVertex.y]) {
            curNeighbor = up[curVertex.x][curVertex.y];
            afterSmell = (grid[curNeighbor.x][curNeighbor.y] == 2) || (smellOn[curVertex.x][curVertex.y] && distUp[curVertex.x][curVertex.y] == 1 && grid[curNeighbor.x][curNeighbor.y] != 4);
            if ((smellOn[curVertex.x][curVertex.y] || grid[curNeighbor.x][curNeighbor.y] != 3) && (!visited[curNeighbor.x][curNeighbor.y] || minDist[curVertex.x][curVertex.y]+distUp[curVertex.x][curVertex.y] < minDist[curNeighbor.x][curNeighbor.y] || ((favorSmell || minDist[curVertex.x][curVertex.y]+distUp[curVertex.x][curVertex.y] == minDist[curNeighbor.x][curNeighbor.y]) && afterSmell && !smellOn[curNeighbor.x][curNeighbor.y]))) {
                if (!visited[curNeighbor.x][curNeighbor.y]) {
                    queue[queueLength++] = curNeighbor;
                    visited[curNeighbor.x][curNeighbor.y] = true;
                }
                minDist[curNeighbor.x][curNeighbor.y] = minDist[curVertex.x][curVertex.y]+distUp[curVertex.x][curVertex.y];
                smellOn[curNeighbor.x][curNeighbor.y] = afterSmell;
            }
        }
        if (distLeft[curVertex.x][curVertex.y]) {
            curNeighbor = left[curVertex.x][curVertex.y];
            afterSmell = (grid[curNeighbor.x][curNeighbor.y] == 2) || (smellOn[curVertex.x][curVertex.y] && distLeft[curVertex.x][curVertex.y] == 1 && grid[curNeighbor.x][curNeighbor.y] != 4);
            if ((smellOn[curVertex.x][curVertex.y] || grid[curNeighbor.x][curNeighbor.y] != 3) && (!visited[curNeighbor.x][curNeighbor.y] || minDist[curVertex.x][curVertex.y]+distLeft[curVertex.x][curVertex.y] < minDist[curNeighbor.x][curNeighbor.y] || ((favorSmell || minDist[curVertex.x][curVertex.y]+distLeft[curVertex.x][curVertex.y] == minDist[curNeighbor.x][curNeighbor.y]) && afterSmell && !smellOn[curNeighbor.x][curNeighbor.y]))) {
                if (!visited[curNeighbor.x][curNeighbor.y]) {
                    queue[queueLength++] = curNeighbor;
                    visited[curNeighbor.x][curNeighbor.y] = true;
                }
                minDist[curNeighbor.x][curNeighbor.y] = minDist[curVertex.x][curVertex.y]+distLeft[curVertex.x][curVertex.y];
                smellOn[curNeighbor.x][curNeighbor.y] = afterSmell;
            }
        }
        if (distDown[curVertex.x][curVertex.y]) {
            curNeighbor = down[curVertex.x][curVertex.y];
            afterSmell = (grid[curNeighbor.x][curNeighbor.y] == 2) || (smellOn[curVertex.x][curVertex.y] && distDown[curVertex.x][curVertex.y] == 1 && grid[curNeighbor.x][curNeighbor.y] != 4);
            if ((smellOn[curVertex.x][curVertex.y] || grid[curNeighbor.x][curNeighbor.y] != 3) && (!visited[curNeighbor.x][curNeighbor.y] || minDist[curVertex.x][curVertex.y]+distDown[curVertex.x][curVertex.y] < minDist[curNeighbor.x][curNeighbor.y] || ((favorSmell || minDist[curVertex.x][curVertex.y]+distDown[curVertex.x][curVertex.y] == minDist[curNeighbor.x][curNeighbor.y]) && afterSmell && !smellOn[curNeighbor.x][curNeighbor.y]))) {
                if (!visited[curNeighbor.x][curNeighbor.y]) {
                    queue[queueLength++] = curNeighbor;
                    visited[curNeighbor.x][curNeighbor.y] = true;
                }
                minDist[curNeighbor.x][curNeighbor.y] = minDist[curVertex.x][curVertex.y]+distDown[curVertex.x][curVertex.y];
                smellOn[curNeighbor.x][curNeighbor.y] = afterSmell;
            }
        }
        if (distRight[curVertex.x][curVertex.y]) {
            curNeighbor = right[curVertex.x][curVertex.y];
            afterSmell = (grid[curNeighbor.x][curNeighbor.y] == 2) || (smellOn[curVertex.x][curVertex.y] && distRight[curVertex.x][curVertex.y] == 1 && grid[curNeighbor.x][curNeighbor.y] != 4);
            if ((smellOn[curVertex.x][curVertex.y] || grid[curNeighbor.x][curNeighbor.y] != 3) && (!visited[curNeighbor.x][curNeighbor.y] || minDist[curVertex.x][curVertex.y]+distRight[curVertex.x][curVertex.y] < minDist[curNeighbor.x][curNeighbor.y] || ((favorSmell || minDist[curVertex.x][curVertex.y]+distRight[curVertex.x][curVertex.y] == minDist[curNeighbor.x][curNeighbor.y]) && afterSmell && !smellOn[curNeighbor.x][curNeighbor.y]))) {
                if (!visited[curNeighbor.x][curNeighbor.y]) {
                    queue[queueLength++] = curNeighbor;
                    visited[curNeighbor.x][curNeighbor.y] = true;
                }
                minDist[curNeighbor.x][curNeighbor.y] = minDist[curVertex.x][curVertex.y]+distRight[curVertex.x][curVertex.y];
                smellOn[curNeighbor.x][curNeighbor.y] = afterSmell;
            }
        }
    }
}

int main() {
    char store;
    dimen i, j;
    
    in = fopen("dream.in", "r");
    fscanf(in, "%hi %hi", &width, &length);
    REPEAT(j, width) REPEAT(i, length) fscanf(in, "%hhi", grid[i]+j);
    fclose(in);

    REPEAT(i, length) REPEAT(j, width) if (grid[i][j]) {
        if (!j || !grid[i][j-1]) distUp[i][j] = 0;
        else {
            up[i][j].x = i, up[i][j].y = j-1, distUp[i][j] = 1;
            while (up[i][j].y && grid[up[i][j].x][up[i][j].y] == 4 && grid[up[i][j].x][up[i][j].y-1] && grid[up[i][j].x][up[i][j].y-1] != 3) up[i][j].y--, distUp[i][j]++;
        }
        if (!i || !grid[i-1][j]) distLeft[i][j] = 0;
        else {
            left[i][j].x = i-1, left[i][j].y = j, distLeft[i][j] = 1;
            while (left[i][j].x && grid[left[i][j].x][left[i][j].y] == 4 && grid[left[i][j].x-1][left[i][j].y] && grid[left[i][j].x-1][left[i][j].y] != 3) left[i][j].x--, distLeft[i][j]++;
        }
        if (j+1 == width || !grid[i][j+1]) distDown[i][j] = 0;
        else {
            down[i][j].x = i, down[i][j].y = j+1, distDown[i][j] = 1;
            while (down[i][j].y+1 != width && grid[down[i][j].x][down[i][j].y] == 4 && grid[down[i][j].x][down[i][j].y+1] && grid[down[i][j].x][down[i][j].y+1] != 3) down[i][j].y++, distDown[i][j]++;
        }
        if (i+1 == length || !grid[i+1][j]) distRight[i][j] = 0;
        else {
            right[i][j].x = i+1, right[i][j].y = j, distRight[i][j] = 1;
            while (right[i][j].x+1 != length && grid[right[i][j].x][right[i][j].y] == 4 && grid[right[i][j].x+1][right[i][j].y] && grid[right[i][j].x+1][right[i][j].y] != 3) right[i][j].x++, distRight[i][j]++;
        }
    }

    dijkstra(false);
    //dijkstra(true);
    
    out = fopen("dream.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}