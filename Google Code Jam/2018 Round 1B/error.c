#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef long test_cases;
typedef long num_people;
typedef long num_groups;

num_people total, numSurveyed, groupSizes[100000];
num_groups numGroups;
long answer;

typedef long item_type;
typedef long item_length;
typedef struct heap {
    item_type list[100000];
    item_length length;
} heap;
heap roundingHeap = { .length = 0 };
item_length inverseHeap[100000];

int compareItems(item_type item1, item_type item2) {
    if ((100 % total)*2 > total) return ((groupSizes[item1]*100) % total)-((groupSizes[item2]*100) % total);
    else {
        int mod1 = (200*groupSizes[item1]-total) % (2*total);
        if (mod1 < 0) mod1 += 2*total;
        int mod2 = (200*groupSizes[item2]-total) % (2*total);
        if (mod2 < 0) mod2 += 2*total;
        return mod2-mod1;
    }
}

void updateHeap(heap *heap, item_length index, item_type item) {
    item_length nextIndex;
    heap->list[index] = item;
    while (index && compareItems(heap->list[(index-1)/2], item) > 0) {
        heap->list[index] = heap->list[(index-1)/2], heap->list[(index-1)/2] = item;
        inverseHeap[heap->list[index]] = index;
        index = (index-1)/2;
        inverseHeap[heap->list[index]] = index;
    }
    while (2*index+1 < heap->length) {
        nextIndex = -1;
        if (compareItems(heap->list[2*index+1], item) < 0) nextIndex = 2*index+1;
        if (2*index+2 < heap->length && compareItems(heap->list[2*index+2], item) < 0 && compareItems(heap->list[2*index+2], heap->list[2*index+1]) < 0) nextIndex = 2*index+2;
        if (nextIndex >= 0) {
           heap->list[index] = heap->list[nextIndex], heap->list[nextIndex] = item;
           inverseHeap[heap->list[index]] = index;
           index = nextIndex;
           inverseHeap[heap->list[index]] = index;
        }
        else break;
    }
}

void insertItem(heap *heap, item_type item) {
    updateHeap(heap, heap->length++, item);
}

item_type extractMin(heap *heap) {
    item_type top = heap->list[0];
    updateHeap(heap, 0, heap->list[--heap->length]);
    return top;
}

int main() {
    num_groups i, minGroup;
    num_people m;
    test_cases numTestCases, z;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%li %li", &total, &numGroups);
        numSurveyed = roundingHeap.length = 0;
        REPEAT(i, numGroups) {
            scanf("%li", groupSizes+i);
            insertItem(&roundingHeap, i);
            numSurveyed += groupSizes[i];
        }
        groupSizes[numGroups++] = 0, insertItem(&roundingHeap, numGroups-1);
        
        for (; numSurveyed < total; numSurveyed++) {
            minGroup = roundingHeap.list[0];
            groupSizes[minGroup]++;
            updateHeap(&roundingHeap, 0, minGroup);
            if (groupSizes[minGroup] == 1) groupSizes[numGroups++] = 0, insertItem(&roundingHeap, numGroups-1);
        }

        //REPEAT(m, numGroups) printf("%li%c", groupSizes[m], (m+1 == numGroups) ? '\n' : ' ');
        answer = 0;
        REPEAT(m, numGroups) {
            long store = (200*groupSizes[m]) / total;
            if (store % 2) answer += (store+1)/2;
            else answer += store/2;
        }
        printf("Case #%li: %li\n", z+1, answer);
    }
    
    exit(0);
}