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
#define printf(...) 1

typedef long long dimen;
typedef struct {
    dimen x, y;
} point;
typedef long long num_points;
typedef long long num_edges;
typedef struct {
    int isX;
    num_edges start;
    dimen length;
} edge;

typedef num_points item_type;
typedef struct {item_type parent[1000000];} dsu;
static inline void initialize(dsu *data, item_type x) {data->parent[x] = x;}
static inline item_type findRoot(dsu *data, item_type x) {return (x == data->parent[x]) ? x : findRoot(data, data->parent[x]);}
static inline bool unionItems(dsu *data, item_type x, item_type y) {
    item_type rootX = findRoot(data, x), rootY = findRoot(data, y);
    data->parent[rootX] = rootY;
    return (rootX != rootY);
}

FILE *in, *out;
num_edges numXWalls, numYWalls;
dimen answer = 0, maxX, maxY, xWalls[25001], yWalls[25001];
edge edgeGroups[50000];
dsu dataStructure;

int main() {
    char store;
    num_edges i, j;
    bool pass;
    
    in = fopen("fencedin.in", "r");
    fscanf(in, "%lli %lli %lli %lli", &maxX, &maxY, &numXWalls, &numYWalls);
    REPEAT(i, numXWalls) fscanf(in, "%lli", xWalls+(i+1));
    REPEAT(j, numYWalls) fscanf(in, "%lli", yWalls+(j+1));
    fclose(in);

    inline int compareDimens(const void *ptr1, const void *ptr2) {
        dimen dimen1 = *(dimen*)ptr1, dimen2 = *(dimen*)ptr2;
        return (dimen1 > dimen2)-(dimen1 < dimen2);
    }
    qsort(xWalls+1, numXWalls, sizeof(dimen), compareDimens), qsort(yWalls+1, numYWalls, sizeof(dimen), compareDimens);
    xWalls[0] = yWalls[0] = 0, xWalls[numXWalls+1] = maxX, yWalls[numYWalls+1] = maxY;
    
    REPEAT(i, numXWalls+1) edgeGroups[i].isX = true, edgeGroups[i].start = i, edgeGroups[i].length = xWalls[i+1]-xWalls[i];
    REPEAT(j, numYWalls+1) edgeGroups[j+numXWalls+1].isX = false, edgeGroups[j+numXWalls+1].start = j, edgeGroups[j+numXWalls+1].length = yWalls[j+1]-yWalls[j];
    inline int compareEdges(const void *ptr1, const void *ptr2) {
        edge edge1 = *(edge*)ptr1, edge2 = *(edge*)ptr2;
        return (edge1.length > edge2.length)-(edge1.length < edge2.length);
    }
    qsort(edgeGroups, numXWalls+numYWalls+2, sizeof(edge), compareEdges);

    REPEAT(i, numXWalls+1) REPEAT(j, numYWalls+1) initialize(&dataStructure, j*(numXWalls+1)+i);
    REPEAT(i, numXWalls+numYWalls+2) {
        if (edgeGroups[i].isX) { REPEAT(j, numYWalls) if (unionItems(&dataStructure, j*(numXWalls+1)+edgeGroups[i].start, (j+1)*(numXWalls+1)+edgeGroups[i].start)) answer += edgeGroups[i].length, printf("X %lli %lli %lli | %lli %lli\n", j, edgeGroups[i].start, edgeGroups[i].length, j*(numXWalls+1)+edgeGroups[i].start, (j+1)*(numXWalls+1)+edgeGroups[i].start); }
        else REPEAT(j, numXWalls) if (unionItems(&dataStructure, edgeGroups[i].start*(numXWalls+1)+j, edgeGroups[i].start*(numXWalls+1)+j+1)) answer += edgeGroups[i].length, printf("Y %lli %lli %lli | %lli %lli\n", j, edgeGroups[i].start, edgeGroups[i].length, edgeGroups[i].start*(numXWalls+1)+j, edgeGroups[i].start*(numXWalls+1)+j+1);
    }
    
    out = fopen("fencedin.out", "w");
    fprintf(out, "%lli\n", answer);
    fclose(out);
    
    exit(0);
}