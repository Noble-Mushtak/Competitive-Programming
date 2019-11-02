#include <stdio.h>
#include <stdlib.h>
#include "struct_segtree.h"

int main() {
    segtree testing = DEFAULT_SEGTREE;
    long items[] = {1, 34, 56, 63, 42, 35, 32, 4};
    segtreeInit(&testing, 0, 0, 7, items);
    puts("BEFORE UPDATE");
    printf("0 7: %li\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 0, 7).item));
    printf("0 2: %li\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 0, 2).item));
    printf("6 7: %li\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 6, 7).item));
    printf("0 8: %li\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 0, 8).item));
    printf("8 8: %hhi\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 8, 8).hasItem));
    segtreeUpdate(&testing, 0, testing.intervalMin, testing.intervalMax, 3, 5, 1);
    puts("AFTER UPDATE");
    printf("0 7: %li\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 0, 7).item));
    printf("0 2: %li\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 0, 2).item));
    printf("6 7: %li\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 6, 7).item));
    printf("0 8: %li\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 0, 8).item));
    printf("8 8: %hhi\n", (segtreeQuery(&testing, 0, testing.intervalMin, testing.intervalMax, 8, 8).hasItem));
    
    exit(0);
}