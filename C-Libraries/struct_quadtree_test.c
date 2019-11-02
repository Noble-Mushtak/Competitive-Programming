#include <stdio.h>
#include <stdlib.h>
#include "struct_quadtree.h"

int main() {
    quadtree testing = DEFAULT_QUADTREE;
    long items[4][5] = {{1, 2, 3, 4, 5}, {3, 4, 2, 6, 7}, {1, 2, 9, 10, 1}, {1, 2, 4, 4, 5}};
    quadtreeInit(&testing, 0, 0, 3, 0, 4, (long**)items, 5);
    puts("BEFORE UPDATE");
    printf("0 3 0 4: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 0, 3, 0, 4).item));
    printf("1 2 1 3: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 1, 2, 1, 3).item));
    printf("2 3 0 4: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 2, 3, 0, 4).item));
    printf("1 3 2 4: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 1, 3, 2, 4).item));
    printf("0 0 0 4: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 0, 0, 0, 4).item));
    quadtreeUpdate(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 1, 2, 1, 3, 1);
    puts("AFTER UPDATE");
    printf("0 3 0 4: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 0, 3, 0, 4).item));
    printf("1 2 1 3: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 1, 2, 1, 3).item));
    printf("2 3 0 4: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 2, 3, 0, 4).item));
    printf("1 3 2 4: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 1, 3, 2, 4).item));
    printf("0 0 0 4: %li\n", (quadtreeQuery(&testing, 0, testing.intervalMin1, testing.intervalMax1, testing.intervalMin2, testing.intervalMax2, 0, 0, 0, 4).item));
    
    exit(0);
}