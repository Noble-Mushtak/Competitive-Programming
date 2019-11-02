#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <array>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num;
typedef int64_t num_nums;

struct board {
    std::array<num, 15> data;
    
    num getCell(num_nums i, num_nums j) {
        return data[i*(i+1)/2+j];
    }
    
    void setCell(num_nums i, num_nums j, num cellVal) {
        data[i*(i+1)/2+j] = cellVal;
    }
    
    num_nums hash() {
        num_nums answer = 0, i;
        REP(i, 15) {
            answer += (data[i] != 0);
            if (i+1 < 15) answer *= 2;
        }
        return answer;
    }

    void print() {
        num_nums i, j;
        REP(i, 5) REP(j, i+1) PRINTF("%" PRId64 "%c", getCell(i, j), (j == i) ? '\n' : ' ');
    }
};

board initialBoard;
num optimalScore[100000];
bool visited[100000];

num calcOptimal(board curBoard) {
    //printf("%" PRId64 "\n", curBoard.hash());
    curBoard.print();
    
    num_nums i, j;
    bool movePossible = false;
    num answer = -1000000;
    REP(i, 5) REP(j, i+1) if (curBoard.getCell(i, j) == 0) {
        if ((i >= 2) && (j <= i-2) && (curBoard.getCell(i-1, j) != 0) && (curBoard.getCell(i-2, j) != 0)) {
        //PRINTF("MOVE 1\n");
            movePossible = true;
            num moveValue = curBoard.getCell(i-1, j)*curBoard.getCell(i-2, j);
            
            board newBoard = curBoard;
            newBoard.setCell(i, j, curBoard.getCell(i-2, j));
            newBoard.setCell(i-1, j, 0), newBoard.setCell(i-2, j, 0);
            answer = std::max(answer, moveValue-calcOptimal(newBoard));
        }
        
        if ((i+2 < 5) && (curBoard.getCell(i+1, j) != 0) && (curBoard.getCell(i+2, j) != 0)) {
        //PRINTF("MOVE 2\n");
            movePossible = true;
            num moveValue = curBoard.getCell(i+1, j)*curBoard.getCell(i+2, j);
            
            board newBoard = curBoard;
            newBoard.setCell(i, j, curBoard.getCell(i+2, j));
            newBoard.setCell(i+1, j, 0), newBoard.setCell(i+2, j, 0);
            answer = std::max(answer, moveValue-calcOptimal(newBoard));
        }
        
        if ((j >= 2) && (curBoard.getCell(i, j-1) != 0) && (curBoard.getCell(i, j-2) != 0)) {
        //PRINTF("MOVE 3\n");
            movePossible = true;
            num moveValue = curBoard.getCell(i, j-1)*curBoard.getCell(i, j-2);
            
            board newBoard = curBoard;
            newBoard.setCell(i, j, curBoard.getCell(i, j-2));
            newBoard.setCell(i, j-1, 0), newBoard.setCell(i, j-2, 0);
            answer = std::max(answer, moveValue-calcOptimal(newBoard));
        }
        
        if ((j >= 2) && (curBoard.getCell(i-1, j-1) != 0) && (curBoard.getCell(i-2, j-2) != 0)) {
        //PRINTF("MOVE 4\n");
            movePossible = true;
            num moveValue = curBoard.getCell(i-1, j-1)*curBoard.getCell(i-2, j-2);
            
            board newBoard = curBoard;
            newBoard.setCell(i, j, curBoard.getCell(i-2, j-2));
            newBoard.setCell(i-1, j-1, 0), newBoard.setCell(i-2, j-2, 0);
            answer = std::max(answer, moveValue-calcOptimal(newBoard));
        }
        
        if ((j+2 <= i) && (curBoard.getCell(i, j+1) != 0) && (curBoard.getCell(i, j+2) != 0)) {
        //PRINTF("MOVE 5\n");
            movePossible = true;
            num moveValue = curBoard.getCell(i, j+1)*curBoard.getCell(i, j+2);
            
            board newBoard = curBoard;
            newBoard.setCell(i, j, curBoard.getCell(i, j+2));
            newBoard.setCell(i, j+1, 0), newBoard.setCell(i, j+2, 0);
            answer = std::max(answer, moveValue-calcOptimal(newBoard));
        }
        
        if ((i+2 < 5) && (curBoard.getCell(i+1, j+1) != 0) && (curBoard.getCell(i+2, j+2) != 0)) {
        //PRINTF("MOVE 2\n");
            movePossible = true;
            num moveValue = curBoard.getCell(i+1, j+1)*curBoard.getCell(i+2, j+2);
            
            board newBoard = curBoard;
            newBoard.setCell(i, j, curBoard.getCell(i+2, j+2));
            newBoard.setCell(i+1, j+1, 0), newBoard.setCell(i+2, j+2, 0);
            answer = std::max(answer, moveValue-calcOptimal(newBoard));
        }
    }

    if (!movePossible) PRINTF("BACKTRACK\n");
    if (!movePossible) return 0;
    else return answer;
}

int main() {
    num_nums i, j;
    num storeNum;
    REP(i, 5) REP(j, i+1) {
        scanf("%" PRId64, &storeNum);
        initialBoard.setCell(i, j, storeNum);
    }
    
    printf("%" PRId64 "\n", calcOptimal(initialBoard));
    
    return 0;
}