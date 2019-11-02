/**
 * Library for computational geometry in C++
 * Documentation coming soon!
*/

#include <list>
#include <algorithm>
#include <cmath>

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