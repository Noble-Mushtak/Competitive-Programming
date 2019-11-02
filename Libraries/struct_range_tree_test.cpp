#include "struct_range_tree.h"

typedef int32_t num;

//#define BULK_TEST

#ifdef BULK_TEST
const num_items NUM_ITEMS = 1000000;
std::array<num, 3> points[NUM_ITEMS];
std::array<num, 3> storeQuery[NUM_ITEMS];
#else
const num_items MAX_NUM_ITEMS = 10000;
num_items NUM_ITEMS;
std::array<num, 3> points[MAX_NUM_ITEMS];
std::array<num, 3> storeQuery[MAX_NUM_ITEMS];
#endif

#include <sys/time.h>

void printDiff(struct timespec start, struct timespec end) {
    uint64_t microseconds = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    if (microseconds < 2000) printf("%lu microseconds\n", microseconds);
    else printf("%lu milliseconds\n", microseconds/1000); 
}

int main() {
#ifdef BULK_TEST
    for (num_items i = 0; i < NUM_ITEMS; i++) {
        points[i][0] = i;
        points[i][1] = rand() % 100;
        points[i][2] = rand() % 100;
    }
#else
    scanf("%" PRId64, &NUM_ITEMS);
    for (num_items i = 0; i < NUM_ITEMS; i++) {
        points[i][0] = i;
        scanf("%" PRId32 " %" PRId32, &(points[i][1]), &(points[i][2]));
    }
#endif

    struct timespec buildStart, buildEnd;
    clock_gettime(CLOCK_MONOTONIC_RAW, &buildStart);
    
    range_tree::subtree<num, 3, 2> test(NUM_ITEMS, points);
    //print(test.internalTree.root->value.second);
    //printSpecial(test.internalTree);
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &buildEnd);
    printDiff(buildStart, buildEnd);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    for (num i = 0; i < 1; i++) {
#ifdef BULK_TEST
        num_items querySize = test.getPointsInRange(nullptr, std::array<num, 3>{0, 10, 10}, std::array<num, 3>{0, 70, 70});
#else
        num_items querySize = test.getPointsInRange(storeQuery, std::array<num, 3>{0, 0, 55}, std::array<num, 3>{0, 8, 87});
#endif
        printf("%ld\n", querySize);
        for (num_items i = 0; i < std::min(querySize, 1000l); i++) {
            printf("%d %d\n", storeQuery[i][1], storeQuery[i][2]);
        } // */
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printDiff(start, end); // */
    exit(0);
}