#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

typedef int64_t num_vertices;
typedef int64_t dimen;
struct vertex {
    dimen x, y;
    vertex() {}
    vertex(dimen x1, dimen y1) : x(x1), y(y1) {}

    bool operator==(vertex other) { return (x == other.x) && (y == other.y); }
    bool operator!=(vertex other) { return (x != other.x) || (y != other.y); }
};

dimen numRows, numColumns;
std::list<vertex> adjacencyList[2000][2000];
vertex pred[2000][2000];
vertex goalVertex;
bool visited[2000][2000];
const int64_t MAX_LINE = 100000;
char name[MAX_LINE], inputLine[MAX_LINE];

bool validPoint(vertex test) {
    return (test.x >= 1) && (test.x <= numRows) && (test.y >= 1) && (test.y <= numColumns);
}

void addIfPossible(vertex start, vertex end) {
   if (validPoint(end)) adjacencyList[end.x][end.y].push_back(start);
}

bool contains(char *str, char test) {
    while (*str != '\0') {
        if (*str == test) return true;
        str++;
    }
    return false;
}

std::vector<char*> tokenize(char *str, const char *delims = " \n") {
    std::vector<char*> tokens;
    for (char *curPtr = strtok(str, delims); curPtr != nullptr; curPtr = strtok(nullptr, delims)) tokens.push_back(curPtr);
    return tokens;
}

int main() {
    dimen l, l2;
    while (true) {
        fgets(name, MAX_LINE, stdin);
        if (feof(stdin)) break;

        fgets(inputLine, MAX_LINE, stdin);
        sscanf(inputLine, INT64 " " INT64, &numRows, &numColumns);
        REP(l, numRows) REP(l2, numColumns) adjacencyList[l+1][l2+1].clear();

        REP(l, numRows) {
            fgets(inputLine, MAX_LINE, stdin);
            auto tokens = tokenize(inputLine);
            REP(l2, numColumns) {
                char *curPtr = tokens[l2];

                vertex curVertex = vertex(l+1, l2+1);
                visited[curVertex.x][curVertex.y] = false;
                if (curPtr[0] == 'G') goalVertex = curVertex;

                if ((curPtr[0] != 'X') && (curPtr[0] != 'G')) {
                    if (contains(curPtr, ':')) {
                        dimen coordX, coordY;
                        sscanf(curPtr, INT64 ":" INT64, &coordX, &coordY);
                        adjacencyList[coordX][coordY].push_back(curVertex);
                    } else {
                        dimen distance;
                        sscanf(curPtr, INT64, &distance);

                        addIfPossible(curVertex, vertex(curVertex.x-distance, curVertex.y));
                        addIfPossible(curVertex, vertex(curVertex.x+distance, curVertex.y));
                        for (dimen d2 = -distance+1; d2 <= distance-1; d2++) {
                            addIfPossible(curVertex, vertex(curVertex.x+d2, curVertex.y+std::abs(distance-std::abs(d2))));
                            addIfPossible(curVertex, vertex(curVertex.x+d2, curVertex.y-std::abs(distance-std::abs(d2))));
                        }
                    }
                }
            }
        }

        std::queue<vertex> search;
        search.push(goalVertex);
        vertex curVertex;
        while (!search.empty()) {
            curVertex = search.front();
            if ((curVertex.x == 1) || (curVertex.x == numRows) || (curVertex.y == 1) || (curVertex.y == numColumns)) break;

            search.pop();
            for (auto it = adjacencyList[curVertex.x][curVertex.y].begin(); it != adjacencyList[curVertex.x][curVertex.y].end(); ++it) {
                if (!visited[it->x][it->y]) {
                    pred[it->x][it->y] = curVertex;
                    search.push(*it);
                    visited[it->x][it->y] = true;
                }
            }
        }
        //Crash the program if we don't find a path to a boundary square:
        if (search.empty()) exit(1);

        printf("%s", name);
        while (curVertex != goalVertex) {
            printf(INT64 ":" INT64 " ", curVertex.x, curVertex.y);
            curVertex = pred[curVertex.x][curVertex.y];
        }
        printf(INT64 ":" INT64 "\n", curVertex.x, curVertex.y);
    } // */                                                                                                                                    
    exit(0);
}