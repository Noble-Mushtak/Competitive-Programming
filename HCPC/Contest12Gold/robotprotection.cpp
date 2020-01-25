#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

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

num_points numPoints;
point allPoints[20000];

int main() {
    while (true) {
        scanf("%" PRId64, &numPoints);
        if (numPoints == 0) break;
        
        num_points i;
        REP(i, numPoints) scanf("%" PRId64 " %" PRId64, &allPoints[i].x, &allPoints[i].y);
        std::list<point> hull = calcConvexHull(numPoints, allPoints);
        int64_t area = 0;
        for (auto it = hull.begin(); it != hull.end(); ++it) {
            point curPoint = *it;
            auto nextPointPtr = std::next(it);
            if (nextPointPtr == hull.end()) {
                nextPointPtr = hull.begin();
            }
            point nextPoint = *nextPointPtr;
            
            area += curPoint.x*nextPoint.y-curPoint.y*nextPoint.x;
        }
        printf("%lf\n", area/2.0);
    }
    
    return 0;
}