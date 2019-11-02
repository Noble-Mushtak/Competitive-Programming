//Received Time Limit Exceeded verdict

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <list>
#include <queue>

#define REP(token, num) for (token = 0; token < num; token++)

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int32_t vertex;
typedef int32_t num_vertices;
typedef int32_t flow;
struct edge;
struct edge {
    vertex end;
    flow actual, capacity;
    edge *rev;
    edge *pred;

    edge() {}
    edge(vertex e, flow a, flow c) : end(e), actual(a), capacity(c), rev(nullptr), pred(nullptr) {}
};
typedef int32_t num_edges;

std::list<edge> adjacencyList[10010], oldAdjacencyList[10010];
num_edges numEdges;
num_vertices numVertices;
bool visited[10010];
flow answer1, answer2;

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
    if (start == end) return info(end, nullptr, 1000000000);

    std::queue<info> queue;

    //Traverse through all the edges in the graph and clear the predecessor property of each edge:
    num_vertices i;
    REP(i, numVertices) {
        for (auto it = adjacencyList[i].begin(); it != adjacencyList[i].end(); it++) it->pred = nullptr;
    }
    //No verticies have been visited yet, so clear visited array:
    memset(visited, false, sizeof(visited));

    //Start off from the start node with infinite flow:
    queue.push(info(start, nullptr, 1000000000));
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

flow edmondsKarp(flow limit = 1000000000) {
    flow answer = 0;
    //Keep trying to find a path from start to end as long as you can:
    while (answer < limit) {
        info curInfo = findPath(0, numVertices-1);
        if (curInfo.minFlow == 0) return answer;
        //When a path is found, update answer and then update the actual flow through each edge and reverse edge along the path:
        answer += curInfo.minFlow;
        for (edge *curEdge = curInfo.curEdge; curEdge != nullptr; curEdge = curEdge->pred) {
            //printf("%" PRId32 " %" PRId32 "\n", curEdge->end, curInfo.minFlow);
            curEdge->actual += curInfo.minFlow;
            (curEdge->rev)->actual -= curInfo.minFlow;
        }
        //puts("");
    }
}

void decrementFlow(info curInfo) {
    //To decrement the flow by 1, just decrement the actual flow through each edge along with path (also, increment flow of reverse edge):
    for (edge *curEdge = curInfo.curEdge; curEdge != nullptr; curEdge = curEdge->pred) {
        //printf("%" PRId32 " %" PRId32 "\n", curEdge->end, curInfo.minFlow);
        curEdge->actual--;
        (curEdge->rev)->actual++;
    }
    //puts("");
}

char name[10000], inputLine[10000];

int main() {
    num_vertices i, j;
    vertex beg, end;
    flow edgeCapacity;
    edge edge1, edge2;

    while (true) {
        fgets(name, 10000, stdin);
        if (feof(stdin)) break;
        fgets(inputLine, 10000, stdin);
        sscanf(inputLine, "%" PRId32 " %" PRId32, &numVertices, &numEdges);
        REP(i, numVertices) adjacencyList[i].clear();
        
        //Read in all the edges:
        REP(i, numEdges) {
            fgets(inputLine, 10000, stdin);
            sscanf(inputLine, "%" PRId32 " %" PRId32 " %" PRId32, &beg, &end, &edgeCapacity);
            //Decrement vertices so that it is 0-based instead of 1-based indexing:
            beg--, end--;

            //Add the edge and reverse edge to the appropriate lists:
            adjacencyList[beg].push_back(edge(end, 0, edgeCapacity));
            adjacencyList[end].push_back(edge(beg, 0, edgeCapacity));
            //Set rev properties of edge:
            adjacencyList[beg].rbegin()->rev = &(*(adjacencyList[end].rbegin()));
            adjacencyList[end].rbegin()->rev = &(*(adjacencyList[beg].rbegin()));
        }

        //Just run Edmonds-Karp to find the first answer:
        answer1 = edmondsKarp();
        //Copy the adjacency list so we have it stored for later:
        REP(i, numVertices) oldAdjacencyList[i] = adjacencyList[i];
        
        answer2 = answer1;
        REP(i, numVertices) {
            PRINTF("%" PRId32 "\n", i);
            //Loop through each edge which has positive flow through them:
            for (auto it = adjacencyList[i].begin(); it != adjacencyList[i].end(); it++) if (it->actual > 0) {
                //Decrement the capacity of each edge down to their actual flow:
                flow storeCapacity = it->capacity;
                it->capacity = it->actual;

                //tempAnswer represents maximum flow without this edge:
                flow tempAnswer = answer1;
                //While this edge still has flow running through it:
                while (it->capacity > 0) {
                    //Decrement the flow along a path from 0 to the beginning vertex of this edge:
                    info storeInfo = findPath(0, i, true);
                    if (storeInfo.minFlow == 0) printf("No flow from 0 to %" PRId32 " (%" PRId32 ")\n", i, it->end), exit(1);
                    decrementFlow(storeInfo);
                    //Decrement the flow along a path from the end vertex of this edge to numVertices-1:
                    storeInfo = findPath(it->end, numVertices-1, true);
                    if (storeInfo.minFlow == 0) printf("No flow from %" PRId32 " to end (%" PRId32 ")\n", it->end, i), exit(1);
                    decrementFlow(storeInfo);

                    //Decrement the flow running through this edge:
                    it->capacity--, it->actual--;
                    (it->rev)->actual++;
                    tempAnswer--;
                    //If the flow can be re-routed through a different edge, edmondsKarp() will be able to re-route it:
                    //Notice that restoreFlow is either 0 (failed to re-route flow) or 1 (re-routed flow successfully).
                    //It can't be greater than 1 since we've only decremented the flow running through the edge by 1.
                    flow restoreFlow = edmondsKarp(1);
                    if (restoreFlow > 1) printf("More flow than expected\n"), exit(1);
                    //Update tempAnswer with the re-routed flow:
                    tempAnswer += restoreFlow;
                }
                //Update answer2 with the maximum flow without this edge:
                answer2 = std::min(answer2, tempAnswer);

                //Finally, restore the old adjacency lists:
                REP(j, numVertices) adjacencyList[j] = oldAdjacencyList[j];
            }
        }
        //Debug code to check the flow values resulting from Edmond-Karp
        /* REP(i, numVertices) {
            for (auto it = adjacencyList[i].begin(); it != adjacencyList[i].end(); it++) printf("%" PRId32 " | %" PRId32 " %" PRId32 " %" PRId32 " | %" PRId32 " %" PRId32 "\n", i, it->end, it->actual, it->capacity, (it->rev)->end == i, (it->rev)->actual == -it->actual);
        } // */

        //Print out the answers:
        printf("%s", name);
        printf("%" PRId32 " %" PRId32 "\n", answer1, answer2);
    }
    
    exit(0);
}