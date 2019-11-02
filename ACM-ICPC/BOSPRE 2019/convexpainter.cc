#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <list>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked

typedef int64_t num_points;
typedef int64_t dimen;
struct point {
    dimen x, y;
    point() {}
    point (dimen x_, dimen y_) : x(x_), y(y_) {}

    point operator-(point other) { return point(x-other.x, y-other.y); }
    dimen operator*(point other) { return x*other.y-other.x*y; }
};

std::list<point> calcConvexHull(num_points numPoints, point *points) {
    num_points i;
    std::list<point> convexHull;
    convexHull.push_back(points[0]);
    convexHull.push_back(points[1]);
    for (i = 2; i < numPoints; i++) {
        bool valid = true;
        if (convexHull.size() >= 2) {
            auto lastElemPtr = std::prev(convexHull.end());
            auto secondLastElemPtr = std::prev(lastElemPtr);
            point lastPoint = *lastElemPtr, secondLastPoint = *secondLastElemPtr;
            point firstVector = lastPoint-secondLastPoint, secondVector = points[i]-lastPoint;
            if (firstVector*secondVector >= 0) valid = false;
        }
        if (valid && (convexHull.size() >= 1)) {
            auto lastElemPtr = std::prev(convexHull.end());
            point lastPoint = *lastElemPtr;
            point firstVector = points[i]-lastPoint, secondVector = points[0]-points[i];
            if (firstVector*secondVector >= 0) valid = false;
        }
        if (valid) {
            point firstVector = points[0]-points[i], secondVector = points[1]-points[i];
            if (firstVector*secondVector >= 0) valid = false;
        }
        if (valid) convexHull.push_back(points[i]);
    }
    return convexHull;
}

double divide(double n, double d) { return n/d; }

bool pointInPolygon(point test, num_points numVertices, point *vertices) {
    num_points i, j;
    bool in = false;
    for (i = 0, j = numVertices-1; i < numVertices; j = i++) {
        if (((vertices[i].y > test.y) ^ (vertices[j].y > test.y)) && (test.x < ((vertices[j].x-vertices[i].x)*divide((test.y-vertices[i].y), (vertices[j].y-vertices[i].y))+vertices[i].x))) in = !in;
    }
    return in;
}

point polygon1[10000], polygon2[10000], polygonFiltered[10000];
num_points firstNumPoints, secondNumPoints, filteredNumPoints;
char name[100000], inputLine[100000];

void readPolygon(num_points numPoints, point *arr) {
    num_points i;
    char *curPtr;
    REP(i, numPoints) {
        curPtr = strtok(nullptr, " ");
        sscanf(curPtr, "%" PRId64, &(arr[i].x));
        curPtr = strtok(nullptr, " ");
        sscanf(curPtr, "%" PRId64, &(arr[i].y));
    }
}

int main() {
    num_points i;
    while (true) {
        fgets(name, 100000, stdin);
        if (feof(stdin)) break;
        fgets(inputLine, 100000, stdin);
        char *curPtr = strtok(inputLine, " ");
        sscanf(curPtr, "%" PRId64, &firstNumPoints);
        readPolygon(firstNumPoints, polygon1);

        fgets(inputLine, 100000, stdin);
        curPtr = strtok(inputLine, " ");
        sscanf(curPtr, "%" PRId64, &secondNumPoints);
        readPolygon(secondNumPoints, polygon2);

        filteredNumPoints = 0;
        REP(i, secondNumPoints) {
            if (pointInPolygon(polygon2[i], firstNumPoints, polygon1)) polygonFiltered[filteredNumPoints++] = polygon2[i];
        }
        printf(name);
        std::list<point> hull = calcConvexHull(filteredNumPoints, polygonFiltered);
        printf("%" PRId64 " ", hull.size());
        for (auto it = hull.begin(); it != hull.end(); ++it) {
            printf("%" PRId64 " %" PRId64 "%c", it->x, it->y, ((std::next(it) == hull.end()) ? '\n' : ' '));
        }
    }
    exit(0);
}
