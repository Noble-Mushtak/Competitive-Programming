/**
 * n-dimensional range tree for C++
 * Documentation coming soon!
*/

#pragma once

#include <cstdio>
#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <array>
#include <algorithm>
#include <vector>

//Enable if you want to record the level of each node in the BST:
//#define USE_LEVEL
//Enable if you want to use static rather than dynamic memory to allocate new BST nodes:
#define USE_STATIC

typedef int64_t num_items;

namespace bst {
    template <class item_key, class item_value> struct bst;
    
    template <class item_key, class item_value> struct node {
        item_key key;
        item_value value;
        item_key min;
        item_key max;
        num_items priority;
        num_items size;
        bst<item_key, item_value> left;
        bst<item_key, item_value> right;
#ifdef USE_LEVEL
        num_items level;
#endif
    };
    
    template <class item_key, class item_value> bst<item_key, item_value> newBstNode(item_key key, item_value value);
    
    template <class item_key, class item_value> struct bst {
        node<item_key, item_value> *root;
        bst() : root(nullptr) {}
        bst(node<item_key, item_value> *ptr) : root(ptr) {}
        
        template <class item_key_container, class item_value_container> bst(num_items numItems, item_key_container keyArr, item_value_container valueArr) {
            //Return an empty bst if there are no items:
            if (numItems == 0) {
                root = nullptr;
                return;
            }
            
            //Find where the median is located:
            num_items medianPos = numItems/2;
            //Create a new node out of the median:
            root = newBstNode(keyArr[medianPos], valueArr[medianPos]).root;
            //Build the left and right sides accordingly:
            root->left = bst<item_key, item_value>(medianPos, keyArr, valueArr);
            root->right = bst<item_key, item_value>(numItems-medianPos-1, keyArr+medianPos+1, valueArr+medianPos+1);
            //Given the new child nodes, update the bst's properties:
            updateProperties();
        }
        
        num_items getSize() { return (root == nullptr) ? 0 : root->size; }
        item_key getMin() { return (root == nullptr) ? std::numeric_limits<item_key>::max() : root->min; }
        item_key getMax() { return (root == nullptr) ? std::numeric_limits<item_key>::min() : root->max; }
#ifdef USE_LEVEL
        num_items getLevel() { return (root == nullptr) ? 0 : root->level; }
#endif
        void updateProperties() {
            if (root != nullptr) {
                root->size = 1+root->left.getSize()+root->right.getSize();
                root->min = std::min(root->key, std::min(root->left.getMin(), root->right.getMin()));
                root->max = std::max(root->key, std::max(root->left.getMax(), root->right.getMax()));
#ifdef USE_LEVEL
                root->level = 1+std::max(root->left.getLevel(), root->right.getLevel());
#endif
            }
        }
    };
        
#ifdef USE_STATIC
    const num_items MAX_SPACE = 4000000;
    template <class item_key, class item_value> node<item_key, item_value> space[MAX_SPACE];
    template <class item_key, class item_value> num_items numSpaceUsed = 0;
    template <class item_key, class item_value> bst<item_key, item_value> newBstNode(item_key key, item_value value) {
        if (numSpaceUsed<item_key, item_value> >= MAX_SPACE) puts("Ran out of bst node space"), exit(1);
 
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].priority = rand();
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].key = key;
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].value = value;
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].left = bst<item_key, item_value>();
        space<item_key, item_value>[numSpaceUsed<item_key, item_value>].right = bst<item_key, item_value>();
 
        bst<item_key, item_value> newNode(space<item_key, item_value>+numSpaceUsed<item_key, item_value>);
        newNode.updateProperties();
 
        numSpaceUsed<item_key, item_value>++;
        return newNode;
    }
#else
    template <class item_key, class item_value> bst<item_key, item_value> newBstNode(item_key key, item_value value) {
        bst<item_key, item_value> newNode(new node<item_key, item_value>());
        newNode.root->priority = rand();
        newNode.root->key = key;
        newNode.root->value = value;
        newNode.root->left = bst<item_key, item_value>();
        newNode.root->right = bst<item_key, item_value>();
        newNode.updateProperties();
        return newNode;
    }
