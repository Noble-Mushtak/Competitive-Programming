//Received Time Limit Exceeded verdict

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <limits>
#include <array>
#include <vector>

#define REP(token, num) for (token = 0; token < num; token++)

//Use -DDEBUG compiler flag if you want PRINTF(...) to print debug output, disable if you want PRINTF(...) to do nothing
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

//Enable if you want to record the level of each node in the BST:
//#define USE_LEVEL
//Enable if you want to use static rather than dynamic memory to allocate new BST nodes:
//#define USE_STATIC

typedef int32_t num_items;

//Use -DMEASURE_ALLOCATION compiler flag if you want time and allocation statistics to be outputted:
#ifdef MEASURE_ALLOCATION
num_items spaceAllocated = 0;
#endif

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
    const num_items MAX_SPACE = 4000010;
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

        subtree() {}
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
#ifdef MEASURE_ALLOCATION
            spaceAllocated += numItems;
#endif
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

typedef int32_t dimen;
struct rect {
    dimen minX, maxX, minY, maxY;
};
typedef int64_t num_rects;

const dimen MIN_X = -1, MIN_Y = -1, MAX_X = 3000000, MAX_Y = 3000000;
num_rects numRects = 0, answer = 0;
rect rectangles[1000010];
//Notice that these are 64-bit integers, even though the other dimensions are stored as 32-bit integers.
//This is because we use 32-bit integers to store the dimensions while answering queries in order to save space, but we read the dimensions in as 64-bit integers so we do not overflow when reading in numbers between -10^15 and 10^15.
int64_t minXs[1000010], minYs[1000010], maxXs[1000010], maxYs[1000010], xs[2000010], ys[2000010];
dimen compressed[2000010];
num_rects numCompressed;
std::array<dimen, 3> topLeftCorners[1000010], topRightCorners[1000010], bottomLeftCorners[1000010], bottomRightCorners[1000010];
range_tree::subtree<dimen, 3, 2> topLeftTree, topRightTree, bottomLeftTree, bottomRightTree;

#ifdef MEASURE_ALLOCATION
struct timespec programStart;
void printDiff(struct timespec start, struct timespec end) {
    uint64_t microseconds = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    if (microseconds < 2000) fprintf(stderr, "DEBUG: %lu microseconds\n", microseconds);
    else fprintf(stderr, "DEBUG: %lu milliseconds\n", microseconds/1000); 
}
#endif

void recordAllocation() {
#ifdef MEASURE_ALLOCATION
    fprintf(stderr, "DEBUG: %" PRId32 " %" PRIu64 "\n", spaceAllocated, spaceAllocated*sizeof(range_tree::point_info<std::array<dimen, 3>>));
    
    struct timespec curTime;
    clock_gettime(CLOCK_MONOTONIC_RAW, &curTime);
    printDiff(programStart, curTime);
#endif
}

char name[10000], inputLine[10000];

