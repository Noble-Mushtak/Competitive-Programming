/**
 * struct heap (and others) for C
 * Comments coming soon!
 * 
 * typedefs:
 * item_type: Type of item held in segtree.
 * item_length: Type for holding list indexes and interval endpoints in segtree.
 *
 * Constants:
 * DEFAULT_HEAP: Default heap.
 * 
 * Properties:
 * item_type *list: The list of items in the heap.
 * item_length length: The number of items in the heap.
 *
 * User-Defined Functions:
 * int compareItems(item_type item1, item_type item2)
 * * Return negative value if item1 should be the parent of item2, 0 if they are effectively equal, and positive value if item1 should be the child of item2.
 * 
 * Callable Functions:
 * void insertItem(heap *heap, item_type item)
 * * Inserts item into heap.
 * void updateHeap(heap *heap, item_length index, item_type item)
 * * Updates heap by setting heap->list[index] to item and updating heap to maintain heap properties.
 * item_type extractTop(heap *heap)
 * * Deletes top from heap and returns the top.
 * * Should only be called with non-empty heap.
 * 
 * Notes:
 * The default implementation of the user-defined functions are for a min-heap.
*/

#pragma once

typedef long item_type;
typedef long item_length;
typedef struct heap {
    item_type list[100000];
    item_length length;
} heap;
heap DEFAULT_HEAP = { .length = 0 };

int compareItems(item_type item1, item_type item2) {
    return item1-item2;
}

void updateHeap(heap *heap, item_length index, item_type item) {
    item_length nextIndex;
    heap->list[index] = item;
    while (index && compareItems(heap->list[(index-1)/2], item) > 0) heap->list[index] = heap->list[(index-1)/2], heap->list[(index-1)/2] = item, index = (index-1)/2;
    while (2*index+1 < heap->length) {
        nextIndex = -1;
        if (compareItems(heap->list[2*index+1], item) < 0) nextIndex = 2*index+1;
        if (2*index+2 < heap->length && compareItems(heap->list[2*index+2], item) < 0 && compareItems(heap->list[2*index+2], heap->list[2*index+1]) < 0) nextIndex = 2*index+2;
        if (nextIndex >= 0) heap->list[index] = heap->list[nextIndex], heap->list[nextIndex] = item, index = nextIndex;
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