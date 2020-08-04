#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; ++token)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t test_cases;
typedef int64_t num_costumes;
typedef int64_t costume;
typedef std::pair<num_costumes, num_costumes> loc;
typedef num_costumes num_vertices;
typedef num_costumes vertex;
typedef num_costumes flow;

num_costumes sideLength;
test_cases numTestCases;

struct edge;
typedef std::list<edge>::iterator edge_ptr;
typedef std::pair<bool, edge_ptr> opt_edge_ptr;
struct edge {
    vertex end;
    flow actual, capacity;
    opt_edge_ptr rev;
    opt_edge_ptr pred;
    
    edge() {}
    edge(vertex e, flow a, flow c) : end(e), actual(a), capacity(c) {
        rev.first = false;
        pred.first = false;
    }
};

struct info {
    vertex curVertex;
    opt_edge_ptr curEdge;
    flow minFlow;
    
    info() {}
    info(vertex v, opt_edge_ptr e, flow f) : curVertex(v), curEdge(e), minFlow(f) {}
};

std::vector<loc> locLists[400], *correspondingLocs;
std::list<edge> adjacencyLists[400];
bool visited[400];

info findPath(vertex start, vertex end) {
    if (start == end) return info(end, opt_edge_ptr(false, edge_ptr()), 1000000000);
    
    std::queue<info> queue;
    
    num_vertices i;
    REP(i, 2*sideLength+2) {
        for (auto it = adjacencyLists[i].begin(); it != adjacencyLists[i].end(); ++it) it->pred = opt_edge_ptr(false, edge_ptr());
        visited[i] = false;
    }
    
    queue.push(info(start, opt_edge_ptr(false, edge_ptr()), 1000000000));
    visited[start] = true;
    
    while (!queue.empty()) {
        info curInfo = queue.front();
        queue.pop();
        vertex curVertex = curInfo.curVertex;
        for (auto it = adjacencyLists[curVertex].begin();
             it != adjacencyLists[curVertex].end();
             ++it) {
            if (!visited[it->end] && (it->actual < it->capacity)) {
                PRINTF("C: " INT64 " " INT64 "\n", it->actual, it->capacity);
                it->pred = curInfo.curEdge;
                info newInfo = info(
                    it->end,
                    opt_edge_ptr(true, it),
                    std::min(curInfo.minFlow, it->capacity-it->actual)
                );
                if (newInfo.curVertex == end) return newInfo;
                
                queue.push(newInfo);
                visited[newInfo.curVertex] = true;
            }
        }
    }
    return info(end, opt_edge_ptr(false, edge_ptr()), 0);
}

flow edmondsKarp() {
    flow answer = 0;
    while (true) {
        info curInfo = findPath(0, 2*sideLength+1);
        PRINTF("B: " INT64 " " INT64 "\n", answer, curInfo.minFlow);
        if (curInfo.minFlow == 0) return answer;
        
        answer += curInfo.minFlow;
        for (opt_edge_ptr curEdge = curInfo.curEdge;
             curEdge.first;
             curEdge = (curEdge.second)->pred) {
            (curEdge.second)->actual += curInfo.minFlow;
            ((curEdge.second)->rev).second->actual -= curInfo.minFlow;
        }
    }
}

void addEdge(vertex start, vertex end) {
    adjacencyLists[start].push_back(edge(end, 0, 1));
    adjacencyLists[end].push_back(edge(start, 0, 0));
    edge_ptr newEdgePtr = std::prev(adjacencyLists[start].end());
    edge_ptr newRevEdgePtr = std::prev(adjacencyLists[end].end());
    newEdgePtr->rev = opt_edge_ptr(true, newRevEdgePtr);
    newRevEdgePtr->rev = opt_edge_ptr(true, newEdgePtr);
}

num_costumes maximumMatching(std::vector<loc> &locs) {
    num_vertices i;
    REP(i, 2*sideLength+2) adjacencyLists[i].clear();
    
    REP(i, sideLength) addEdge(0, i+1), addEdge(i+sideLength+1, 2*sideLength+1);
    for (auto it = locs.begin(); it != locs.end(); ++it) addEdge(it->first+1, it->second+sideLength+1);
    return edmondsKarp();
}

int main() {
    test_cases l;
    correspondingLocs = locLists+200;
    
    scanf(INT64, &numTestCases);
    REP(l, numTestCases) {
        scanf(INT64, &sideLength);
        num_costumes i, j;
        REP(i, sideLength) {
            correspondingLocs[i+1].clear();
            correspondingLocs[-(i+1)].clear();
        }
        REP(i, sideLength) REP(j, sideLength) {
            costume storeCostume;
            scanf(INT64, &storeCostume);
            correspondingLocs[storeCostume].push_back(loc(i, j));
        }

        costume c;
        num_costumes answer = 0;
        for (c = -sideLength; c <= sideLength; ++c) {
            if (c == 0) continue;
            num_costumes maximumMatches = maximumMatching(correspondingLocs[c]);
            answer += correspondingLocs[c].size()-maximumMatches;
            PRINTF("A: " INT64 " " INT64 " " INT64 "\n", c, answer, maximumMatches);
        }
        printf("Case #" INT64 ": " INT64 "\n", l+1, answer);
    }
    
    return 0;
}