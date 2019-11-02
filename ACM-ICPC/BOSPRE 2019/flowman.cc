#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked

typedef int64_t vertex;
typedef int64_t num_vertices;
typedef long double flow;
typedef long double cost;
const long double INF = 1e9;
const long double EPSILON = 1e-8;

struct edge;
struct edge {
    //This the vertex which the edge points to:
    vertex end;
    //Actual flow represents the amount of flow actually going through the edge.
    //Flow capacity represents the maximum amount of flow the edge can handle.
    flow actual, capacity;
    //rev represents the reverse of this edge in the residual graph
    //(i.e. if this edge points from i to j, then rev points from j to i.)
    edge *rev;
    //costRate represents the cost of putting flow across this edge in dollars per gallon
    cost costRate;

    edge () {}
    edge (vertex e, flow a, flow c, cost r) : end(e), actual(a), capacity(c), costRate(r), rev(nullptr) {}
};
typedef int64_t num_edges;

//adjacencyList[i] holds all of the edges which start at vertex i
std::list<edge> adjacencyList[10010];
//Total number of edges and vertices in the graph:
num_edges numEdges;
num_vertices numVertices;
//costsFromStart[i] represents distance from source to vertex i
cost costsFromStart[10010];
//nodePotential[i] represents the node potential of vertex i, which allows us to convert all of the edges to a non-negative weight:
cost nodePotential[10010];
//visited[i] is true if and only if it has been visited so far in the current run of Dijkstra's algorithm
bool visited[10010];

//info(v, e, f) represents a path from the source vertex to the vertex e->end
struct info {
    //curEdge represents the last edge in the path
    edge *curEdge;
    //prevVertex represents the vertex from which curEdge begins
    vertex prevVertex;
    //minFlow represents the minimum capacity across all the edges in this path
    flow minFlow;
    //totalCost represents the sum of the costs of all the edges across this path:
    cost totalCost;

    info () {}
    info (vertex v, edge *e, flow f, cost t) : prevVertex(v), curEdge(e), minFlow(f), totalCost(t) {}
};
//pred[i] represents a path from the source vertex to the vertex i
info pred[10010];

//Finds a path of non-zero flow from start to end, if possible
//At the end, the path is stored in pred[end] and the cost rate of the path is stored in costsFromStart[end]
void findPath(vertex start, vertex end) {
    //If start equals end, then return a path of flow with no edges and infinite flow:
    if (start == end) {
        pred[end] = info(end, nullptr, INF, 0);
        return;
    }

    //Initialize all vertices i with infinite distance from the start vertex and 0 flow from start to i, and mark all vertices as not yet visited:
    vertex i;
    REP(i, numVertices) {
        costsFromStart[i] = INF;
        pred[i] = info(i, nullptr, 0, INF);
        visited[i] = false;
    }

    //Initialize start with a distance of 0 and infinite flow from start to start:
    costsFromStart[start] = 0;
    pred[start] = info(start, nullptr, INF, 0);
    //Run Dijkstra's algorithm:
    while (true) {
        //Find the unvisited vertex with minimum distance from start:
        vertex minVertex = -1;
        REP(i, numVertices) {
            if (!visited[i] && ((minVertex == -1) || (costsFromStart[minVertex] > costsFromStart[i]))) minVertex = i;
        }
        //Exit the loop if there are no more unvisited vertices:
        if (minVertex == -1) break;
        //Otherwise, mark minVertex as visited and loop through all of its edges which point to unvisited vertices:
        visited[minVertex] = true;
        for (auto it = adjacencyList[minVertex].begin(); it != adjacencyList[minVertex].end(); ++it) if (!visited[it->end]) {
            //Here, we are examining an edge from minVertex to the vertex it->end
            //If the distance from start to minVertex plus the costRate of this edge minus the potential difference between minVertex and it->end is less than the distance from start to it->end,
            // AND it is possible to add a non-zero flow to this edge,
            //then update costsFromStart[it->end] and pred[it->end]:
            cost distanceToItEndMinusNodePotential = costsFromStart[minVertex]+it->costRate-(nodePotential[it->end]-nodePotential[minVertex]);
            if ((distanceToItEndMinusNodePotential < costsFromStart[it->end]-EPSILON) && (it->actual < it->capacity-EPSILON)) {
                costsFromStart[it->end] = distanceToItEndMinusNodePotential;
                pred[it->end] = info(minVertex, &(*it), std::min(pred[minVertex].minFlow, it->capacity-it->actual), pred[minVertex].totalCost+it->costRate);
            }
        }
    }
    //At the end, update the node potentials so that Dijkstra's algorithm will still work next time around:
    REP(i, numVertices) nodePotential[i] += std::min(costsFromStart[i], INF);
}

