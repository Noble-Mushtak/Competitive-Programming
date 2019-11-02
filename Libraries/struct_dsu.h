/**
 * struct dsu (and others) for C++
 *
 * typedefs:
 * item: Type of item held in disjoint-set union.
 * item_rank: The rank of an element.
 * * If the dsu is seen as a tree based off each element's parent, then the rank of an element is the height of the tree starting at that element.
 * dsu_info: The info associated with an element: its parent and its rank.
 *
 * Properties:
 * dsu_info *allInfo: The info associated with all elements in the dsu.
 *
 * Methods:
 * void initialize(item x)
 * * Initializes the element x in the dsu.
 * item find(item x)
 * * Finds the root of a certain element.
 * void join(item x, item y)
 * * Combines the sets that contain x and y
*/

#pragma once

#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#define REP(token, num) for (token = 0; token < num; token++)

namespace dsu {
    typedef int64_t item;
    typedef int64_t item_rank;
    typedef int64_t num_items;
    
    struct dsu_info {
        item parent;
        item_rank rank;
    };
    
    struct dsu {
        const static num_items MAX_ITEMS = 10000;
        dsu_info allInfo[MAX_ITEMS];

        dsu() {}
        dsu(num_items numItems) {
            item x;
            REP(x, numItems) initialize(x);
        }

        void initialize(item x) {
            allInfo[x].parent = x;
            allInfo[x].rank = 0;
        }
        
        item find(item x) {
            if (allInfo[x].parent != x) allInfo[x].parent = find(allInfo[x].parent);
            return allInfo[x].parent;
        }

        void join(item x, item y) {
            item xRoot = find(x), yRoot = find(y);
            if (xRoot == yRoot) return;

            if (allInfo[xRoot].rank < allInfo[yRoot].rank) allInfo[xRoot].parent = yRoot;
            else if (allInfo[yRoot].rank < allInfo[xRoot].rank) allInfo[yRoot].parent = xRoot;
            else {
                allInfo[yRoot].parent = xRoot;
                allInfo[xRoot].rank += 1;
            }
        }
    };
}