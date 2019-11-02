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
point up[1000][1000], down[1000][1000], left[1000][1000], right[1000][1000], heap[1000000];
num_points heapLength;
dist distUp[1000][1000], distDown[1000][1000], distLeft[1000][1000], distRight[1000][1000], minDist[1000][1000], answer = -1;
bool smellOn[1000][1000], visited[1000][1000];

void dijkstra(bool favorSmell) {
    num_points l, curIndex, childIndex;
    point curVertex, curNeighbor, temp;
    bool afterSmell;
    memset(visited, false, sizeof(visited));
    minDist[0][0] = 0, smellOn[0][0] = false, heap[0].x = 0, heap[0].y = 0, heapLength = 1;
    while (heapLength) {
        curVertex = heap[0];
        if (heapLength > 1) {
            heap[0] = heap[--heapLength], curIndex = 0;
            while (2*curIndex+1 < heapLength) {
                if (2*curIndex+2 < heapLength && minDist[heap[2*curIndex+1].x][heap[2*curIndex+1].y] > minDist[heap[2*curIndex+2].x][heap[2*curIndex+2].y] || ((favorSmell || minDist[heap[2*curIndex+1].x][heap[2*curIndex+1].y] == minDist[heap[2*curIndex+2].x][heap[2*curIndex+2].y]) && smellOn[heap[2*curIndex+2].x][heap[2*curIndex+2].y] && !smellOn[heap[2*curIndex+1].x][heap[2*curIndex+1].y])) childIndex = 2*curIndex+2;
                else childIndex = 2*curIndex+1;
                if (minDist[heap[curIndex].x][heap[curIndex].y] > minDist[heap[childIndex].x][heap[childIndex].y] || ((favorSmell || minDist[heap[curIndex].x][heap[curIndex].y] == minDist[heap[childIndex].x][heap[childIndex].y]) && smellOn[heap[childIndex].x][heap[childIndex].y] && !smellOn[heap[curIndex].x][heap[curIndex].y])) temp = heap[curIndex], heap[curIndex] = heap[childIndex], heap[childIndex] = temp, curIndex = childIndex;
                else break;
            }
        } else heapLength = 0;
        //printf("%hi %hi %hhi\n", curVertex.x, curVertex.y, smellOn[curVertex.x][curVertex.y]);
        if (curVertex.x+1 == length && curVertex.y+1 == length) {
            if (answer < 0 || minDist[curVertex.x][curVertex.y] < answer) answer = minDist[curVertex.x][curVertex.y];
            break;
        }
        
        if (distUp[curVertex.x][curVertex.y]) {
            curNeighbor = up[curVertex.x][curVertex.y];
            afterSmell = (smellOn[curVertex.x][curVertex.y] && distUp[curVertex.x][curVertex.y] == 1 && grid[curNeighbor.x][curNeighbor.y] != 4);
            if ((smellOn[curVertex.x][curVertex.y] || grid[curNeighbor.x][curNeighbor.y] != 3) && (!visited[curNeighbor.x][curNeighbor.y] || minDist[curVertex.x][curVertex.y]+distUp[curVertex.x][curVertex.y] < minDist[curNeighbor.x][curNeighbor.y] || ((favorSmell || minDist[curVertex.x][curVertex.y]+distUp[curVertex.x][curVertex.y] == minDist[curNeighbor.x][curNeighbor.y]) && afterSmell && !smellOn[curNeighbor.x][curNeighbor.y]))) {
                if (!visited[curNeighbor.x][curNeighbor.y]) {
                    heap[heapLength++] = curNeighbor, curIndex = heapLength-1;
                    while (curIndex) {
                        if (minDist[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y] > minDist[heap[curIndex].x][heap[curIndex].y] || ((favorSmell || minDist[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y] == minDist[heap[curIndex].x][heap[curIndex].y]) && smellOn[heap[curIndex].x][heap[curIndex].y] && !smellOn[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y])) temp = heap[(curIndex-1)/2], heap[(curIndex-1)/2] = heap[curIndex], heap[curIndex] = temp, curIndex = (curIndex-1)/2;
                        else break;
                    }
                    visited[curNeighbor.x][curNeighbor.y] = true;
                }
                minDist[curNeighbor.x][curNeighbor.y] = minDist[curVertex.x][curVertex.y]+distUp[curVertex.x][curVertex.y];
                smellOn[curNeighbor.x][curNeighbor.y] = afterSmell;
            }
        }
        if (distLeft[curVertex.x][curVertex.y]) {
            curNeighbor = left[curVertex.x][curVertex.y];
            afterSmell = (smellOn[curVertex.x][curVertex.y] && distLeft[curVertex.x][curVertex.y] == 1 && grid[curNeighbor.x][curNeighbor.y] != 4);
            if ((smellOn[curVertex.x][curVertex.y] || grid[curNeighbor.x][curNeighbor.y] != 3) && (!visited[curNeighbor.x][curNeighbor.y] || minDist[curVertex.x][curVertex.y]+distLeft[curVertex.x][curVertex.y] < minDist[curNeighbor.x][curNeighbor.y] || ((favorSmell || minDist[curVertex.x][curVertex.y]+distLeft[curVertex.x][curVertex.y] == minDist[curNeighbor.x][curNeighbor.y]) && afterSmell && !smellOn[curNeighbor.x][curNeighbor.y]))) {
                if (!visited[curNeighbor.x][curNeighbor.y]) {
                    heap[heapLength++] = curNeighbor, curIndex = heapLength-1;
                    while (curIndex) {
                        if (minDist[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y] > minDist[heap[curIndex].x][heap[curIndex].y] || ((favorSmell || minDist[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y] == minDist[heap[curIndex].x][heap[curIndex].y]) && smellOn[heap[curIndex].x][heap[curIndex].y] && !smellOn[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y])) temp = heap[(curIndex-1)/2], heap[(curIndex-1)/2] = heap[curIndex], heap[curIndex] = temp, curIndex = (curIndex-1)/2;
                        else break;
                    }
                    visited[curNeighbor.x][curNeighbor.y] = true;
                }
                minDist[curNeighbor.x][curNeighbor.y] = minDist[curVertex.x][curVertex.y]+distLeft[curVertex.x][curVertex.y];
                smellOn[curNeighbor.x][curNeighbor.y] = afterSmell;
            }
        }
        if (distDown[curVertex.x][curVertex.y]) {
            curNeighbor = down[curVertex.x][curVertex.y];
            afterSmell = (smellOn[curVertex.x][curVertex.y] && distDown[curVertex.x][curVertex.y] == 1 && grid[curNeighbor.x][curNeighbor.y] != 4);
            if ((smellOn[curVertex.x][curVertex.y] || grid[curNeighbor.x][curNeighbor.y] != 3) && (!visited[curNeighbor.x][curNeighbor.y] || minDist[curVertex.x][curVertex.y]+distDown[curVertex.x][curVertex.y] < minDist[curNeighbor.x][curNeighbor.y] || ((favorSmell || minDist[curVertex.x][curVertex.y]+distDown[curVertex.x][curVertex.y] == minDist[curNeighbor.x][curNeighbor.y]) && afterSmell && !smellOn[curNeighbor.x][curNeighbor.y]))) {
                if (!visited[curNeighbor.x][curNeighbor.y]) {
                    heap[heapLength++] = curNeighbor, curIndex = heapLength-1;
                    while (curIndex) {
                        if (minDist[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y] > minDist[heap[curIndex].x][heap[curIndex].y] || ((favorSmell || minDist[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y] == minDist[heap[curIndex].x][heap[curIndex].y]) && smellOn[heap[curIndex].x][heap[curIndex].y] && !smellOn[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y])) temp = heap[(curIndex-1)/2], heap[(curIndex-1)/2] = heap[curIndex], heap[curIndex] = temp, curIndex = (curIndex-1)/2;
                        else break;
                    }
                    visited[curNeighbor.x][curNeighbor.y] = true;
                }
                minDist[curNeighbor.x][curNeighbor.y] = minDist[curVertex.x][curVertex.y]+distDown[curVertex.x][curVertex.y];
                smellOn[curNeighbor.x][curNeighbor.y] = afterSmell;
            }
        }
        if (distRight[curVertex.x][curVertex.y]) {
            curNeighbor = right[curVertex.x][curVertex.y];
            afterSmell = (smellOn[curVertex.x][curVertex.y] && distRight[curVertex.x][curVertex.y] == 1 && grid[curNeighbor.x][curNeighbor.y] != 4);
            if ((smellOn[curVertex.x][curVertex.y] || grid[curNeighbor.x][curNeighbor.y] != 3) && (!visited[curNeighbor.x][curNeighbor.y] || minDist[curVertex.x][curVertex.y]+distRight[curVertex.x][curVertex.y] < minDist[curNeighbor.x][curNeighbor.y] || ((favorSmell || minDist[curVertex.x][curVertex.y]+distRight[curVertex.x][curVertex.y] == minDist[curNeighbor.x][curNeighbor.y]) && afterSmell && !smellOn[curNeighbor.x][curNeighbor.y]))) {
                if (!visited[curNeighbor.x][curNeighbor.y]) {
                    heap[heapLength++] = curNeighbor, curIndex = heapLength-1;
                    while (curIndex) {
                        if (minDist[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y] > minDist[heap[curIndex].x][heap[curIndex].y] || ((favorSmell || minDist[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y] == minDist[heap[curIndex].x][heap[curIndex].y]) && smellOn[heap[curIndex].x][heap[curIndex].y] && !smellOn[heap[(curIndex-1)/2].x][heap[(curIndex-1)/2].y])) temp = heap[(curIndex-1)/2], heap[(curIndex-1)/2] = heap[curIndex], heap[curIndex] = temp, curIndex = (curIndex-1)/2;
                        else break;
                    }
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