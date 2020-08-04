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
typedef int64_t vertex;
typedef int64_t num_vertices;
typedef int64_t num_edges;
struct edge {
    num_edges index;
    vertex beg, end;
};
typedef int64_t event_time;
struct vertex_info {
    vertex v;
    num_vertices before;
};

test_cases numTestCases;
num_vertices numVertices, numCorresponding[10000];
num_edges numEdges;
event_time achievementTimes[10000], sortedTimes[10000], answers[10000];
const event_time MAX_LATENCY = 1000000;
std::list<edge> adjacencyLists[10000];
std::priority_queue<edge> primLine;
std::priority_queue<vertex_info> vertexLine;
bool visited[10000];

bool operator<(vertex_info info1, vertex_info info2) {
    return info1.before > info2.before;
}

bool operator<(edge edge1, edge edge2) {
    return achievementTimes[edge1.end] > achievementTimes[edge2.end];
}

int main() {
    test_cases k;
    scanf(INT64, &numTestCases);
    REP(k, numTestCases) {
        scanf(INT64 " " INT64, &numVertices, &numEdges);
        
        event_time t;
        REP(t, 10000) numCorresponding[t] = (t == 0) ? 1 : 0;
        
        num_vertices i;
        adjacencyLists[0].clear();
        achievementTimes[0] = 0;
        REP(i, numVertices-1) {
            visited[i+1] = false;
            adjacencyLists[i+1].clear();
            scanf(INT64, achievementTimes+(i+1));
            if (achievementTimes[i+1] < 0) {
                vertex_info curInfo;
                curInfo.v = i+1;
                curInfo.before = -achievementTimes[i+1];
                vertexLine.push(curInfo);
                
                achievementTimes[i+1] = 1000000;
            }
            else ++numCorresponding[achievementTimes[i+1]];
        }
        
        num_vertices curPast = 0;
        event_time curTime = 0;
        while (!vertexLine.empty()) {
            vertex_info curInfo = vertexLine.top();
            vertexLine.pop();
            while (curPast < curInfo.before) {
                curPast += numCorresponding[curTime];
                ++curTime;
            }
            if (curPast > curInfo.before) fprintf(stderr, "IMPOSSIBLE: " INT64 " " INT64 " " INT64 "\n", curInfo.v, curPast, curTime), exit(1);
            achievementTimes[curInfo.v] = curTime;
            ++numCorresponding[curTime];
        }

        while (!primLine.empty()) primLine.pop();
        num_edges l;
        REP(l, numEdges) {
            
            edge curEdge;
            curEdge.index = l;
            scanf(INT64 " " INT64, &(curEdge.beg), &(curEdge.end));
            --curEdge.beg, --curEdge.end;
            adjacencyLists[curEdge.beg].push_back(curEdge);
            
            if (curEdge.beg == 0) primLine.push(curEdge);
            
            edge revEdge;
            revEdge.index = l, revEdge.beg = curEdge.end, revEdge.end = curEdge.beg;
            adjacencyLists[revEdge.beg].push_back(revEdge);
            answers[l] = 0;
        }
        
        visited[0] = true;
        while (!primLine.empty()) {
            edge curEdge = primLine.top();
            primLine.pop();
            if (visited[curEdge.end]) continue;
            if (achievementTimes[curEdge.end] == achievementTimes[curEdge.beg]) continue;
            visited[curEdge.end] = true;
            //PRINTF(INT64 " " INT64 " " INT64 " | " INT64 "\n", curEdge.index, curEdge.beg, curEdge.end, achievementTimes[curEdge.end]);
            
            answers[curEdge.index] = achievementTimes[curEdge.end]-achievementTimes[curEdge.beg];
            for (auto it = adjacencyLists[curEdge.end].begin(); it != adjacencyLists[curEdge.end].end(); ++it) primLine.push(*it);
        }
        
        printf("Case #" INT64 ": ", k+1);
        REP(l, numEdges) {
            if (answers[l] == 0) answers[l] = MAX_LATENCY;
            printf(INT64 "%c", answers[l], (l+1 == numEdges) ? '\n' : ' ');
        }
    }
    
    return 0;
}