#endif

    //Used to initialize internal bst with empty items:
    template <class item_type> struct default_item {
        item_type operator*() { return item_type(); }
        default_item &operator+(int a) { return *this; }
        item_type operator[](int a) { return item_type(); }
    };
    
    //Binary search function used to find least element >= some item in a sorted array
    //Returns numItems when all elements are < query
    template <class item_type, class item_type_container> num_items findBegin(num_items numItems, item_type_container itemArr, item_type query) {
        num_items left = 0, right = numItems;
        while (left < right) {
            num_items mid = (left+right)/2;
            if (itemArr[mid] < query) left = mid+1;
            else right = mid;
        }
        return left;
    }
    
    //Binary search function used to find least element > some item in a sorted array
    //Returns numItems when all elements are <= query
    template <class item_type, class item_type_container> num_items findEnd(num_items numItems, item_type_container itemArr, item_type query) {
        num_items left = 0, right = numItems;
        while (left < right) {
            num_items mid = (left+right)/2;
            if (itemArr[mid] <= query) left = mid+1;
            else right = mid;
        }
        return left;
    }
}

namespace range_tree {
    //Used with std::sort to sort a bunch of dim-dimensional points by a single coordinate.
    template<class item_type, size_t dimension, size_t coord> struct compare_by_coord {
        static bool lessThan(const std::array<item_type, dimension> &point1, const std::array<item_type, dimension> &point2) {
             for (size_t i = 0; i < dimension; i++) {
                 size_t indexToBeExamined = (coord+i) % dimension;
                 if (point1[indexToBeExamined] != point2[indexToBeExamined]) return point1[indexToBeExamined] < point2[indexToBeExamined];
             }
             return false;
        }
        
        bool operator()(const std::array<item_type, dimension> &point1, const std::array<item_type, dimension> &point2) { return lessThan(point1, point2); }
    };

    //Used to pretend that an array of points is actually an array of coordinates.
    //Helpful for building bsts.
    template<class item_type, size_t dimension, size_t coord> struct mock_coordinate_array {
        std::array<item_type, dimension> *ptr;
        mock_coordinate_array(std::array<item_type, dimension> *p) : ptr(p) {}
        item_type operator*() { return (*ptr)[coord]; }
        mock_coordinate_array operator+(int offset) { return ptr+offset; }
        item_type operator[](int offset) { return ptr[offset][coord]; }
    };
    
    //Used to pretend that an array of points is actually an array of points paired with an empty bst.
    //Helpful for building bsts.
    template<class point, class bst> struct mock_pair_array {
        point *ptr;
        mock_pair_array(point *p) : ptr(p) {}
        std::pair<point, bst> operator*() { return std::pair<point, bst>(*ptr, bst()); }
        mock_pair_array operator+(int offset) { return ptr+offset; }
        std::pair<point, bst> operator[](int offset) { return std::pair<point, bst>(ptr[offset], bst()); }
    };

    //Object that stores point along with pointers.
    //Used for fractional cascading.
    template<class point> struct point_info {
        point val;
        point_info() {}
        point_info(point item) : val(item), left(-1), right(-1) {}
        num_items left, right;
    };

    //Used to pretend that an array of point_infos are actually an array of coordinates.
    //Used for binary search.
    template<class item_type, size_t dimension, size_t coord> struct mock_coordinate_array_from_info {
        point_info<std::array<item_type, dimension>> *ptr;
        mock_coordinate_array_from_info(point_info<std::array<item_type, dimension>> *p) : ptr(p) {}
        item_type operator*() { return (*ptr).val[coord]; }
        mock_coordinate_array_from_info operator+(int offset) { return ptr+offset; }
        item_type operator[](int offset) { return ptr[offset].val[coord]; }
    };

    //subtree<item_type, dim, lev> is a lev-dimensional range tree on a set of dim-dimensional vectors.
    //Most range trees start as subtree<item_type, dim, dim>, which contains a bunch of subtree<item_type, dim, dim-1>, each of which contains a bunch of subtree<item_type, dim, dim-2>, etc. until we get down to subtree<item_type, dim, 2>
    //Note that lev-dimensional range trees has not yet been implemented for lev > 2.
    template<class item_type, size_t dimension, size_t level> struct subtree {
        bst::bst<item_type, subtree<item_type, dimension, level-1>> internalTree;
    };

