#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked

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
char testCaseName[MAX_LINE], inputLine[MAX_LINE];

bool validPoint(vertex test) {
    return (test.x >= 1) && (test.x <= numRows) && (test.y >= 1) && (test.y <= numColumns);
}

void addIfPossible(vertex start, vertex end) {
   if (validPoint(end)) adjacencyList[end.x][end.y].push_back(start);
}

int main() {
    /**
     * The following line makes std::cin go much faster,
     * but it also means that you CAN NOT use any of the <cstdio>
     * functions, like scanf, printf, fgets, etc.
     * if you are using std::cin and std::cout for I/O
    */
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    dimen l, l2;
    while (true) {
        /**
         * Many BOSPRE problems require you to read in all of the test cases in the file
         * and the first line of a test case is usually a name line,
         * like the following:
         * -- TEST CASE 1 --
         * You are required to output this line again when you output your answer,
         * which is why we store this line in the "testCaseName" variable for later.
        */
        std::cin.getline(testCaseName, MAX_LINE);
        //Once we hit EOF, we know we've gone through all the test cases.
        if (std::cin.eof()) break;

        /**
         * Notice how I am using getline() first, and then making an input stream in order to read the integers.
         * I could be more direct, like this:
         *   std::cin >> numRows >> numColumns;
         * However, this would cause the next call to getline()
         * to return an empty line,
         * because reading the integers directly from std::cin
         * means that any newline after
         * 
         * In general, if you are using std::cin.getline() anywhere in your program repeatedly,
         * then it is best if you read in the whole input using only getline().
        */
        std::cin.getline(inputLine, MAX_LINE);
        std::istringstream firstLineStream(inputLine);
        firstLineStream >> numRows >> numColumns;
        
        REP(l, numRows) REP(l2, numColumns) adjacencyList[l+1][l2+1].clear();

        REP(l, numRows) {
            std::cin.getline(inputLine, MAX_LINE);
            std::istringstream curLineStream(inputLine);
            /**
             * The operation "curLineStream >> curToken" reads in a single token
             * from the current line, and stores it in the "curToken" variable.
             * Here, a "token" is a list of non-whitespace characters.
             * For example, "3", "X", "abc345sd", and "345:1234:dfg" are all tokens.
             * This operation will fail once we have read all of the tokens from this line.
             * so the while loop will end once there are no more tokens.
            */
            std::string curToken;
            while (curLineStream >> curToken) {
                vertex curVertex = vertex(l+1, l2+1);
                visited[curVertex.x][curVertex.y] = false;
                if (curToken[0] == 'G') goalVertex = curVertex;
                
                std::istringstream curTokenStream(curToken);
                if ((curToken[0] != 'X') && (curToken[0] != 'G')) {
                    //If the current string has a ':' character...
                    if (curToken.find(':') != std::string::npos) {
                        dimen coordX, coordY;
                        
                        curTokenStream >> coordX;
                        //Ignore one character (i.e. the colon)
                        curTokenStream.ignore(1);
                        curTokenStream >> coordY;
                        
                        adjacencyList[coordX][coordY].push_back(curVertex);
                    } else {
                        dimen distance;
                        curTokenStream >> distance;

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

        std::cout << testCaseName << "\n";
        while (curVertex != goalVertex) {
            std::cout << curVertex.x << ":" << curVertex.y << " ";
            curVertex = pred[curVertex.x][curVertex.y];
        }
        std::cout << curVertex.x << ":" << curVertex.y << "\n";
    }
    
    exit(0);
}