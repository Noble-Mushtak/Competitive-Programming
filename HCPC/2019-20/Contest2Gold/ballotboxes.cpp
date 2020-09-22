#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <queue>
#include <tuple>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_cities;
typedef int64_t num_boxes;
typedef int64_t city;
typedef std::tuple<city, num_cities, city> point;

num_cities numCities;
num_boxes numBoxes;
city cities[1000000], maxElem, minElem;
num_cities cuts[1000000];
std::priority_queue<point> citiesHeap;

point calcPopulation(city i) {
    num_cities numPortions = cuts[i]+1;
    //city curMinElem = cities[i]/numPortions;
    city curMaxElem = (cities[i]+numPortions-1)/numPortions;
    return point(curMaxElem, -cuts[i], i);
}

int main() {
    num_cities i;
    while (true) {
        scanf("%" PRId64 " %" PRId64, &numCities, &numBoxes);
        if ((numCities == -1) && (numBoxes == -1)) break;
        while (!citiesHeap.empty()) citiesHeap.pop();
        
        REP(i, numCities) {
            scanf("%" PRId64, cities+i);
            cuts[i] = 0;
            citiesHeap.push(calcPopulation(i));
        }

        num_boxes l;
        REP(l, numBoxes-numCities) {
            city maxCity = std::get<2>(citiesHeap.top());
            cuts[maxCity]++;
            citiesHeap.pop();
            citiesHeap.push(calcPopulation(maxCity));
        }
        printf("%" PRId64 "\n", std::get<0>(citiesHeap.top()));
    }
    
    return 0;
}