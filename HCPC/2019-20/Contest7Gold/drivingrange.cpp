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

namespace dsu {
    typedef int64_t item;
    typedef int64_t item_rank;
    typedef int64_t num_items;
    
    struct dsu_info {
        item parent;
        item_rank rank;
    };
    
    struct dsu {
        const static num_items MAX_ITEMS = 1000010;
        dsu_info allInfo[MAX_ITEMS];

        dsu() {}
        dsu(num_items numItems) {
            item x;
            REP(x, numItems) initialize(x);
        }

        void initialize(item x) {
            allInfo[x].parent = x;
            allInfo[x].rank = 0;
        }
        
        item find(item x) {
            if (allInfo[x].parent != x) allInfo[x].parent = find(allInfo[x].parent);
            return allInfo[x].parent;
        }

        void join(item x, item y) {
            item xRoot = find(x), yRoot = find(y);
            if (xRoot == yRoot) return;

            if (allInfo[xRoot].rank < allInfo[yRoot].rank) allInfo[xRoot].parent = yRoot;
            else if (allInfo[yRoot].rank < allInfo[xRoot].rank) allInfo[yRoot].parent = xRoot;
            else {
                allInfo[yRoot].parent = xRoot;
                allInfo[xRoot].rank += 1;
            }
        }
    };
}

dsu::dsu storeConnected(1000010);

typedef int64_t vertex;
typedef int64_t num_vertices;
typedef int64_t num_edges;
typedef int64_t cost;
struct edge {
    vertex beg, end;
    cost cost_;
};

bool operator<(edge edge1, edge edge2) {
    return edge1.cost_ < edge2.cost_;
}

num_edges numEdges;
num_vertices numVertices;
edge edges[1000010];

int main() {
    scanf(INT64 " " INT64, &numVertices, &numEdges);
    num_edges i;
    REP(i, numEdges) scanf(INT64 " " INT64 " " INT64, &(edges[i].beg), &(edges[i].end), &(edges[i].cost_));
    num_vertices left = numVertices;
    std::sort(edges, edges+numEdges);
    REP(i, numEdges) {
        if (storeConnected.find(edges[i].beg) != storeConnected.find(edges[i].end)) {
            storeConnected.join(edges[i].beg, edges[i].end);
            left--;
            if (left == 1) {
                printf(INT64 "\n", edges[i].cost_);
                break;
            }
        }
    }
    if (left > 1) puts("IMPOSSIBLE");
    return 0;
}