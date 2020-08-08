/**
 * Wavelet tree for C++
 * Documentation coming soon!
*/

#pragma once

namespace wavelet_tree {
    typedef int64_t num_items;
    
    template<class num> struct tree {
        num minVal, maxVal;
        tree *leftChild, *rightChild;
        //itemsInLeftChild[i] denotes how many elements from arr[0..i] are in the leftChild of this wavelet tree
        //NOTE: arr[0..i] does not include arr[i]
        std::vector<num_items> itemsInLeftChild;

        template<class num_it> tree(num_it beginIt, num_it endIt, num minV, num maxV) {
            leftChild = nullptr;
            rightChild = nullptr;
            reconstruct(beginIt, endIt, minV, maxV);
        }

        //Reconstruct a wavelet tree to represent the elements [beginIt, endIt), where every element is in the interval [minVal, maxVal]          
        template<class num_it> void reconstruct(num_it beginIt, num_it endIt, num minV, num maxV) {
            //Before reconstructing the tree, delete any old children
            deleteOldChildren();
            
            minVal = minV, maxVal = maxV;
            itemsInLeftChild.clear();
            //If this node represents a bunch of items which have all the same value or this node represents an empty subarray, then this node is a leaf of the wavelet tree.
            if ((minVal == maxVal) || (beginIt >= endIt)) { 
                leftChild = nullptr;
                rightChild = nullptr;
                return;
            }
            
            itemsInLeftChild.reserve(endIt-beginIt+1);
            //Here, itemsInLeftChild[0] denotes the number of elements from beginIt[0..0] which are in the leftChild, which is obviously 0:
            itemsInLeftChild.push_back(0);
            
            num midVal = (minVal+maxVal)/2;
            for (num_it it = beginIt; it != endIt; ++it) {
                //Add 1 to this element in itemsInLeftChild if *it <= mid, i.e. if this element is going to be put in the left child
                itemsInLeftChild.push_back(itemsInLeftChild.back() + (*it <= midVal));
            }

            //Partition the elements so that all elements <= mid are on the left side and all elements > mid are on the right side
            //pivotIt points to the first element on the right side
            num_it pivotIt = std::stable_partition(beginIt, endIt, [midVal](num x) { return x <= midVal; });
            
            leftChild = new tree(beginIt, pivotIt, minVal, midVal);
            rightChild = new tree(pivotIt, endIt, midVal+1, maxVal);
        }

        //Find the kth smallest value in arr[leftIndex..rightIndex]
        //NOTE: leftIndex, rightIndex, k are 0-based, i.e. the smallest value is the 0th smallest value
        num kthSmallest(num_items leftIndex, num_items rightIndex, num_items k) {
            if (minVal == maxVal) return minVal;
            
            num_items leftIndexOfLeftChild = itemsInLeftChild[leftIndex];
            num_items rightIndexOfLeftChild = itemsInLeftChild[rightIndex];
            num_items itemsInLeftChild = rightIndexOfLeftChild-leftIndexOfLeftChild;
            if (k < itemsInLeftChild) {
                return leftChild->kthSmallest(leftIndexOfLeftChild, rightIndexOfLeftChild, k);
            } else {
                return rightChild->kthSmallest(leftIndex-leftIndexOfLeftChild, rightIndex-rightIndexOfLeftChild, k-itemsInLeftChild);
            }
        }

        //Count number of elements in arr[leftIndex..rightIndex] in the interval [queryMin, queryMax]
        num_items withinInterval(num_items leftIndex, num_items rightIndex, num queryMin, num queryMax, bool d = false) {
            //If this range of elements is empty or there is no overlap, return 0:
            if ((leftIndex >= rightIndex) || (queryMax < queryMin) || (queryMax < minVal) || (maxVal < queryMin)) return 0;
            //If there is only total overlap, return all elements:
            if ((queryMin <= minVal) && (maxVal <= queryMax)) return rightIndex-leftIndex;

            if ((leftChild != nullptr) && (leftChild->itemsInLeftChild.size() > 0) && (itemsInLeftChild.back()+1 != leftChild->itemsInLeftChild.size())) std::cout << "??? " << itemsInLeftChild.back() << " " << leftChild->itemsInLeftChild.size() << "\n", std::cout.flush();
            
            if (rightIndex >= itemsInLeftChild.size()) std::cerr << "OVERFLOW: " << rightIndex << " " << itemsInLeftChild.size() << "\n", std::cerr.flush();

            num_items leftIndexOfLeftChild = itemsInLeftChild[leftIndex];
            num_items rightIndexOfLeftChild = itemsInLeftChild[rightIndex];
            
            if (d) std::cout << leftIndex << " " << rightIndex << " | " << leftIndexOfLeftChild << " " << rightIndexOfLeftChild << " | " << itemsInLeftChild.back() << " " << itemsInLeftChild.size() << "\n", std::cout.flush();
            
            return leftChild->withinInterval(
                leftIndexOfLeftChild, rightIndexOfLeftChild, queryMin, queryMax
            )+rightChild->withinInterval(
                leftIndex-leftIndexOfLeftChild, rightIndex-rightIndexOfLeftChild, queryMin, queryMax
            );
        }

        void deleteOldChildren() {
            if (leftChild != nullptr) delete leftChild;
            if (rightChild != nullptr) delete rightChild;
        }
        
        ~tree() {
            deleteOldChildren();
        }
    };
}