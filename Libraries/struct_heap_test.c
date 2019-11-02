#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include "struct_heap.h"

typedef int64_t num_queries;
typedef int64_t item_key;
typedef int64_t item_value;
typedef heap::pair<item_key, item_value> heap_item;

int main() {
    heap::heap<heap_item> testing;
    num_queries l, numQueries;
    item_key curKey;
    item_value curValue;
    bool result;
    char command[5];
    scanf("%" PRId64, &numQueries);
    
    for (l = 0; l < numQueries; l++) {
        scanf("%s", command);
        if (command[0] == 'E') {
            puts(" > E");
            if (testing.length == 0) puts("Heap is empty.");
            else {
                heap_item storeItem = testing.extractTop();
                printf("%" PRId64 " %" PRId64 "\n", storeItem.key, storeItem.val);
            }
        } else if (command[0] == 'I') {
            scanf("%" PRId64 "%" PRId64, &curKey, &curValue);
            printf(" > I %" PRId64 " %" PRId64 "\n", curKey, curValue);
            result = testing.insertItem(heap_item(curKey, curValue));
            if (!result) puts("Heap already has item with that key.");
        } else if (command[0] == 'V') {
            scanf("%" PRId64, &curKey);
            printf(" > V %" PRId64 "\n", curKey);
            if (testing.itemExists(curKey)) {
                printf("%" PRId64 "\n", testing.list[testing.inverseList[curKey]].val);
            }
            else puts("Heap does not have item with that key.");
        } else if (command[0] == 'D') {
            scanf("%" PRId64, &curKey);
            printf(" > D %" PRId64 "\n", curKey);
            result = testing.deleteItem(curKey);
            if (!result) puts("Heap does not have item with that key.");
        }
    }
    
    exit(0);
}