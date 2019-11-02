/**
 * struct binary_tree (and others) for C
 * 
 * typedefs:
 * item_type: Type of item held by binary_tree.
 * 
 * Properties:
 * item_type top: Item held by binary_tree.
 * binary_tree_ref leftNode: Reference to binary_tree on left.
 * binary_tree_ref rightNode: Reference to binary_tree on right.
 * 
 * Functions:
 * binary_tree* initTree(binary_tree *tree, item_type topElem)
 * * Initializes tree with topElem as only element and returns pointer to tree. If tree is NULL, then tree will be dynamically allocated.
 * bool findNode(const binary_tree *tree, item_type elem)
 * * Returns true iff tree holds elem (returns false otherwise).
 * bool insertNode(binary_tree *tree, item_type newElem)
 * * Returns true iff newElem was not in tree and has been added in (returns false otherwise).
*/

#pragma once

#include <stdbool.h>

typedef int64_t item_type;
typedef struct binary_tree {
    item_type top;
    struct binary_tree *leftNode;
    struct binary_tree *rightNode;
} binary_tree;

binary_tree* initTree(binary_tree *tree, item_type topElem) {
    //If tree is NULL, allocate it.
    if (tree == NULL) tree = malloc(sizeof(binary_tree));
    //Set the top of the tree
    tree->top = topElem;
    //Set the .leftNode and .rightNode to empty NULL trees
    tree->leftNode = tree->rightNode = NULL;
    //Return tree back
    return tree;
}

bool findNode(const binary_tree *tree, item_type elem) {
    //Return false if there's nowhere else to look.
    if (tree == NULL) return false;
    //Return true if found.
    else if (tree->top == elem) return true;
    //Otherwise, traverse tree further.
    else if (tree->top > elem) return findNode(tree->leftNode, elem);
    else if (tree->top < elem) return findNode(tree->rightNode, elem);
}

bool insertNode(binary_tree *tree, item_type newElem) {
    //Return false is element already exists
    if (tree->top == newElem) return false;
    //Otherwise:
    else if (tree->top > newElem) {
        //If there's nowhere else to look, insert newElem.
        if (tree->leftNode == NULL) {
            tree->leftNode = initTree(tree->leftNode, newElem);
            return true;
        }
        //Otherwise, traverse further
        else return insertNode(tree->leftNode, newElem);
    }
    //Do a similar thing as above for .rightNode if newElem is greater than tree->top
    else if (tree->top < newElem) {
        if (tree->rightNode == NULL) {
            tree->rightNode = initTree(tree->rightNode, newElem);
            return true;
        } else return insertNode(tree->rightNode, newElem);
    }
}