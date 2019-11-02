#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <list>
#include <cmath>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_points;
typedef int64_t dimen;
struct point {
    dimen x, y;
    point() {}
    point(dimen x_, dimen y_) : x(x_), y(y_) {}

    //Order points by x-coordinate, then by y-coordinate:
    bool operator<(point other) {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    //Difference of two vectors:
    point operator-(point other) { return point(x-other.x, y-other.y); }
    //Cross product:
    dimen operator*(point other) { return x*other.y-other.x*y; }
};
typedef int64_t time;

//Standard Convex Hull Algorithm:
std::list<point> calcConvexHull(num_points numPoints, point *points) {
    //Sort the points by x-coordinate, then by y-coordinate:
    //Notice that this is done in-place, which assumes that changing the order of the original points array will have no unintended side effects.
    std::sort(points, points+numPoints);
    
    num_points i;
    //By default, add the first two points to the lower hull:
    std::list<point> convexHull;
    convexHull.push_back(points[0]);
    convexHull.push_back(points[1]);
    //Loop through the rest of the points:
    for (i = 2; i < numPoints; i++) {
        //In this while loop, we try to remove points.
        //However, only try this if the lower hull still has at least two points:
        while (convexHull.size() >= 2) {
            //Get the vector from the second-to-last point to the last point,
            //and the vector from the last point to the current point:
            auto lastElemPtr = std::prev(convexHull.end());
            auto secondLastElemPtr = std::prev(lastElemPtr);
            point lastPoint = *lastElemPtr, secondLastPoint = *secondLastElemPtr;
            point firstVector = lastPoint-secondLastPoint, secondVector = points[i]-lastPoint;
            //If these vectors have a negative cross product, then the polygon is no longer convex, so remove the last point:
            if (firstVector*secondVector <= 0) convexHull.erase(lastElemPtr);
            else break;
        }
        //Finally, add the new point to the convex hull:
        convexHull.push_back(points[i]);
    }
    //Record size of lower hull (don't include the last point):
    num_points lowerHullSize = convexHull.size()-1;
    
    //By default, add the second-to-last point to the upper hull:
    //(The last point is already in the upper hull, since it was added by the previous for loop.)
    convexHull.push_back(points[numPoints-2]);
    //Loop through the rest of the points:
    for (i = numPoints-3; i >= 0; i--) {
        //In this while loop, we try to remove points.
        //However, only try this if upper hull still has at least two points:
        while (convexHull.size()-lowerHullSize >= 2) {
            //Get the vector from the second-to-last point to the last point,
            //and the vector from the last point to the current point:
            auto lastElemPtr = std::prev(convexHull.end());
            auto secondLastElemPtr = std::prev(lastElemPtr);
            point lastPoint = *lastElemPtr, secondLastPoint = *secondLastElemPtr;
            point firstVector = lastPoint-secondLastPoint, secondVector = points[i]-lastPoint;
            //If these vectors have a negative cross product, then the polygon is no longer convex, so remove the last point:
            if (firstVector*secondVector <= 0) convexHull.erase(lastElemPtr);
            else break;
        }
        //Finally, add the new point to the convex hull:
        convexHull.push_back(points[i]);
    }
    //At the end, return the convex hull:
    //Notice that the lexicographically least point in the set (i.e. the one which has the least x-coordinate) will be repeated in the hull, as it is both the first and the last point.
    return convexHull;
}

double calcPerimeter(std::list<point> polygon) {
    //This variable stores the perimeter:
    double distance = 0;
    //Loop through all the points except the last point:
    //(This is because we are assuming the first point is the same as the last point.)
    for (auto it = polygon.begin(); it != std::prev(polygon.end()); it++) {
        //Use distance formula to calculate distance between this point and the one adjacent to it:
        auto nextPointPtr = std::next(it);
        point curPoint = *it, nextPoint = *nextPointPtr;
        double distanceX = curPoint.x-nextPoint.x;
        double distanceY = curPoint.y-nextPoint.y;
        distance += std::sqrt(distanceX*distanceX+distanceY*distanceY);
    }
    //Finally, return the distance:
    return distance;
}

num_points numTrees, numPoles;
point allPoles[2000], convexHull[2000];
dimen treeLengths[2000], storage1[10000], storage2[10000];
time treeTimes[2000];

int main() {
    //Read in the input and store the data in the appropriate arrays:
    num_points i;
    scanf("%" PRId64 " %" PRId64, &numTrees, &numPoles);
    REP(i, numTrees) scanf("%" PRId64 " %" PRId64, treeLengths+i, treeTimes+i);
    REP(i, numPoles) scanf("%" PRId64 " %" PRId64, &(allPoles[i].x), &(allPoles[i].y));

    //Calc convex hull and take ceiling of the perimeter to get the minimum number of meters we need:
    std::list<point> hull = calcConvexHull(numPoles, allPoles);
    //for (auto it = hull.begin(); it != hull.end(); it++) printf("%" PRId64 " %" PRId64 "\n", (*it).x, (*it).y);
    dimen requiredDistance = std::ceil(calcPerimeter(hull));

    dimen curDist;
    time *minTime = storage1, *oldMinTime = storage2, *temp;
    //Let i be the number of trees processed so far. (Right now, i=0)
    //oldMinTime[curDist] represents the minimum amount of time required to get curDist meters from the first i trees (set to 1100000 if the first i trees altogether make up less than curDist meters)
    //minTime[curDist] represents the minimum amount of time required to get curDist meters from the first i+1 trees (set to 1100000 if the first i trees altogether make up less than curDist meters)
    REP(curDist, requiredDistance+1) oldMinTime[curDist] = (curDist == 0) ? 0 : 1100000;
    
    //Process each tree one-by-one:
    REP(i, numTrees) {
        //Update the minTime array appropriately:
        //(The equation used is based off the standard solution to the 0/1 knapsack problem: https://en.wikipedia.org/wiki/Knapsack_problem#0/1_knapsack_problem)
        REP(curDist, requiredDistance+1) {
            minTime[curDist] = std::min(oldMinTime[curDist], oldMinTime[(curDist >= treeLengths[i]) ? (curDist-treeLengths[i]) : 0]+treeTimes[i]);
        }
        //Swap minTime and oldMinTime pointers:
        temp = minTime, minTime = oldMinTime, oldMinTime = temp;
    }
    //Now that all the trees have been processed, output the minimum amount of time needed to get requiredDistance meters:
    printf("%" PRId64 "\n", oldMinTime[requiredDistance]);
    
    return 0;
}