#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <list>
#include <queue>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t vertex;
typedef int64_t num_vertices;
typedef int64_t flow;
struct edge;
struct edge {
    vertex end;
    flow actual, capacity;
    edge *rev;
    edge *pred;

    edge() {}
    edge(vertex e, flow a, flow c) : end(e), actual(a), capacity(c), rev(nullptr), pred(nullptr) {}
};
typedef int64_t num;
typedef int64_t num_edges;

num gcd(num num1, num num2) {
    num remainder = num1, lastRemainder = num2, lastLastRemainder;
    while (remainder) {
        lastLastRemainder = lastRemainder, lastRemainder = remainder;
        remainder = lastLastRemainder % lastRemainder;
    }
    return lastRemainder;
}

std::list<edge> adjacencyList[10010];
num_vertices numVertices;
bool visited[10010];
flow vertexValues[10010];

//This struct is used in findPath() in order to keep track of the flow path we are currently traversing in the graph:
struct info {
    vertex curVertex;
    edge *curEdge;
    flow minFlow;
    
    info() {}
    info(vertex v, edge *e, flow f) : curVertex(v), curEdge(e), minFlow(f) {}
};
//If withFlow is false, this function finds a path from start to end such that the actual flow of each edge in the path is less than capacity.
//If withFlow is true, this function finds a path from start to end such that the actual flow of each edge is positive.
info findPath(vertex start, vertex end, bool withFlow = false) {
    //If start == end, then just return empty path, infinite flow:
    if (start == end) return info(end, nullptr, 3000000000LL);

    std::queue<info> queue;

    //Traverse through all the edges in the graph and clear the predecessor property of each edge:
    num_vertices i;
    REP(i, numVertices) {
        for (auto it = adjacencyList[i].begin(); it != adjacencyList[i].end(); it++) it->pred = nullptr;
    }
    //No verticies have been visited yet, so clear visited array:
    memset(visited, false, sizeof(visited));

    //Start off from the start node with infinite flow:
    queue.push(info(start, nullptr, 3000000000LL));
    //start has been visited:
    visited[start] = true;

    //Keep looping while there are still info objects to be processed:
    while (!queue.empty()) {
        //Get the current object which needs to be processed:
        info curInfo = queue.front();
        queue.pop();
        //Loop through all the neighbors of the current vertex:
        for (auto it = adjacencyList[curInfo.curVertex].begin(); it != adjacencyList[curInfo.curVertex].end(); it++) {
            //If withFlow is false: If this neighbor hasn't been visited yet and this edge is not at capacity flow, then...
            //If withFlow is true: If this neighbor hasn't been visited yet and this edge has positive actual flow, then...
            if (!visited[it->end] && (withFlow ? (it->actual > 0) : (it->actual < it->capacity))) {
                //The predecessor of this new edge is the current edge:
                it->pred = curInfo.curEdge;
                //Create an info object with the new vertex, the new edge, and the new flow.
                //If withFlow is false: New flow is difference between capacity and actual flow
                //If withFlow is true: New flow is actual flow through edge
                info newInfo = info(it->end, &(*it), std::min(curInfo.minFlow, withFlow ? it->actual : (it->capacity-it->actual)));
                //If this is the end vertex, return:
                if (newInfo.curVertex == end) {
                    return newInfo;
                }
                //Otherwise, add info object to queue and set visited flag:
                queue.push(newInfo);
                visited[newInfo.curVertex] = true;
            }
        }
    }
    //If we never find a path to end, return empty path with 0 flow:
    return info(end, nullptr, 0);
}

flow edmondsKarp() {
    flow answer = 0;
    //Keep trying to find a path from start to end as long as you can:
    while (true) {
        info curInfo = findPath(0, numVertices-1);
        if (curInfo.minFlow == 0) return answer;
        //When a path is found, update answer and then update the actual flow through each edge and reverse edge along the path:
        answer += curInfo.minFlow;
        for (edge *curEdge = curInfo.curEdge; curEdge != nullptr; curEdge = curEdge->pred) {
            //printf("%" PRId64 " %" PRId64 "\n", curEdge->end, curInfo.minFlow);
            curEdge->actual += curInfo.minFlow;
            (curEdge->rev)->actual -= curInfo.minFlow;
        }
        //puts("");
    }
}

int main() {
    num_vertices i, j;
    scanf("%" PRId64, &numVertices);

    num_vertices indexOfMin = 0, indexOfMax = 0;
    REP(i, numVertices) {
        scanf("%" PRId64, vertexValues+i);
        if (vertexValues[i] < vertexValues[indexOfMin]) indexOfMin = i;
        if (vertexValues[i] > vertexValues[indexOfMax]) indexOfMax = i;
    }
    flow temp;
    temp = vertexValues[0], vertexValues[0] = vertexValues[indexOfMin], vertexValues[indexOfMin] = temp;
    temp = vertexValues[numVertices-1], vertexValues[numVertices-1] = vertexValues[indexOfMax], vertexValues[indexOfMax] = temp;
    
    REP(i, numVertices) REP(j, i) if (gcd(vertexValues[i], vertexValues[j]) > 1) {
        vertex beg = i, end = j;
        flow edgeCapacity = gcd(vertexValues[i], vertexValues[j]);
        //Add the edge and reverse edge to the appropriate lists:
        adjacencyList[beg].push_back(edge(end, 0, edgeCapacity));
        adjacencyList[end].push_back(edge(beg, 0, edgeCapacity));
        //Set rev properties of edge:
        adjacencyList[beg].rbegin()->rev = &(*(adjacencyList[end].rbegin()));
        adjacencyList[end].rbegin()->rev = &(*(adjacencyList[beg].rbegin()));
    }
    printf("%" PRId64 "\n", edmondsKarp());
    
    return 0;
}