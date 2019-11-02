/**
 * treap for C++
 * Documentation coming soon!
*/

#pragma once

#include <cstdio>
#include <cinttypes>
#include <cstdlib>
#include <limits>
#include <algorithm>

typedef int64_t num_items;

//Enable if you want nodes to collect the sum of values:
#define USE_SUM
//Enable if you want to use static rather than dynamic memory to allocate new treap nodes:
#define USE_STATIC

namespace treap {
    template <class item_key, class item_value> struct treap;
    
    template <class item_key, class item_value> struct node {
        item_key key;
        item_value value;
        item_key min;
        item_key max;
        num_items priority;
        num_items size;
        treap<item_key, item_value> left;
        treap<item_key, item_value> right;
#ifdef USE_SUM
        item_value sum;
#endif
    };
    
    template <class item_key, class item_value> struct treap_pair {
        treap<item_key, item_value> left;
        treap<item_key, item_value> right;
        treap_pair() : left(nullptr), right(nullptr) {};
    };
    
    template <class item_key, class item_value> treap<item_key, item_value> newTreapNode(item_key key, item_value value);
    
    template <class item_key, class item_value> struct treap {
        node<item_key, item_value> *root;
        treap() : root(nullptr) {}
        treap(node<item_key, item_value> *ptr) : root(ptr) {}
        
        template <class item_key_container, class item_value_container> treap(num_items numItems, item_key_container keyArr, item_value_container valueArr) {
            //Return an empty treap if there are no items:
            if (numItems == 0) {
                root = nullptr;
                return;
            }
            //Return a treap with one item if there is an item:
            if (numItems == 1) {
                root = nullptr;
                addElementByKey(*keyArr, *valueArr, false);
                return;
            }

            //Find where the median is located:
            num_items medianPos = numItems/2;
            //Build the left and right sides accordingly:
            treap<item_key, item_value> leftSide(medianPos, keyArr, valueArr);
            treap<item_key, item_value> rightSide(numItems-medianPos, keyArr+medianPos, valueArr+medianPos);
            //Merge the two treaps together:
            root = mergeTreaps(leftSide, rightSide).root;
        }
        
        num_items getSize() { return (root == nullptr) ? 0 : root->size; }
        item_key getMin() { return (root == nullptr) ? std::numeric_limits<item_key>::max() : root->min; }
        item_key getMax() { return (root == nullptr) ? std::numeric_limits<item_key>::min() : root->max; }
#ifdef USE_SUM
        item_value getSum() { return (root == nullptr) ? 0 : root->sum; }
#endif
        void updateProperties() {
            if (root != nullptr) {
                root->size = 1+root->left.getSize()+root->right.getSize();
                root->min = std::min(root->key, std::min(root->left.getMin(), root->right.getMin()));
                root->max = std::max(root->key, std::max(root->left.getMax(), root->right.getMax()));
#ifdef USE_SUM
                root->sum = root->value+root->left.getSum()+root->right.getSum();
#endif
            }
        }
        
        static treap<item_key, item_value> mergeTreaps(treap<item_key, item_value> left, treap<item_key, item_value> right) {
            if (left.root == nullptr) return right;
            if (right.root == nullptr) return left;
            if (left.root->priority > right.root->priority) {
                left.root->right = mergeTreaps(left.root->right, right);
                left.updateProperties();
                return left;
            } else {
                right.root->left = mergeTreaps(left, right.root->left);
                right.updateProperties();
                return right;
            }
        }
        
        //Split treap into a left-side with all elements less than or equal to key and a right-side with the rest of the elements.
        //Note that if exclusive is true, then left-side will have all elements less than key and right-side will have all elements greater than or equal to key.
        treap_pair<item_key, item_value> splitByKey(item_key key, bool exclusive) {
            treap_pair<item_key, item_value> answer;
            if (root == nullptr) return answer;

            //If key is less than or equal to the key of the root, then all items less than or equal to key are on the left-hand side.
            if (exclusive ? (key <= root->key) : (key < root->key)) {
                answer = root->left.splitByKey(key, exclusive);
                //Since answer.left is the tree with all elements up to key, make answer.right, which has all elements greater than key but less than the key of the root, the new left node of the treap:
                root->left = answer.right;
                //After making this modification, this becomes the right-side, which has all elements greater than key:
                answer.right = *this;
            }
            //If key is greater than key of the root, then we know that the left-side and the root is composed of all elements less than or equal to key, so we need to search the right-hand side for any other elements which are less than or equal to key.
            else {
                answer = root->right.splitByKey(key, exclusive);
                //Now, we need to combine this treap and its left-side with all of the elements in the right-side which are also less than or equal to key.
                //These elements are now in answer.left, so make answer.left the new right-side of treap:
                root->right = answer.left;
                //After making this modification, this becomes the left-side, which has all elements less than or equal to key:
                answer.left = *this;
            }
            updateProperties();
            return answer;
        }

#ifdef USE_SUM
        item_value getKeyRangeSum(item_key startKey, item_key endKey) {
            //Split the treap up into a left-side which has all elements up to endKey:
            treap_pair<item_key, item_value> parts = splitByKey(endKey, false);
            //Split that treap up into a left-side which has all elements up to startKey-1:
            treap_pair<item_key, item_value> parts2 = parts.left.splitByKey(startKey, true);
            //Get the sum of the elements greater than startKey, less than or equal to endKey:
            item_value result = parts2.right.getSum();
            //Merge the treaps back together:
            root = mergeTreaps(mergeTreaps(parts2.left, parts2.right), parts.right).root;
            return result;
        }
#endif

        bool addElementByKey(item_key newKey, item_value newValue, bool exclusive) {
            //Split treap up into a left-side with all elements less than newKey:
            treap_pair<item_key, item_value> parts = splitByKey(newKey, false);
            //Make sure newKey is not already in the tree:
            if (exclusive) {
                treap_pair<item_key, item_value> parts2 = parts.left.splitByKey(newKey, true);
                if (parts2.right.root != nullptr) {
                    root = mergeTreaps(mergeTreaps(parts2.left, parts2.right), parts.right).root;
                    return false;
                }
                parts.left = mergeTreaps(parts2.left, parts2.right);
            }

            //Create a new node:
            treap<item_key, item_value> storeTreap = newTreapNode<item_key, item_value>(newKey, newValue);
            //Put the new node to the right of the left-side, and then merge the new left-side with the right-side:
            root = mergeTreaps(mergeTreaps(parts.left, storeTreap), parts.right).root;

            return true;
        }

        bool removeElementByKey(item_key oldKey) {
            //Split treap up into a left-side which has all elements up to oldKey:
            treap_pair<item_key, item_value> parts = splitByKey(oldKey, false);
            //Now, split the left-side up into a left-side which has all elements before oldKey and a right-side which has all elements equal to oldKey:
            treap_pair<item_key, item_value> parts2 = parts.left.splitByKey(oldKey, true);
            //Record whether there were actually any elements with oldKey:
            bool actuallyRemoved = parts2.right.root != nullptr;
            //Merge treaps back together without the elements equal to oldKey:
            root = mergeTreaps(parts2.left, parts.right).root;

            return actuallyRemoved;
        }

        //Split treap into a left-side with the first pos elements and a right-side with the rest of the elements.
        treap_pair<item_key, item_value> splitByPos(num_items pos) {
            treap_pair<item_key, item_value> answer;
            if (this->root == nullptr) return answer;
            if (pos > getSize()) {
                answer.left = *this;
                return answer;
            }

            num_items leftSize = root->left.getSize();
            //If the left-side has pos elements or more, then the (pos-1)th element is on the left-side:
            if (pos <= leftSize) {
                answer = root->left.splitByPos(pos);
                //Since answer.left has all the elements up to the (pos-1)th element, make answer.right, the elements between the (pos-1)th element and the root, the new left node of the treap:
                root->left = answer.right;
                //After making this modification, treap1 becomes the right-side, which has all elements after the (pos-1)th one:
                answer.right = *this;
            }
            //Otherwise, we need to split the right-side up to look for the (pos-1)th element:
            else {
                //Notice that we subtract pos by the number of elements in the root and left-side:
                answer = root->right.splitByPos(pos-leftSize-1);
                //Now, in order to get all of the first pos elements, we need to combine treap1 and its left-side with all of the elements in the right-side.
                //These elements are now in answer.left, so make answer.left the new right-side of treap:
                root->right = answer.left;
                //After making this modification, treap1 becomes the left-side, which has all of the first pos elements:
                answer.left = *this;
            }
            updateProperties();
            return answer;
        }

#ifdef USE_SUM
        item_value getIntervalSum(num_items startPos, num_items endPos) {
            //Split the treap up into a left-side which has all elements up to endPos index:
            treap_pair<item_key, item_value> parts = splitByPos(endPos+1);
            //Split that treap up into a left-side which has all elements up to startPos-1 index:
            treap_pair<item_key, item_value> parts2 = parts.left.splitByPos(startPos);
            //Get the sum of the elements with index greater than startPos-1, less than or equal to endPos:
            item_value result = parts2.right.getSum();
            //Merge the treaps back together:
            root = mergeTreaps(mergeTreaps(parts2.left, parts2.right), parts.right).root;
            return result;
        }
#endif

        void addElementByPos(num_items newPos, item_key newKey, item_value newValue) {
            //Split treap up into a left-side with first pos elements:
            treap_pair<item_key, item_value> parts = splitByPos(newPos);
            //Create the new node:
            treap<item_key, item_value> storeTreap = newTreapNode<item_key, item_value>(newKey, newValue);
            //Put the new node to the right of the left-side, and then merge the new left-side with the right-side:
            root = mergeTreaps(mergeTreaps(parts.left, storeTreap), parts.right).root;
        }

        bool removeElementByPos(num_items oldPos) {
            //If the index is too big or too small, we can't remove it:
            if (oldPos+1 > getSize()) return false;
            if (oldPos < 0) return false;

            //Split treap up into a left-side which has the first (oldPos+1) elements:
            treap_pair<item_key, item_value> parts = splitByPos(oldPos+1);
            //Now, separate out the first oldPos elements from this left-side in order to isolate the (oldPos)th element:
            treap_pair<item_key, item_value> parts2 = parts.left.splitByPos(oldPos);
            //Merge treaps back together without the isolated element:
            root = mergeTreaps(parts2.left, parts.right).root;

            return true;
        }
        
        treap getNodeAtPos(num_items pos) {
            //If the index is too big or too small, we can't find its value:
            if (pos < 0) return nullptr;
            if (pos > getSize()) return nullptr;

            treap<item_key, item_value> curTreap = *this;
            //Keep looking for the treap whose root is the (pos)th element:
            while (curTreap.root->left.getSize() != pos) {
                //If the left subtree has less than pos elements, then the (pos)th element must be in the right subtree.
                //Also, adjust pos accordingly.
                if (curTreap.root->left.getSize() < pos) {
                    pos -= curTreap.root->left.getSize()+1;
                    curTreap = curTreap.root->right;
                }
                //Otherwise, the (pos)th element must be in the left subtree.
                else curTreap = curTreap.root->left;
                
                if (curTreap.root == nullptr) puts("Treap size values are corrupted"), exit(1);
            }
            //Finally, return the treap that we just found:
            return curTreap;
        }
    };
        
#ifdef USE_STATIC
    const num_items MAX_SPACE = 4000000;
    template <class item_key, class item_value> node<item_key, item_value> space[MAX_SPACE];
    template <class item_key, class item_value> num_items numSpaceUsed = 0;
    template <class item_key, class item_value> treap<item_key, item_value> newTreapNode(item_key key, item_value value) {
        if (numSpaceUsed<item_key, item_value> >= MAX_SPACE) puts("Ran out of treap node space"), exit(1);
 
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].priority = rand();
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].key = key;
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].value = value;
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].left = treap<item_key, item_value>();
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].right = treap<item_key, item_value>();
 
        treap<item_key, item_value> newNode(space<item_key, item_value>+numSpaceUsed<item_key, item_value>);
        newNode.updateProperties();
 
        numSpaceUsed<item_key, item_value>++;
        return newNode;
    }
#else
    template <class item_key, class item_value> treap<item_key, item_value> newTreapNode(item_key key, item_value value) {
        treap<item_key, item_value> newNode(new node<item_key, item_value>());
        newNode.root->priority = rand();
        newNode.root->key = key;
        newNode.root->value = value;
        newNode.root->left = treap<item_key, item_value>();
        newNode.root->right = treap<item_key, item_value>();
        newNode.updateProperties();
        return newNode;
    }
#endif

    //Used to initialize internal treap with empty items:
    template <class item_type> struct default_item {
        item_type operator*() { return item_type(); }
        default_item &operator+(int a) { return *this; }
    };  
}