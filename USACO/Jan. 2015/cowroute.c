#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define SET(arr, e1, e2) ( \
    (arr[0] = e1), \
    (arr[1] = e2) \
)
#define MOD(a, b) (((a % b)+b) % b)
typedef signed char byte;

typedef long long dist;
typedef short city;
typedef short num_cities;

FILE *in, *out;
dist distances[1000][1000][2], distanceFrom[1000][2];
city route[100], source, dest, stack[1000], stackPos, maxCity = 0;
num_cities numRoutes, numCities;
bool added[1000], scanned[1000];

int main() {
    dist store, minC, minF, store2[2];
    num_cities i, j, k, min;
    city minCity, l;
    REPEAT(i, 1000) {
        SET(distanceFrom[i], LLONG_MAX, LLONG_MAX);
        REPEAT(j, 1000) SET(distances[i][j], LLONG_MAX, LLONG_MAX);
    }
    
    in = fopen("cowroute.in", "r");
    fscanf(in, "%hi %hi %hi", &source, &dest, &numRoutes);
    source--, dest--;
    REPEAT(i, numRoutes) {
        fscanf(in, "%lli %hi", &store, &numCities);
        REPEAT(j, numCities) {
            fscanf(in, "%hi", route+j);
            route[j]--;
            if (maxCity <= route[j]) maxCity = route[j]+1;
            REPEAT(k, j) if (distances[route[j]][route[k]][0] >= store) {
               if (store != distances[route[j]][route[k]][0] || distances[route[j]][route[k]][1] > MOD((k-j), numCities)) SET(distances[route[j]][route[k]], store, MOD((k-j), numCities));
                if (store != distances[route[k]][route[j]][0] || distances[route[k]][route[j]][1] > j-k) SET(distances[route[k]][route[j]], distances[route[j]][route[k]][0], j-k);
            }
        }
    }
    fclose(in);
    
    #define COMPARE(a, b) (a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]))
    stack[0] = source, stackPos = 1;
    SET(distanceFrom[source], 0, 0);
    while (stackPos) {
        min = 0;
        REPEAT(i, stackPos) if (COMPARE(distanceFrom[stack[i]], distanceFrom[stack[min]]) || (distanceFrom[stack[min]][0] == distanceFrom[stack[i]][0] && distanceFrom[stack[min]][1] == distanceFrom[stack[i]][1] && stack[i] == dest)) min = i;
        minCity = stack[min], minC = distanceFrom[minCity][0], minF = distanceFrom[minCity][1];
        if (minCity == dest) break;
        stackPos--;
        stack[min] = stack[stackPos];
        scanned[minCity] = true;
        REPEAT(l, maxCity) if (!scanned[l] && distances[minCity][l][0] < LLONG_MAX) {
            SET(store2, minC+distances[minCity][l][0], minF+distances[minCity][l][1]);
            if (COMPARE(store2, distanceFrom[l])) SET(distanceFrom[l], store2[0], store2[1]);
            if (!added[l]) {
                stack[stackPos] = l;
                stackPos++;
                added[l] = true;
            }
        }
    }
    
    out = fopen("cowroute.out", "w");
    fprintf(out, "%lli %lli\n", added[dest] ? minC : -1, added[dest] ? minF : -1);
    fclose(out);
    
    exit(0);
}