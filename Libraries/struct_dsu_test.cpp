#include "struct_dsu.h"

typedef int64_t num_queries;

dsu::dsu curDsu;
num_queries numQueries;

int main() {
    num_queries l;
    dsu::item curElem, elem1, elem2;
    char command[10];
    
    scanf("%" PRId64, &numQueries);
    for (l = 0; l < numQueries; l++) {
        scanf("%s", command);
        if (command[0] == 'A') {
            scanf("%" PRId64, &curElem);
            curDsu.initialize(curElem);
        } else if (command[0] == 'V') {
            scanf("%" PRId64, &curElem);
            printf("%" PRId64 "\n", curDsu.allInfo[curElem].parent);
        } else if (command[0] == 'J') {
            scanf("%" PRId64 " %" PRId64, &elem1, &elem2);
            curDsu.join(elem1, elem2);
        }
    }
    
    exit(0);
}