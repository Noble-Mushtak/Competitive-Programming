#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <algorithm>

#define REP(var, token) for(var = 0; var < token; ++var)

typedef int64_t dimen;
typedef int64_t height;
typedef int64_t num_points;

struct point {
    dimen x, y;
    point(dimen x1 = 0, dimen y1 = 0) : x(x1), y(y1) {}
    bool operator==(point other) { return (x == other.x) && (y == other.y); }
};

dimen numRows, numColumns;
point minPoint, maxPoint;
height matrix[1000][1000], minHeight, maxHeight;
char name[10000], inputLine[10000];
bool answers[1000][1000], memoed[1000][1000], visited[1000][1000];

height heightAtPoint(point loc) {
    return matrix[loc.x][loc.y];
}

bool valid(point loc) {
    return (loc.x >= 0) && (loc.x < numColumns) && (loc.y >= 0) && (loc.y < numRows);
}

bool dfs(point curPoint) {
    num_points i;
    if (curPoint == maxPoint) return true;
    if (memoed[curPoint.x][curPoint.y]) return answers[curPoint.x][curPoint.y];
    visited[curPoint.x][curPoint.y] = true;
    height curHeight = heightAtPoint(curPoint);
    
    point newPoints[4];
    newPoints[0] = point(curPoint.x-1, curPoint.y);
    newPoints[1] = point(curPoint.x+1, curPoint.y);
    newPoints[2] = point(curPoint.x, curPoint.y+1);
    newPoints[3] = point(curPoint.x, curPoint.y-1);
    bool answer = false;
    REP(i, 4) if (!answer && valid(newPoints[i])) {
        if ((heightAtPoint(newPoints[i]) >= curHeight) && !visited[newPoints[i].x][newPoints[i].y]) {
            bool subAnswer = dfs(newPoints[i]);
            answer = answer || subAnswer;
        }
    }
    
    visited[curPoint.x][curPoint.y] = false;
    memoed[curPoint.x][curPoint.y] = true;
    answers[curPoint.x][curPoint.y] = answer;
    return answer;
}

int main() {
    dimen i, j;
    while (true) {
        fgets(name, 10000, stdin);
        if (feof(stdin)) break;
        fgets(inputLine, 10000, stdin);
        sscanf(inputLine, "%" PRId64 " %" PRId64, &numRows, &numColumns);
        REP(i, numRows) {
            fgets(inputLine, 10000, stdin);
            char *curPtr;
            REP(j, numColumns) {
                if (j == 0) curPtr = strtok(inputLine, " ");
                else curPtr = strtok(nullptr, " ");
                sscanf(curPtr, "%" PRId64, matrix[i]+j);
            }
        }

        /* REP(i, numRows) REP(j, numColumns) printf("%" PRId64 "%c", matrix[i][j], (j+1 == numColumns) ? '\n' : ' ');
        puts(""); // */
        minHeight = 1000, maxHeight = -1;
        REP(i, numRows) REP(j, numColumns) {
            memoed[i][j] = visited[i][j] = false;
            if (matrix[i][j] < minHeight) minPoint = point(i, j), minHeight = matrix[i][j];
            if (matrix[i][j] > maxHeight) maxPoint = point(i, j), maxHeight = matrix[i][j];
        }
        bool answer = dfs(minPoint);
        printf(name);
        printf("%" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %s\n", minPoint.x+1, minPoint.y+1, maxPoint.x+1, maxPoint.y+1, answer ? "yes" : "no");
    }
    
    return 0;
}
