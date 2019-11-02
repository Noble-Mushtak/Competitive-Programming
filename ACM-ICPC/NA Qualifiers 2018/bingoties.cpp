#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <list>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_cards;
typedef int64_t num_cells;
typedef int64_t cell;

num_cards numCards;
cell board[200][5][5];
num_cells boardQuery[200][5000];

bool contains(std::list<cell> list, cell query) {
    for (auto it = list.begin(); it != list.end(); it++) {
        if ((*it) == query) return true;
    }
    return false;
}

bool wins(cell card[5][5], std::list<cell> list) {
    num_cells i, i2;
    REP(i, 5) {
        bool wins = true;
        REP(i2, 5) wins = wins && contains(list, card[i][i2]);
        if (wins) return true;
    }
    return false;
}

std::list<cell> mergeRows(cell row1[5], cell row2[5], cell commonElem) {
    std::list<cell> merged;
    num_cells i;
    REP(i, 5) if (row1[i] != commonElem) merged.push_back(row1[i]);
    REP(i, 5) if ((row2[i] != commonElem) && !contains(merged, row2[i])) merged.push_back(row2[i]);
    return merged;
}

int main() {
    scanf("%" PRId64, &numCards);
    
    num_cards i, i2, i3;
    num_cells j;
    cell storeCell;
    REP(i, numCards) {
        REP(storeCell, 5000) boardQuery[i][storeCell] = -1;
        REP(j, 25) {
            scanf("%" PRId64, &(board[i][j/5][j % 5]));
            boardQuery[i][board[i][j/5][j % 5]] = j/5;
        }
    }
    REP(i, numCards) {
        for (i2 = i+1; i2 < numCards; i2++) {
            REP(storeCell, 5000) if ((boardQuery[i][storeCell] > -1) && (boardQuery[i2][storeCell] > -1)) {
                std::list<cell> requiredCells = mergeRows(board[i][boardQuery[i][storeCell]], board[i2][boardQuery[i2][storeCell]], storeCell);
                REP(i3, numCards) if (wins(board[i3], requiredCells)) break;
                
                if (i3 == numCards) {
                    PRINTF("%" PRId64 "\n", storeCell);
                    printf("%" PRId64 " %" PRId64 "\n", i+1, i2+1);
                    exit(0);
                }
            }
        }
    }
    puts("no ties");
    
    return 0;
}