int main() {
    while (true) {
        fgets(name, 10000, stdin);
        if (feof(stdin)) break;
        
        num_rects i;
    #ifdef MEASURE_ALLOCATION
        clock_gettime(CLOCK_MONOTONIC_RAW, &programStart);
    #endif

        numRects = numCompressed = answer = 0;
        //Keep looping until we find an asterisk:
        while (true) {
            fgets(inputLine, 10000, stdin);
            if (inputLine[0] == '*') break;
            //Convert all of the tokens to numbers in the appropriate arrays:
            sscanf(inputLine, "%" PRId64 " %" PRId64 " %" PRId64 " %" PRId64, minXs+numRects, maxXs+numRects, minYs+numRects, maxYs+numRects);
            //Store all x-coordinates and y-coordinates in one array:
            xs[2*numRects] = minXs[numRects];
            xs[2*numRects+1] = maxXs[numRects];
            ys[2*numRects] = minYs[numRects];
            ys[2*numRects+1] = maxYs[numRects];
            //Increment number of rectangles:
            numRects++;
        }
        //Sort the x and y coordinate arrays:
        std::sort(xs, xs+(2*numRects));
        std::sort(ys, ys+(2*numRects));
        //Compress the x-coordinate array so that there is only one copy of each coordinate:
        REP(i, 2*numRects) {
            if ((i == 0) || (xs[i] != xs[i-1])) compressed[numCompressed++] = xs[i];
        }
        //Then, update the min/max arrays of the rectangles with compressed coordinates:
        REP(i, numRects) {
            minXs[i] = bst::findBegin(numCompressed, compressed, minXs[i]);
            maxXs[i] = bst::findBegin(numCompressed, compressed, maxXs[i]);
        }
        numCompressed = 0;
        //Repeat for y-coordinates:
        REP(i, 2*numRects) {
            if ((i == 0) || (ys[i] != ys[i-1])) compressed[numCompressed++] = ys[i];
        }
        REP(i, numRects) {
            minYs[i] = bst::findBegin(numCompressed, compressed, minYs[i]);
            maxYs[i] = bst::findBegin(numCompressed, compressed, maxYs[i]);
        }

        REP(i, numRects) {
            //Store all of the corners.
            //The first dimension is a unique identifier so that two rectangles that share corners can be distinguished from each other.
            topLeftCorners[i][0] = i;
            topLeftCorners[i][1] = minXs[i];
            topLeftCorners[i][2] = minYs[i];
            topRightCorners[i][0] = i;
            topRightCorners[i][1] = maxXs[i];
            topRightCorners[i][2] = minYs[i];
            bottomLeftCorners[i][0] = i;
            bottomLeftCorners[i][1] = minXs[i];
            bottomLeftCorners[i][2] = maxYs[i];
            bottomRightCorners[i][0] = i;
            bottomRightCorners[i][1] = maxXs[i];
            bottomRightCorners[i][2] = maxYs[i];

            //Store the rectangle info in a separate array for later:
            rectangles[i].minX = minXs[i];
            rectangles[i].maxX = maxXs[i];
            rectangles[i].minY = minYs[i];
            rectangles[i].maxY = maxYs[i];
        }
        //Build the 1D range trees: (i.e. sort the arrays)
        recordAllocation();
        std::sort(minXs, minXs+numRects);
        std::sort(minYs, minYs+numRects);
        std::sort(maxXs, maxXs+numRects);
        std::sort(maxYs, maxYs+numRects);
        //Build the 2D range trees:
        recordAllocation();
        topLeftTree = range_tree::subtree<dimen, 3, 2>(numRects, topLeftCorners);
        recordAllocation();
        topRightTree = range_tree::subtree<dimen, 3, 2>(numRects, topRightCorners);
        recordAllocation();
        bottomLeftTree = range_tree::subtree<dimen, 3, 2>(numRects, bottomLeftCorners);
        recordAllocation();
        bottomRightTree = range_tree::subtree<dimen, 3, 2>(numRects, bottomRightCorners);
        recordAllocation();

        REP(i, numRects) {
            if ((i % 10000) == 0) printf("%" PRId64 "\n", i);
            
            //At first, assume all other rectangles intersect with rectangles[i]:
            num_rects tempAnswer = numRects-1;
            //Use the 1D range tree to subtract out the ones which don't intersect based off the following properties which make intersection impossible:
            //maxX <= rectangles[i].minX
            tempAnswer -= bst::findEnd(numRects, maxXs, rectangles[i].minX);
            PRINTF("%" PRId64 " %" PRId64 "\n", i, tempAnswer);
            //minX >= rectangles[i].maxX
            tempAnswer -= numRects-bst::findBegin(numRects, minXs, rectangles[i].maxX);
            PRINTF("%" PRId64 " %" PRId64 "\n", i, tempAnswer);
            //maxY <= rectangles[i].minY
            tempAnswer -= bst::findEnd(numRects, maxYs, rectangles[i].minY);
            PRINTF("%" PRId64 " %" PRId64 "\n", i, tempAnswer);
            //minY >= rectangles[i].maxY
            tempAnswer -= numRects-bst::findBegin(numRects, minYs, rectangles[i].maxY);
            PRINTF("%" PRId64 " %" PRId64 "\n", i, tempAnswer);
            //Use the 2D range tree to add back the group of rectangles which were subtracted out twice:
            tempAnswer += topLeftTree.countPointsInRange(std::array<dimen, 3>{0, rectangles[i].maxX, rectangles[i].maxY}, std::array<dimen, 3>{0, MAX_X, MAX_Y});
            PRINTF("%" PRId64 " %" PRId64 "\n", i, tempAnswer);
            tempAnswer += topRightTree.countPointsInRange(std::array<dimen, 3>{0, MIN_X, rectangles[i].maxY}, std::array<dimen, 3>{0, rectangles[i].minX, MAX_Y});
            PRINTF("%" PRId64 " %" PRId64 "\n", i, tempAnswer);
            tempAnswer += bottomLeftTree.countPointsInRange(std::array<dimen, 3>{0, rectangles[i].maxX, MIN_Y}, std::array<dimen, 3>{0, MAX_X, rectangles[i].minY});
            PRINTF("%" PRId64 " %" PRId64 "\n", i, tempAnswer);
            tempAnswer += bottomRightTree.countPointsInRange(std::array<dimen, 3>{0, MIN_X, MIN_Y}, std::array<dimen, 3>{0, rectangles[i].minX, rectangles[i].minY});
            PRINTF("%" PRId64 " %" PRId64 "\n", i, tempAnswer);

            //Update answer:
            answer += tempAnswer;
        }
        if (answer & 1) puts("Odd number of pairs"), exit(1);
        printf("%s", name);
        printf("%" PRId64 "\n", answer/2);
    }
    
    exit(0);
}