    //Alias so people can just use tree<item_type, dim> instead of subtree<item_type, dim, dim>
    template <class item_type, size_t dimension> using tree = subtree<item_type, dimension, dimension>;

    template<class item_type, size_t dimension> struct subtree<item_type, dimension, 2> {
        typedef std::array<item_type, dimension> point;
        typedef std::vector<point_info<point>> info_array;
        typedef std::pair<point, info_array> item_value;
        typedef bst::bst<item_type, item_value> internal_tree_type;
        internal_tree_type internalTree;

        static constexpr int MAX_SPACE = 2000000;
        static point pointStorageSpace[MAX_SPACE];
        
        subtree(num_items numItems, point *points) {
            //Sort by the (dimension-2) coordinate:
            std::sort(points, points+numItems, compare_by_coord<item_type, dimension, dimension-2>());

            //Make sure all points are unique:
            /* for (num_items i = 1; i < numItems; i++) {
                size_t j = 0;
                for (; j < dimension; j++) {
                    if (points[i-1][j] != points[i][j]) break;
                }
                if (j == dimension) puts("Not all points are unique"), exit(1);
            } // */
            
            //Build the bst by using these unique coordinates as the keys:
            internalTree = internal_tree_type(numItems, mock_coordinate_array<item_type, dimension, dimension-2>(points), mock_pair_array<point, info_array>(points));
            
            //Sort by the (dimension-1) coordinate:
            std::sort(points, points+numItems, compare_by_coord<item_type, dimension, dimension-1>());
            //Build the 1D range trees:
            buildNode(internalTree, numItems, points);
        }

        void buildNode(internal_tree_type node, num_items numItems, point *points) {
            if (numItems != node.getSize()) puts("Something wrong happened with sizes. Make sure all points are unique."), exit(1);
            if (node.root == nullptr) return;

            //Build the 1D range tree:
            node.root->value.second = info_array(numItems);
            for (num_items i = 0; i < numItems; i++) node.root->value.second[i] = point_info<point>(points[i]);
            //These pointers will help us update the left and right properties in the point_info array:
            num_items locInInfoArrLeft = 0, locInInfoArrRight = 0;
            
            //Put the points that should go into the left and right children into pointStorageSpace.
            num_items numLessThanRoot = 0, numGreaterThanRoot = 0;
            for (num_items i = 0; i < numItems; i++) {
                //Left child:
                if (compare_by_coord<item_type, dimension, dimension-2>::lessThan(points[i], node.root->value.first)) {
                     pointStorageSpace[numLessThanRoot++] = points[i];
                     //Update the info array so that infoArray[j].left points to the least element with (dimension-1) coordinate >= infoArray[j].val[dimension-1]
                     for (; locInInfoArrLeft < numItems; locInInfoArrLeft++) {
                         if (points[i][dimension-1] >= node.root->value.second[locInInfoArrLeft].val[dimension-1]) node.root->value.second[locInInfoArrLeft].left = numLessThanRoot-1;
                         else break;
                     }
                }

                //Right child:
                else if (compare_by_coord<item_type, dimension, dimension-2>::lessThan(node.root->value.first, points[i])) {
                     pointStorageSpace[node.root->left.getSize()+(numGreaterThanRoot++)] = points[i];
                     //Update the info array so that infoArray[j].right points to the least element with (dimension-1) coordinate >= infoArray[j].val[dimension-1]
                     for (; locInInfoArrRight < numItems; locInInfoArrRight++) {
                         if (points[i][dimension-1] >= node.root->value.second[locInInfoArrRight].val[dimension-1]) node.root->value.second[locInInfoArrRight].right = numGreaterThanRoot-1;
                         else break;
                     }
                }
            }
            //Update the rest of the lefts with numLessThanRoot (this acts as a null pointer, meaning there are no elements with (dimension-1) coordinate >= infoArray[j])
            for (; locInInfoArrLeft < numItems; locInInfoArrLeft++) node.root->value.second[locInInfoArrLeft].left = numLessThanRoot;
            //Do the same thing for the rights:
            for (; locInInfoArrRight < numItems; locInInfoArrRight++) node.root->value.second[locInInfoArrRight].right = numGreaterThanRoot;
            
            //Copy pointStorageSpace back into points:
            memcpy(points, pointStorageSpace, (numLessThanRoot+numGreaterThanRoot)*sizeof(point));
            //Build the children nodes:
            buildNode(node.root->left, numLessThanRoot, points);
            buildNode(node.root->right, numGreaterThanRoot, points+numLessThanRoot);
        }
        
        num_items countPointsInRange(point minPoint, point maxPoint) {
            return getPointsInRange(nullptr, minPoint, maxPoint);
        }
        
        num_items getPointsInRange(point *points, point minPoint, point maxPoint) {
            //Find the points which are within the (dimension-1) interval of this query:
            num_items begin = bst::findBegin(internalTree.getSize(), mock_coordinate_array_from_info<item_type, dimension, dimension-1>(internalTree.root->value.second.data()), minPoint[dimension-1]);
            num_items end = bst::findEnd(internalTree.getSize(), mock_coordinate_array_from_info<item_type, dimension, dimension-1>(internalTree.root->value.second.data()), maxPoint[dimension-1]);
            
            //Start traversing the tree in order to look for points within the query:
            return getPointsInRangeAtNode(internalTree, points, minPoint, maxPoint, begin, end);
        }
        
        num_items getPointsInRangeAtNode(internal_tree_type node, point *points, point minPoint, point maxPoint, num_items begin, num_items end) {
            if (node.root == nullptr) return 0;
            
            //Get the start and end coordinates for both the (dimension-2) and (dimension-1) coordinates:
            item_type startCoord = minPoint[dimension-2], startCoord2 = minPoint[dimension-1];
            item_type endCoord = maxPoint[dimension-2], endCoord2 = maxPoint[dimension-1];
            //If the query interval is out of range of this node, return 0:
            if (startCoord > node.getMax()) return 0;
            if (endCoord < node.getMin()) return 0;
            
            //If the (dimension-1) interval is empty, return 0:
            if (begin == end) return 0;
            //If the node's (dimension-2) interval is entirely within the query interval, return the number of nodes in the (dimension-1) interval:
            if ((startCoord <= node.getMin()) && (endCoord >= node.getMax())) {
                if (points != nullptr) {
                    for (num_items i = begin; i < end; i++) points[i-begin] = node.root->value.second[i].val;
                }
                return end-begin;
            }
            
            //This stores the number of items which will be stored in points according to the query:
            num_items result = 0;
            
            //Calculate whether or not the root point is within the query interval.
            //Note that only (dimension-2) and (dimension-1) coordinates are taken into account when making this decision.
            size_t i;
            for (i = dimension-2; i < dimension; i++) {
                if ((minPoint[i] > node.root->value.first[i]) || (maxPoint[i] < node.root->value.first[i])) break;
            }
            //If it is, then add it to the results
            if (i == dimension) {
                if (points != nullptr) points[result] = node.root->value.first;
                result++;
            }
            
            //Get the two pointers needed to do the child query:
            num_items leftBegin = (begin == node.getSize()) ? node.root->left.getSize() : node.root->value.second[begin].left;
            num_items leftEnd = (end == node.getSize()) ? node.root->left.getSize() : node.root->value.second[end].left;
            num_items rightBegin = (begin == node.getSize()) ? node.root->right.getSize() : node.root->value.second[begin].right;
            num_items rightEnd = (end == node.getSize()) ? node.root->right.getSize() : node.root->value.second[end].right;

            //Traverse the child on the left:
            result += getPointsInRangeAtNode(node.root->left, (points == nullptr) ? nullptr : points+result, minPoint, maxPoint, leftBegin, leftEnd);
            //Finally, traverse the child on the right:
            result += getPointsInRangeAtNode(node.root->right, (points == nullptr) ? nullptr : points+result, minPoint, maxPoint, rightBegin, rightEnd);
            return result;
        }
    };
    
    template<class item_type, size_t dimension> std::array<item_type, dimension> subtree<item_type, dimension, 2>::pointStorageSpace[subtree<item_type, dimension, 2>::MAX_SPACE];
}