//Finds the maximum amount of flow that can be set from start to end, on a budget of maxCost
flow edmondsKarp(vertex start, vertex end, cost maxCost) {
    //answer is our final answer:
    flow answer = 0;
    //totalCost is the cost of the flow we've sent through the graph so far:
    cost totalCost = 0;
    //Initialize all the edges with 0 flow and initialize all the vertices to 0 potential:
    vertex  i;
    REP(i, numVertices) {
        for (auto it = adjacencyList[i].begin(); it != adjacencyList[i].end(); ++it) it->actual = 0;
        nodePotential[i] = 0;
    }

    //Keep finding paths until we can't add any more flow:
    while (true) {
        findPath(start, end);
        info curInfo = pred[end];

        //The amount of flow we can add is the minimum of the amount of flow that we can still afford to add without going over our budget, and the amount of flow that can be sent through this path without exceeding the capacities of any of the edges along the path:
        flow flowCanBeAdded = std::min((maxCost-totalCost)/curInfo.totalCost, curInfo.minFlow);
        //If the amount of flow we can add is basically 0, then just return the answer:
        if (std::abs(flowCanBeAdded) < EPSILON) return answer;
        //Otherwise, update answer and totalCost:
        answer += flowCanBeAdded;
        totalCost += flowCanBeAdded*curInfo.totalCost;
        
        //Also, traverse through the path and update the flow along all the edges in the path:
        for (edge *curEdge = curInfo.curEdge; curEdge != nullptr; curInfo = pred[curInfo.prevVertex], curEdge = curInfo.curEdge) {
            curEdge->actual += flowCanBeAdded;
            (curEdge->rev)->actual -= flowCanBeAdded;
        }
    }
}

//name stores the test case name, inputLine stores a line read in from the test case:
char name[100000], inputLine[100000];
//numQueries represents the number of queries in the current test case:
typedef int64_t num_queries;
num_queries numQueries;

int main() {
    while (true) {
        //Read in the test case name, and exit if we hit the end of input:
        fgets(name, 100000, stdin);
        if (feof(stdin)) break;
        //Read in the number of vertices, edges, and queries from the first line of input:
        fgets(inputLine, 100000, stdin);
        sscanf(inputLine, "%" PRId64 " %" PRId64 " %" PRId64, &numVertices, &numEdges, &numQueries);

        //Reset the adjacency lists:
        num_edges i;
        num_vertices j;
        REP(j, numVertices) adjacencyList[j].clear();
        //For every edge, read about the info from that edge from the next line of input:
        REP(i, numEdges) {
            fgets(inputLine, 100000, stdin);
            vertex beg, end;
            flow capacity;
            double storeCost;
            int64_t capacityI;
            sscanf(inputLine, "%" PRId64 " %" PRId64 " %" PRId64 " %lf", &beg, &end, &capacityI, &storeCost);
            capacity = capacityI;
            //Convert vertices from 1-based indexing to 0-based indexing:
            beg--, end--;
            //Add the edge and the reverse of the edge (with negative cost) to the appropriate adjacency lists:
            adjacencyList[beg].push_back(edge(end, 0, capacity, storeCost));
            adjacencyList[end].push_back(edge(beg, 0, 0, -storeCost));
            //Update the rev pointers of the edges we just added:
            adjacencyList[beg].rbegin()->rev = &(*adjacencyList[end].rbegin());
            adjacencyList[end].rbegin()->rev = &(*adjacencyList[beg].rbegin());
        }

        //Print out the test case name:
        printf("%s", name);
        //For every query, read in the source vertex, the sink vertex, and the maximum cost from the next input line:
        num_queries l;
        REP(l, numQueries) {
            fgets(inputLine, 100000, stdin);
            vertex beg, end;
            double maxCost;
            sscanf(inputLine, "%" PRId64 " %" PRId64 " %lf", &beg, &end, &maxCost);
            beg--, end--;
            //Finally, output the answer for this test case to 2 decimal places:
            printf("%.2lf\n", static_cast<double>(edmondsKarp(beg, end, maxCost)));
        }
    }
    exit(0);
}
