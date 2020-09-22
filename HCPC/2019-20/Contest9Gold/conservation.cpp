#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t test_cases;
typedef int64_t vertex;
typedef int64_t num_vertices;
typedef int64_t num_edges;
struct edge {
    vertex dest;
    std::list<edge>::iterator rev;
};

num_vertices numVertices;
num_edges numEdges;
std::queue<vertex> childlessFirst, childlessSecond;
std::pair<vertex, vertex> edges[3000000];
std::list<edge> parents[3000000], children[3000000], parentsTemp[3000000], childrenTemp[3000000];
bool firstLaboratory[3000000];

void addToQueue(vertex i) {
    if (firstLaboratory[i]) childlessFirst.push(i);
    else childlessSecond.push(i);
}

void initParents() {
    num_vertices i;
    REP(i, numVertices) {
        parents[i].clear();
        children[i].clear();
    }
    num_edges l;
    REP(l, numEdges) {
        vertex beg, end;
        beg = edges[l].first, end = edges[l].second;
        edge parentOfEnd, childOfBeg;
        parentOfEnd.dest = beg;
        childOfBeg.dest = end;
        parents[end].push_back(parentOfEnd);
        children[beg].push_back(childOfBeg);
        auto parentIt = std::prev(parents[end].end());
        auto childIt = std::prev(children[beg].end());
        parentIt->rev = childIt;
        childIt->rev = parentIt;
    }
}

num_vertices countSwitches(bool startAtFirst) {
    std::queue<vertex> empty;
    std::swap(childlessFirst, empty);
    std::swap(childlessSecond, empty);

    initParents();
    num_vertices i;
    REP(i, numVertices) {
        if (parents[i].empty()) addToQueue(i);
    }
    
    bool currentlyUsingFirst = startAtFirst;
    num_vertices numSwitches = 0, numProcessed = 0;
    while ((childlessFirst.size() != 0) || (childlessSecond.size() != 0)) {
        //printf("R " INT64 " " INT64 "\n", childlessFirst.size(), childlessSecond.size());
        vertex toBeProcessed;
        if (currentlyUsingFirst) {
            if (childlessFirst.empty()) {
                numSwitches++;
                currentlyUsingFirst = !currentlyUsingFirst;
                toBeProcessed = childlessSecond.front();
                childlessSecond.pop();
                //printf("A " INT64 "\n", toBeProcessed);
            } else {
                toBeProcessed = childlessFirst.front();
                childlessFirst.pop();
                //printf("B " INT64 "\n", toBeProcessed);
            }
        } else {
            if (childlessSecond.empty()) {
                numSwitches++;
                currentlyUsingFirst = !currentlyUsingFirst;
                toBeProcessed = childlessFirst.front();
                childlessFirst.pop();
                //printf("C " INT64 "\n", toBeProcessed);
            } else {
                toBeProcessed = childlessSecond.front();
                childlessSecond.pop();
                //printf("D " INT64 "\n", toBeProcessed);
            }
        }
        for (auto it = children[toBeProcessed].begin(); it != children[toBeProcessed].end(); ++it) {
            vertex childVertex = it->dest;
            auto parentIt = it->rev;
            parents[childVertex].erase(parentIt);
            //printf(INT64 " " INT64 "\n", toBeProcessed, childVertex);
            if (parents[childVertex].size() == 0) addToQueue(childVertex)/*, printf("N " INT64 "\n", childVertex)*/;
        }
        numProcessed += 1;
    }
    if (numProcessed != numVertices) printf("CRITICAL ERROR: " INT64 " " INT64 "\n", numProcessed, numVertices), exit(1);
    return numSwitches;
}

int main() {
    int64_t numTestCases;
    scanf(INT64, &numTestCases);
    while (numTestCases--) {
        scanf(INT64 " " INT64, &numVertices, &numEdges);
        num_vertices i;
        REP(i, numVertices) {
            int64_t labNum;
            scanf(INT64, &labNum);
            firstLaboratory[i] = (labNum == 1);
        }
        
        num_edges l;
        REP(l, numEdges) {
            vertex beg, end;
            scanf(INT64 " " INT64, &beg, &end);
            beg--, end--;
            edges[l] = std::pair<vertex, vertex>(beg, end);
        }
        
        num_vertices answer = std::min(countSwitches(false), countSwitches(true));
        printf(INT64 "\n", answer);
    }
    
    return 0;
}