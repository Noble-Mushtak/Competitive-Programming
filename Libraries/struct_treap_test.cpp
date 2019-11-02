#include "struct_treap.h"

typedef int64_t num_queries;
typedef int64_t item_key;
typedef int64_t item_value;

treap::treap<item_key, item_value> root;

int main() {
    num_queries l, numQueries;
    num_items newPos, leftPos, rightPos;
    item_key newKey, left, right;
    item_value newElem;
    char command[10];
    scanf("%" PRId64, &numQueries);
    for (l = 0; l < numQueries; l++) {
        scanf("%s", command);
        if (command[1] == 'P') {
            if (command[0] == 'S') {
                scanf("%" PRId64 "%" PRId64, &leftPos, &rightPos);
                printf(" > SP %" PRId64 " %" PRId64 "\n", leftPos, rightPos);
                printf("%" PRId64 "\n", root.getIntervalSum(leftPos, rightPos));
            } else if (command[0] == 'A') {
                scanf("%" PRId64 "%" PRId64 "%" PRId64, &newPos, &newKey, &newElem);
                printf(" > AP %" PRId64 " %" PRId64 " %" PRId64 "\n", newPos, newKey, newElem);
                root.addElementByPos(newPos, newKey, newElem);
            } else if (command[0] == 'R') {
                scanf("%" PRId64, &newPos);
                printf(" > RP %" PRId64 "\n", newPos);
                root.removeElementByPos(newPos);
            }
        } else {
            if (command[0] == 'S') {
                scanf("%" PRId64 "%" PRId64, &left, &right);
                printf(" > S %" PRId64 " %" PRId64 "\n", left, right);
                printf("%" PRId64 "\n", root.getKeyRangeSum(left, right));
            } else if (command[0] == 'A') {
                scanf("%" PRId64 "%" PRId64, &newKey, &newElem);
                printf(" > A %" PRId64 " %" PRId64 "\n", newKey, newElem);
                root.addElementByKey(newKey, newElem, false);
            } else if (command[0] == 'R') {
                scanf("%" PRId64, &newKey);
                printf(" > R %" PRId64 "\n", newKey);
                root.removeElementByKey(newKey);
            }
        }
    }
    
    exit(0);
}