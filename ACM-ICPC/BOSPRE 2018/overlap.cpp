//https://hc3.seas.harvard.edu/hc3/bospre/2018/problems/overlap/overlap.txt
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; ++token)

#ifdef TESTING
#define DEBUG(...) __VA_ARGS__
#else
#define DEBUG(...)
#endif

namespace wavelet_tree {
    typedef int64_t num_items;
    
    template<class num> struct tree {
        num minVal, maxVal;
        tree *leftChild, *rightChild;
        //itemsInLeftChild[i] denotes how many elements from arr[0..i] are in the leftChild of this wavelet tree
        //NOTE: arr[0..i] does not include arr[i]
        std::vector<num_items> itemsInLeftChild;

        //Construct a wavelet tree to represent the elements [beginIt, endIt), where every element is in the interval [minVal, maxVal]          
        template<class num_it> tree(num_it beginIt, num_it endIt, num minV, num maxV) : minVal(minV), maxVal(maxV), leftChild(nullptr), rightChild(nullptr) {
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

        //Count number of elements in arr[leftIndex..rightIndex] in the interval [queryMin, queryMax]
        num_items withinInterval(num_items leftIndex, num_items rightIndex, num queryMin, num queryMax) {
            //If this range of elements is empty or there is no overlap, return 0:
            if ((leftIndex >= rightIndex) || (queryMax < queryMin) || (queryMax < minVal) || (maxVal < queryMin)) return 0;
            //If there is only total overlap, return all elements:
            if ((queryMin <= minVal) && (maxVal <= queryMax)) return rightIndex-leftIndex;

            num_items leftIndexOfLeftChild = itemsInLeftChild[leftIndex];
            num_items rightIndexOfLeftChild = itemsInLeftChild[rightIndex];
            
            return leftChild->withinInterval(
                leftIndexOfLeftChild, rightIndexOfLeftChild, queryMin, queryMax
            )+rightChild->withinInterval(
                leftIndex-leftIndexOfLeftChild, rightIndex-rightIndexOfLeftChild, queryMin, queryMax
            );
        }
    };
}

typedef int64_t num_rects;
typedef int64_t coord;

enum coord_type {
    MIN_X,
    MAX_X,
    MIN_Y,
    MAX_Y
};

struct rect {
    coord minX;
    coord maxX;
    coord minY;
    coord maxY;
    coord getCoord(coord_type cType) {
        if (cType == coord_type::MIN_Y) return minY;
        if (cType == coord_type::MAX_Y) return maxY;
        if (cType == coord_type::MIN_X) return minX;
        if (cType == coord_type::MAX_X) return maxX;
    }
};

struct labeled_coord {
    num_rects ind;
    coord loc;
    labeled_coord() {}
    labeled_coord(coord l, num_rects i) : loc(l), ind(i) {}
};
bool operator<(labeled_coord lc1, labeled_coord lc2) { return lc1.loc < lc2.loc; }

const num_rects MAX_RECTS = 1000010;
char testCaseName[100];
num_rects numRects, minXInds[MAX_RECTS], maxXInds[MAX_RECTS], minYInds[MAX_RECTS], maxYInds[MAX_RECTS], cornerYs[MAX_RECTS], inverseXInds[MAX_RECTS];
rect rects[MAX_RECTS];
labeled_coord minXs[MAX_RECTS], maxXs[MAX_RECTS], minYs[MAX_RECTS], maxYs[MAX_RECTS];

void calcInds(labeled_coord *origCoords, labeled_coord *refCoords, num_rects *inds, bool upperBound) {
    num_rects origIdx = 0, refIdx;
    REP(refIdx, numRects) {
        while ((origIdx < numRects) && (upperBound ? (refCoords[refIdx].loc > origCoords[origIdx].loc) : (refCoords[refIdx].loc >= origCoords[origIdx].loc))) {
            inds[origCoords[origIdx].ind] = refIdx;
            ++origIdx;
        }
    }
    for (; origIdx < numRects; ++origIdx) inds[origCoords[origIdx].ind] = numRects;
}

void calcInverseInds(labeled_coord *arr, num_rects *inverseInds) {
    num_rects i;
    REP(i, numRects) inverseInds[arr[i].ind] = i;
}

void buildCornerYs(num_rects *inverseXInds, labeled_coord *ys) {
    num_rects xsIdx, ysIdx = 0;
    while (ysIdx < numRects) {
        num_rects lastYsIdx = ysIdx;
        for (; (ysIdx < numRects) && (ys[ysIdx].loc == ys[lastYsIdx].loc); ++ysIdx) cornerYs[inverseXInds[ys[ysIdx].ind]] = lastYsIdx;
        
        //cornerYs[i] = std::lower_bound(ys, ys+numRects, labeled_coord(rects[xs[i].ind].getCoord(cType), 0))-ys;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (true) {
        std::cin.getline(testCaseName, 100);
        if (std::cin.eof()) break;
        std::cout << testCaseName << "\n";

        numRects = 0;
        while (true) {
            char curLine[1000];
            std::cin.getline(curLine, 1000);
            if (curLine[0] == '*') break;
            
            std::stringstream curLineStream(curLine);
            curLineStream >> rects[numRects].minX >> rects[numRects].maxX >> rects[numRects].minY >> rects[numRects].maxY;
            minXs[numRects] = labeled_coord(rects[numRects].minX, numRects);
            maxXs[numRects] = labeled_coord(rects[numRects].maxX, numRects);
            minYs[numRects] = labeled_coord(rects[numRects].minY, numRects);
            maxYs[numRects] = labeled_coord(rects[numRects].maxY, numRects);
            ++numRects;
        }
        
        num_rects answer = numRects*(numRects-1), i;
        
        std::sort(minXs, minXs+numRects);
        std::sort(maxXs, maxXs+numRects);
        calcInds(minXs, maxXs, minXInds, true);
        REP(i, numRects) {
            //maxX <= rects[i].minX
            //minXInds[i] = std::upper_bound(maxXs, maxXs+numRects, labeled_coord(rects[i].minX, 0))-maxXs;
            answer -= minXInds[i];
        }
        
        calcInds(maxXs, minXs, maxXInds, false);
        REP(i, numRects) {
            //minX >= rects[i].maxX
            //maxXInds[i] = std::lower_bound(minXs, minXs+numRects, labeled_coord(rects[i].maxX, 0))-minXs;
            answer -= numRects-maxXInds[i];
        }
        
        std::sort(minYs, minYs+numRects);
        std::sort(maxYs, maxYs+numRects);
        calcInds(minYs, maxYs, minYInds, true);
        REP(i, numRects) {   
            //maxY <= rects[i].minY
            //minYInds[i] = std::upper_bound(maxYs, maxYs+numRects, rects[i].minY)-maxYs;
            answer -= minYInds[i];
        }
        
        calcInds(maxYs, minYs, maxYInds, false);
        REP(i, numRects) {
            //minY >= rects[i].maxY
            //maxYInds[i] = std::lower_bound(minYs, minYs+numRects, rects[i].maxY)-minYs;
            answer -= numRects-maxYInds[i];
        }

        calcInverseInds(minXs, inverseXInds);
        buildCornerYs(inverseXInds, minYs);
        wavelet_tree::tree<num_rects> topLeftCornersTree(cornerYs, cornerYs+numRects, 0, numRects-1);
        REP(i, numRects) {
            //minX >= rects[i].maxX, minY >= rects[i].maxY
            answer += topLeftCornersTree.withinInterval(maxXInds[i], numRects, maxYInds[i], numRects-1);
        }
        
        buildCornerYs(inverseXInds, maxYs);
        wavelet_tree::tree<num_rects> bottomLeftCornersTree(cornerYs, cornerYs+numRects, 0, numRects-1);
        REP(i, numRects) {
            //minX >= rects[i].maxX, maxY <= rects[i].minY
            answer += bottomLeftCornersTree.withinInterval(maxXInds[i], numRects, 0, minYInds[i]-1);
        }
        
        calcInverseInds(maxXs, inverseXInds);
        buildCornerYs(inverseXInds, minYs);
        wavelet_tree::tree<num_rects> topRightCornersTree(cornerYs, cornerYs+numRects, 0, numRects-1);
        REP(i, numRects) {
            //maxX <= rects[i].minX, minY >= rects[i].maxY
            answer += topRightCornersTree.withinInterval(0, minXInds[i], maxYInds[i], numRects-1);
        }
        
        buildCornerYs(inverseXInds, maxYs);
        wavelet_tree::tree<num_rects> bottomRightCornersTree(cornerYs, cornerYs+numRects, 0, numRects-1);
        REP(i, numRects) {
            //maxX <= rects[i].minX, maxY <= rects[i].minY
            answer += bottomRightCornersTree.withinInterval(0, minXInds[i], 0, minYInds[i]-1);
        }

        if (answer & 1) {
            std::cerr << "Odd number of answers: " << answer << "\n";
            exit(1);
        }
        std::cout << (answer >> 1) << "\n";
    }

    return 0;
}