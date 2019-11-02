/**
 * struct quadtree (and others) for C
 * Example of how NOT to do a 2D segment tree: O((R+C)*log(RC)) updates and queries!
 * Documentation coming soon!
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
typedef struct quadtree {
    item_type list[5000000];
    item_container lazy[5000000];
    item_length size;
    item_length intervalMin1;
    item_length intervalMax1;
    item_length intervalMin2;
    item_length intervalMax2;
} quadtree;

static inline item_type quadtreeMerge(item_type item1, item_type item2) {
    //Merge items by adding them together
    return item1+item2;
}

static inline void quadtreeSingleUpdate(quadtree *tree, item_length ind, item_length start1, item_length end1, item_length start2, item_length end2, item_type updateItem) {
    //Update intervals by incrementing them by updateItem times the number of elements an interval has
    tree->list[ind] += (end1-start1+1)*(end2-start2+1)*updateItem;
}

static inline void quadtreePropogate(quadtree *tree, item_length ind, item_type updateItem) {
    item_length i;
    //Propogate to all four childs
    for (i = 0; i < 4; i++) {
        //If there is no lazy update, then initialize the lazy update.
        if (!tree->lazy[4*ind+i+1].hasItem) tree->lazy[4*ind+i+1].item = updateItem, tree->lazy[4*ind+i+1].hasItem = true;
        //Otherwise, merge the two updates together.
        else tree->lazy[4*ind+i+1].item = quadtreeMerge(tree->lazy[4*ind+i+1].item, updateItem);
   }
}

static inline void quadtreeLazy(quadtree *tree, item_length ind, item_length start1, item_length end1, item_length start2, item_length end2) {
    //If there is a lazy update:
    if (tree->lazy[ind].hasItem) {
        //Update tree->list[ind] with tree->lazy[ind].item.
        quadtreeSingleUpdate(tree, ind, start1, end1, start2, end2, tree->lazy[ind].item);
        //Propogate the update if tree->list[ind] has children.
        if (start1 != end1 || start2 != end2) quadtreePropogate(tree, ind, tree->lazy[ind].item);
        //Erase this lazy update.
        tree->lazy[ind].hasItem = false;
    }
}
 
void quadtreeInit(quadtree *tree, item_length ind, item_length start1, item_length end1, item_length start2, item_length end2, item_type *items, item_length yDimension) {
    //The midpoint of the two intervals (one for each dimension):
    item_length mid1 = (start1+end1)/2, mid2 = (start2+end2)/2, i;
    //This tells us if a child is empty and if tree->list[ind] has been set yet:
    bool empty[4] = {true, true, true, true}, setInd = false;
    
    //Remember to set .interval* properties at the beginning:
    if (!ind) tree->intervalMin1 = start1, tree->intervalMax1 = end1, tree->intervalMin2 = start2, tree->intervalMax2 = end2;
    //If this initialization makes us go beyond the size of tree->list, print an error message and exit the program:
    if (ind >= tree->size) puts("QUADTREE DOES NOT HAVE ENOUGH SPACE. ABORT!!!"), exit(1);
    //Clear array of lazy items:
    tree->lazy[ind].hasItem = false;
    
    //If the interval is only one point, then return the value of items at that point:
    if ((start1 == end1) && (start2 == end2)) {
        tree->list[ind] = (item_type)(*((items+start1*yDimension)+start2));
        return;
    }

    //Check if each child is non-empty and if they are, do the recursive call:
    //Left-left:
    if (start1 <= mid1 && start2 <= mid2) {
        empty[0] = false;
        quadtreeInit(tree, 4*ind+1, start1, mid1, start2, mid2, items, yDimension);
    }
    //Left-right:
    if (start1 <= mid1 && mid2+1 <= end2) {
        empty[1] = false;
        quadtreeInit(tree, 4*ind+2, start1, mid1, mid2+1, end2, items, yDimension);
    }
    //Right-left:
    if (mid1+1 <= end1 && start2 <= mid2) {
        empty[2] = false;
        quadtreeInit(tree, 4*ind+3, mid1+1, end1, start2, mid2, items, yDimension);
    }
    //Right-right:
    if (mid1+1 <= end1 && mid2+1 <= end2) {
        empty[3] = false;
        quadtreeInit(tree, 4*ind+4, mid1+1, end1, mid2+1, end2, items, yDimension);
    }
    //Merge all of the non-empty children together:
    for (i = 0; i < 4; i++) if (!empty[i]) {
        //If tree->list[ind] has not been set yet, set it:
        if (!setInd) tree->list[ind] = tree->list[4*ind+i+1], setInd = true;
        //Otherwise, merge it with this child:
        else tree->list[ind] = quadtreeMerge(tree->list[ind], tree->list[4*ind+i+1]);
    }
}
 
item_container quadtreeQuery(quadtree *tree, item_length ind, item_length start1, item_length end1, item_length start2, item_length end2, item_length begInterval1, item_length endInterval1, item_length begInterval2, item_length endInterval2) {
    //The answer for this interval and the array of answers for all four children:
    item_container answer = { .hasItem = false }, childAnswers[4];
    //The midpoint of the two intervals (one for each dimension):
    item_length mid1 = (start1+end1)/2, mid2 = (start2+end2)/2, i;

    //Return if this interval is empty.
    if (start1 > end1 || start2 > end2) return answer;
    //Update tree->list[ind] with any lazy updates.
    quadtreeLazy(tree, ind, start1, end1, start2, end2);
    //Return if the update interval has no intersection with this interval.   
    if (begInterval1 > end1 || endInterval1 < start1 || begInterval2 > end2 || endInterval2 < start2) return answer;
    
    //If this interval is completely inside the query interval, simply return tree->list[ind]:
    if (start1 >= begInterval1 && end1 <= endInterval1 && start2 >= begInterval2 && end2 <= endInterval2) {
        answer.hasItem = true, answer.item = tree->list[ind];
        return answer;
    }

    //If none of the cases above apply, traverse all four children:
    //Left-left:
    childAnswers[0] = quadtreeQuery(tree, 4*ind+1, start1, mid1, start2, mid2, begInterval1, endInterval1, begInterval2, endInterval2);
    //Left-right:
    childAnswers[1] = quadtreeQuery(tree, 4*ind+2, start1, mid1, mid2+1, end2, begInterval1, endInterval1, begInterval2, endInterval2);
    //Right-left:
    childAnswers[2] = quadtreeQuery(tree, 4*ind+3, mid1+1, end1, start2, mid2, begInterval1, endInterval1, begInterval2, endInterval2);
    //Right-right:
    childAnswers[3] = quadtreeQuery(tree, 4*ind+4, mid1+1, end1, mid2+1, end2, begInterval1, endInterval1, begInterval2, endInterval2);
    //Merge all of the non-empty children together:
    for (i = 0; i < 4; i++) if (childAnswers[i].hasItem) {
        //If answer.item has not been set yet, set it:
        if (!answer.hasItem) answer.item = childAnswers[i].item, answer.hasItem = true;
        //Otherwise, merge it with this child:
        else answer.item = quadtreeMerge(answer.item, childAnswers[i].item);
    }
    return answer;
}
 
void quadtreeUpdate(quadtree *tree, item_length ind, item_length start1, item_length end1, item_length start2, item_length end2, item_length begInterval1, item_length endInterval1, item_length begInterval2, item_length endInterval2, item_type updateItem) {
    //The midpoint of the two intervals (one for each dimension):
    item_length mid1 = (start1+end1)/2, mid2 = (start2+end2)/2, i;
    //This tells us if a child is empty and if tree->list[ind] has been set yet:
    bool empty[4] = {true, true, true, true}, setInd = false;
    
    //Return if this interval is empty.
    if (start1 > end1 || start2 > end2) return;
    //Update tree->list[ind] with any lazy updates.
    quadtreeLazy(tree, ind, start1, end1, start2, end2);
    //Return if the update interval has no intersection with this interval.   
    if (begInterval1 > end1 || endInterval1 < start1 || begInterval2 > end2 || endInterval2 < start2) return;
    
    //If this interval is completely inside the update interval, update tree->list[ind] with updateItem and propogate if there are children.
    if (start1 >= begInterval1 && end1 <= endInterval1 && start2 >= begInterval2 && end2 <= endInterval2) {
        quadtreeSingleUpdate(tree, ind, start1, end1, start2, end2, updateItem);
        if (start1 != end1 || start2 != end2) quadtreePropogate(tree, ind, updateItem);
    }
    //Otherwise, traverse all four children and update tree->list[ind] by merging the non-empty children.
    else {
        //Check if each child is non-empty and if they are, do the recursive call:
        //Left-left:
        if (start1 <= mid1 && start2 <= mid2) {
            empty[0] = false;
            quadtreeUpdate(tree, 4*ind+1, start1, mid1, start2, mid2, begInterval1, endInterval1, begInterval2, endInterval2, updateItem);
        }
        //Left-right:
        if (start1 <= mid1 && mid2+1 <= end2) {
            empty[1] = false;
            quadtreeUpdate(tree, 4*ind+2, start1, mid1, mid2+1, end2, begInterval1, endInterval1, begInterval2, endInterval2, updateItem);
        }
        //Right-left:
        if (mid1+1 <= end1 && start2 <= mid2) {
            empty[2] = false;
            quadtreeUpdate(tree, 4*ind+3, mid1+1, end1, start2, mid2, begInterval1, endInterval1, begInterval2, endInterval2, updateItem);
        }
        //Right-right:
        if (mid1+1 <= end1 && mid2+1 <= end2) {
            empty[3] = false;
            quadtreeUpdate(tree, 4*ind+4, mid1+1, end1, mid2+1, end2, begInterval1, endInterval1, begInterval2, endInterval2, updateItem);
        }
        //Merge all of the non-empty children together:
        for (i = 0; i < 4; i++) if (!empty[i]) {
            //If tree->list[ind] has not been set yet, set it:
            if (!setInd) tree->list[ind] = tree->list[4*ind+i+1], setInd = true;
            //Otherwise, merge it with this child:
            else tree->list[ind] = quadtreeMerge(tree->list[ind], tree->list[4*ind+i+1]);
        }
    }
}