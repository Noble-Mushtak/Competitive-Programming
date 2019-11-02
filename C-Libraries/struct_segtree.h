/**
 * struct segtree (and others) for C
 * 
 * typedefs:
 * item_type: Type of item held in segtree
 * item_length: Type for holding list indexes and interval endpoints in segtree.
 * item_container: Container for item_type:
 * * bool item_container.hasItem: true iff the container holds an item.
 * * item_type item_container.item: The item iff .hasItem. Otherwise, likely garbage that should be ignored.
 *
 * Constants:
 * DEFAULT_SEGTREE: Default segtree.
 *
 * Properties:
 * item_type list[10000]: The list containing all of the items for the segtree.
 * item_container lazy[10000]: The list used for update propogation.
 * item_length size: The size of tree->list and tree->lazy, equal to 10000.
 * item_length intervalMin: The minimum of intervals for segtree.
 * item_length intervalMax: The maximum of intervals for segtree.
 *
 * User-Defined Functions:
 * inline item_type segtreeMerge(item_type item1, item_type item2)
 * * User-defined function that merges two items together to create a new item. This could be to merge two children items into a parent item or to merge two items in .lazy to combine them into one update.
 * inline item_type segtreeSingleUpdate(segtree *tree, item_length start, item_length end, item_length ind, item_type updateItem)
 * * User-defined function that updates tree->list[ind] (representing the interval [start, end]) with the update of updateItem.
 *
 * Helper Functions:
 * inline void segtreePropogate(segtree *tree, item_length ind, item_type updateItem)
 * * Lazily propogates an update from tree->list[ind] to its children, tree->lazy[2*ind+1] and tree->lazy[2*ind+2].
 * inline void segtreeLazy(segtree *tree, item_length ind, item_length start, item_length end)
 * * Checks if there is a lazy update at tree->lazy[ind] and if there is, updates tree->list[ind] (representing the interval [start, end]) and propogates accordingly.
 *
 * Callable Functions:
 * void segtreeInit(segtree *tree, item_length ind, item_length start, item_length end, item_type *items)
 * * MUST BE CALLED BEFORE segtreeQuery() AND segtreeUpdate() CAN BE USED
 * * Initializes the segtree tree from tree->list[ind] (representing the interval [start, end]) to all of its children with array items. If ind is the root (i.e. 0), then .intervalMin will be set to start and .intervalMax will be set to end.
 * * Should be called as the following (where tree is the pointer to the segtree):
 * * segtreeInit(tree, 0, [smallest index of items, i.e. .intervalMin], [biggest index of items, i.e. .intervalMax], [array containing items for segtree]).
 * 
 * item_container segtreeQuery(segtree *tree, item_length ind, item_length start, item_length end, item_length begInterval, item_length endInterval)
 * * Uses tree->list[ind] (representing the interval [start, end]) and all of its children to find the value associated with the interval [begInterval, endInterval]. .hasItem is true iff [begInterval, endInterval] overlaps with [start, end].
 * * Should be called as the following (where tree is the pointer to the segtree):
 * * segtreeQuery(tree, 0, tree->intervalMin, tree->intervalMax, [beginning of query interval], [end of query interval])
 * 
 * void segtreeUpdate(segtree *tree, item_length ind, item_length start, item_length end, item_length begInterval, item_length endInterval, item_type updateItem)
 * * Updates tree->list[ind] (representing the interval [start, end]) and all of its children with updateItem in the interval [begInterval, endInterval].
 * * Should be called as the following (where tree is the pointer to the segtree):
 * * segtreeUpdate(tree, 0, tree->intervalMin, tree->intervalMax, [beginning of update interval], [end of update interval], [item to update with])
 *
 * Notes:
 * The default implementation of the user-defined functions create a segtree such that if tree->list[ind] represents the interval [start, end], then tree->list[ind] represents the sum of all of the elements in [start, end].
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int64_t item_type;
typedef int64_t item_length;
typedef struct {
    item_type item;
    bool hasItem;
} item_container;
typedef struct segtree {
    item_type list[10000];
    item_container lazy[10000];
    item_length size;
    item_length intervalMin;
    item_length intervalMax;
} segtree;
segtree DEFAULT_SEGTREE = { .size = 10000, .intervalMin = 0, .intervalMax = 0 };

static inline item_type segtreeMerge(item_type item1, item_type item2) {
    //Merge items by adding them together
    return item1+item2;
}

static inline void segtreeSingleUpdate(segtree *tree, item_length ind, item_length start, item_length end, item_type updateItem) {
    //Update intervals by incrementing them by updateItem times the number of elements an interval has
    tree->list[ind] += (end-start+1)*updateItem;
}

static inline void segtreePropogate(segtree *tree, item_length ind, item_type updateItem) {
    item_length i;
    //Propogate to both childs
    for (i = 0; i < 2; i++) {
        //If there is no lazy update, then initialize the lazy update.
        if (!tree->lazy[2*ind+i+1].hasItem) tree->lazy[2*ind+i+1].item = updateItem, tree->lazy[2*ind+i+1].hasItem = true;
        //Otherwise, merge the two updates together.
        else tree->lazy[2*ind+i+1].item = segtreeMerge(tree->lazy[2*ind+i+1].item, updateItem);
   }
}

static inline void segtreeLazy(segtree *tree, item_length ind, item_length start, item_length end) {
    //If there is a lazy update:
    if (tree->lazy[ind].hasItem) {
        //Update tree->list[ind] with tree->lazy[ind].item.
        segtreeSingleUpdate(tree, ind, start, end, tree->lazy[ind].item);
        //Propogate the update if tree->list[ind] has children.
        if (start != end) segtreePropogate(tree, ind, tree->lazy[ind].item);
        //Erase this lazy update.
        tree->lazy[ind].hasItem = false;
    }
}
 
void segtreeInit(segtree *tree, item_length ind, item_length start, item_length end, item_type *items) {
    //The midpoint of this interval:
    item_length mid = (start+end)/2;
    //Remember to set .intervalMin and .intervalMax at the beginning:
    if (!ind) tree->intervalMin = start, tree->intervalMax = end;
    //If this initialization makes us go beyond the size of tree->list, print an error message and exit the program:
    if (2*ind+2 >= tree->size) puts("SEGTREE DOES NOT HAVE ENOUGH SPACE. ABORT!!!"), exit(1);
    
    //In the rare case that the whole interval is only one element, just set the root accordingly and exit:
    if (start == end) {
        tree->list[ind] = items[start];
        return;
    }

    //If the left half of this interval is only one element, then set the left child accordingly. Otherwise, traverse the left half of this interval.
    (start == mid) ? (tree->list[2*ind+1] = items[start]) : segtreeInit(tree, 2*ind+1, start, mid, items);
    //Do the same thing for the right half of this interval.
    (mid+1 == end) ? (tree->list[2*ind+2] = items[mid+1]) : segtreeInit(tree, 2*ind+2, mid+1, end, items);
    //Merge the two children to set tree->list[ind].
    tree->list[ind] = segtreeMerge(tree->list[2*ind+1], tree->list[2*ind+2]);
}
 
item_container segtreeQuery(segtree *tree, item_length ind, item_length start, item_length end, item_length begInterval, item_length endInterval) {
    //The answer for this interval, the answer for the left half of this interval, and the answer for the right half of this interval:
    item_container answer = { .hasItem = false }, ans1, ans2;
    //The midpoint of this interval:
    item_length mid = (start+end)/2;
    //Update tree->list[ind] with any lazy updates.
    segtreeLazy(tree, ind, start, end);

    //Return the default invalid answer of no item if the query interval has no intersection with this interval.
    if (begInterval > end || endInterval < start) return answer;
    //If this interval is completely inside the query interval, simply return tree->list[ind]
    if (start >= begInterval && end <= endInterval) {
        answer.hasItem = true, answer.item = tree->list[ind];
        return answer;
    }

    //If none of the cases above apply, traverse both halves of this interval.
    ans1 = segtreeQuery(tree, 2*ind+1, start, mid, begInterval, endInterval);
    ans2 = segtreeQuery(tree, 2*ind+2, mid+1, end, begInterval, endInterval);
    //If one of the answers is invalid, return the other answer.
    if (!ans1.hasItem) return ans2;
    if (!ans2.hasItem) return ans1;
    //Otherwise, return the merge of the two answers.
    answer.hasItem = true, answer.item = segtreeMerge(ans1.item, ans2.item);
    return answer;
}
 
void segtreeUpdate(segtree *tree, item_length ind, item_length start, item_length end, item_length begInterval, item_length endInterval, item_type updateItem) {
    //The midpoint of this interval:
    item_length mid = (start+end)/2;
    //Update tree->list[ind] with any lazy updates.
    segtreeLazy(tree, ind, start, end);
    
    //Return if the update interval has no intersection with this interval or ind is outside of the tree.   
    if (begInterval > end || endInterval < start) return;
    //If this interval is completely inside the update interval, update tree->list[ind] with updateItem and propogate if there are children.
    if (start >= begInterval && end <= endInterval) {
        segtreeSingleUpdate(tree, ind, start, end, updateItem);
        if (start != end) segtreePropogate(tree, ind, updateItem);
    }
    //Otherwise, traverse both halves of the interval and update tree->list[ind] by merging the two children.
    else {
        segtreeUpdate(tree, 2*ind+1, start, mid, begInterval, endInterval, updateItem);
        segtreeUpdate(tree, 2*ind+2, mid+1, end, begInterval, endInterval, updateItem);
        tree->list[ind] = segtreeMerge(tree->list[2*ind+1], tree->list[2*ind+2]);
    }
}