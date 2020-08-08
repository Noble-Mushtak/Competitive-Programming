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

#include "../../Libraries/struct_wavelet_tree.h"

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
num_rects numRects, minXInds[MAX_RECTS], maxXInds[MAX_RECTS], minYInds[MAX_RECTS], maxYInds[MAX_RECTS], cornerYs[MAX_RECTS];
rect rects[MAX_RECTS];
labeled_coord minXs[MAX_RECTS], maxXs[MAX_RECTS];
coord minYs[MAX_RECTS], maxYs[MAX_RECTS];

void buildCornerYs(labeled_coord *xs, coord_type cType, coord *ys) {
    num_rects i;
    REP(i, numRects) {
        cornerYs[i] = std::lower_bound(ys, ys+numRects, rects[xs[i].ind].getCoord(cType))-ys;
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
            minYs[numRects] = rects[numRects].minY;
            maxYs[numRects] = rects[numRects].maxY;
            ++numRects;
        }
        
        num_rects answer = 0, i;
        
        std::sort(maxXs, maxXs+numRects);
        REP(i, numRects) {
            answer += numRects-1;
            
            //maxX <= rects[i].minX
            minXInds[i] = std::upper_bound(maxXs, maxXs+numRects, labeled_coord(rects[i].minX, 0))-maxXs;
            answer -= minXInds[i];
        }
        
        std::sort(minXs, minXs+numRects);
        REP(i, numRects) {
            //minX >= rects[i].maxX
            maxXInds[i] = std::lower_bound(minXs, minXs+numRects, labeled_coord(rects[i].maxX, 0))-minXs;
            answer -= numRects-maxXInds[i];
        }
        
        std::sort(maxYs, maxYs+numRects);
        REP(i, numRects) {   
            //maxY <= rects[i].minY
            minYInds[i] = std::upper_bound(maxYs, maxYs+numRects, rects[i].minY)-maxYs;
            answer -= minYInds[i];
        }
        
        std::sort(minYs, minYs+numRects);
        REP(i, numRects) {
            //minY >= rects[i].maxY
            maxYInds[i] = std::lower_bound(minYs, minYs+numRects, rects[i].maxY)-minYs;
            answer -= numRects-maxYInds[i];
        }

        buildCornerYs(minXs, coord_type::MIN_Y, minYs);
        wavelet_tree::tree<num_rects> topLeftCornersTree(cornerYs, cornerYs+numRects, 0, numRects-1);
        //wavelet_tree::tree<num_rects> cornersTree(cornerYs, cornerYs+numRects, 0, numRects-1);
        REP(i, numRects) {
            //minX >= rects[i].maxX, minY >= rects[i].maxY
            answer += topLeftCornersTree.withinInterval(maxXInds[i], numRects, maxYInds[i], numRects-1);
            //answer += cornersTree.withinInterval(maxXInds[i], numRects, maxYInds[i], numRects-1);
        }
        
        buildCornerYs(maxXs, coord_type::MIN_Y, minYs);
        wavelet_tree::tree<num_rects> topRightCornersTree(cornerYs, cornerYs+numRects, 0, numRects-1);
        //cornersTree.reconstruct(cornerYs, cornerYs+numRects, 0, numRects-1);
        REP(i, numRects) {
            //maxX <= rects[i].minX, minY >= rects[i].maxY
            answer += topRightCornersTree.withinInterval(0, minXInds[i], maxYInds[i], numRects-1);
            //answer += cornersTree.withinInterval(0, minXInds[i], maxYInds[i], numRects-1);
        }
        
        buildCornerYs(minXs, coord_type::MAX_Y, maxYs);
        wavelet_tree::tree<num_rects> bottomLeftCornersTree(cornerYs, cornerYs+numRects, 0, numRects-1);
        //cornersTree.reconstruct(cornerYs, cornerYs+numRects, 0, numRects-1);
        REP(i, numRects) {
            //minX >= rects[i].maxX, maxY <= rects[i].minY
            answer += bottomLeftCornersTree.withinInterval(maxXInds[i], numRects, 0, minYInds[i]-1);
            //answer += cornersTree.withinInterval(maxXInds[i], numRects, 0, minYInds[i]-1);   
        }
        
        buildCornerYs(maxXs, coord_type::MAX_Y, maxYs);
        wavelet_tree::tree<num_rects> bottomRightCornersTree(cornerYs, cornerYs+numRects, 0, numRects-1);
        //cornersTree.reconstruct(cornerYs, cornerYs+numRects, 0, numRects-1);
        REP(i, numRects) {
            //maxX <= rects[i].minX, maxY <= rects[i].minY
            answer += bottomRightCornersTree.withinInterval(0, minXInds[i], 0, minYInds[i]-1);
            //answer += cornersTree.withinInterval(0, minXInds[i], 0, minYInds[i]-1);
        }

        if (answer & 1) {
            std::cerr << "Odd number of answers: " << answer << "\n";
            exit(1);
        }
        std::cout << answer/2 << "\n";
    }

    return 0;
}