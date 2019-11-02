/**
 * linked_list for C++
 * Documentation coming soon!
 * 
 * typedefs:
 * num_items: Type of list length in linked_list.
*/

#pragma once

#include <cstdio>
#include <cstdlib>

typedef int64_t num_items;

namespace linked_list {
    template <class item_type> struct node {
        struct node *prev, *next;
        item_type val;
    };

    const num_items MAX_SPACE = 1000000;
    template <class item_type> node<item_type> space[MAX_SPACE];
    template <class item_type> num_items numSpaceUsed;
    template <class item_type> node<item_type> *newNode(item_type value) {
         if (numSpaceUsed<item_type> >= MAX_SPACE) puts("Not enough node space"), exit(1);
         node<item_type> *newNode = space<item_type>+numSpaceUsed<item_type>;
         numSpaceUsed<item_type>++;
         newNode->prev = newNode->next = nullptr;
         newNode->val = value;
         return newNode;
    }
    
    template <class item_type> void linkNodes(node<item_type> *node1, node<item_type> *node2) {
        if (node2 != nullptr) node2->prev = node1;
        if (node1 != nullptr) node1->next = node2;
    }
    
    template <class item_type> struct list {
        node<item_type> *beg, *end;
        num_items size;
        list() : beg(nullptr), end(nullptr), size(0) {}
        
        void appendNode(node<item_type> *node) {
            if (beg == nullptr) beg = end = node;
            else {
                linkNodes(end, node);
                end = node;
            }
            size++;
        }
        void prependNode(node<item_type> *node) {
            if (beg == nullptr) beg = end = node;
            else {
                linkNodes(node, beg);
                beg = node;
            }
            size++;
        }
        
        void removeNode(node<item_type> *node) {
            if (beg == node) beg = node->next;
            if (end == node) end = node->prev;
            linkNodes(node->prev, node->next);
            size--;
        }
        
        node<item_type> *popLeftNode() {
            node<item_type> *bottom = beg;
            if (bottom != nullptr) removeNode(bottom);
            return bottom;
        }
        node<item_type> *popNode() {
            node<item_type> *top = end;
            if (top != nullptr) removeNode(top);
            return top;
        }
    };
}