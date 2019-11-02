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
#include <sstream>
#include <map>
#include <string>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t vertex;
typedef int64_t num_vertices;
struct edge;
struct edge {
    vertex other;
    std::list<edge>::iterator rev;

    edge() {}
    edge(vertex v) : other(v) {}
};
typedef int64_t num_edges;

num_vertices vertexOrder[2000];
struct compare_vertices {
    bool operator()(vertex v1, vertex v2) {
        return vertexOrder[v1] > vertexOrder[v2];
    }
};
std::priority_queue<vertex, std::vector<vertex>, compare_vertices> heap;

std::list<std::string> parentNames[4000];
std::map<std::string, vertex> decodeNames;
std::map<vertex, std::string> encodeNames;
std::list<edge> parents[2000], children[2000];
std::list<vertex> answer;
char storeLine[50000];
num_vertices numVertices;

int main() {
    bool beg = false;
    while (true) {
        decodeNames.clear(), encodeNames.clear(), answer.clear();
        
        fgets(storeLine, 50000, stdin);
        sscanf(storeLine, "%" PRId64, &numVertices);
        if (numVertices == 0) break;
        if (beg) puts("");
        else beg = true;
        
        num_vertices i;
        REP(i, numVertices) {
            parents[i].clear(), children[i].clear(), parentNames[i].clear();
            
            fgets(storeLine, 50000, stdin);
            std::string stringLine(storeLine);
            std::istringstream stringParser(stringLine);
            std::string name;
            stringParser >> name;
            decodeNames.insert(std::pair<std::string, vertex>(name, i));
            encodeNames.insert(std::pair<vertex, std::string>(i, name));
            
            while (stringParser) {
                std::string parent;
                stringParser >> parent;
                if (parent.size() > 0) parentNames[i].push_back(parent);
            }
        }
        
        REP(i, numVertices) {
            for (auto it = parentNames[i].begin(); it != parentNames[i].end(); ++it) {
                vertex parentVertex = decodeNames[*it];
                vertex childVertex = i;
                
                edge toParent, toChild;
                toParent.other = parentVertex, toChild.other = childVertex;
                parents[i].push_back(toParent);
                children[parentVertex].push_back(toChild);
                auto parentIt = std::prev(parents[i].end());
                auto childIt = std::prev(children[parentVertex].end());
                parentIt->rev = childIt, childIt->rev = parentIt;
            }
        }

        i = 0;
        for (auto it = decodeNames.begin(); it != decodeNames.end(); ++it, ++i) vertexOrder[it->second] = i;
        
        REP(i, numVertices) {
            if (parents[i].size() == 0) heap.push(i);
        }
        while (heap.size() > 0) {
            vertex curVertex = heap.top();
            heap.pop();
            answer.push_back(curVertex);
            for (auto it = children[curVertex].begin(); it != children[curVertex].end(); it = children[curVertex].erase(it)) {
                vertex otherVertex = it->other;
                parents[otherVertex].erase(it->rev);
                if (parents[otherVertex].size() == 0) heap.push(otherVertex);
            }
        }

        if (answer.size() < numVertices) puts("cannot be ordered");
        else {
            for (auto it = answer.begin(); it != answer.end(); ++it) {
                puts(encodeNames[*it].c_str());
            }
        }
    }
    return 0;
}