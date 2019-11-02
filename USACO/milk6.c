/*
ID: noble.m1
PROB: milk6
LANG: C
*/
//From USACO Training Site: http://train.usaco.org
//Section 4.4, Problem 2, Pollutant Control
//Saved because of min cut algorithm

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;
#define FASTIO(lvalue, file) (lvalue = fgetc(file))
#define FASTEX(lvalue, char) (lvalue = lvalue*10+(char-'0'))
#define FASTEXS(lvalue, char) ((char == '-') ? (-1) : (FASTEX(lvalue, char), 1))
#define FASTEXN(lvalue, sign, char) (lvalue = lvalue*10+sign*(char-'0'))
#define POPQUEUE(arr, len) memmove(arr, arr+1, len*sizeof(arr[0]))
#define REMOVEELEM(arr, off, len) memmove(arr+off, arr+(off+1), (len-off)*sizeof(arr[0]))
#define REMOVEELEMS(arr, off, len, num) memmove(arr+off, arr+(off+num), (len-off)*sizeof(arr[0]))
#define SET(arr, e1, e2) ( \
    (arr[0] = e1), \
    (arr[1] = e2) \
)

typedef byte num_warehouses;
typedef byte warehouse;
typedef short num_routes;
typedef warehouse route[2];
typedef long cost;

FILE *in, *out;
num_warehouses numWarehouses;
route routes[1000];
num_routes numRoutes, cuttingOrder[1000], nextRoute[1001], answers[1000], answerLength;
cost routesCost[1000], answerCost, costAnswer;
bool disabled[1000];

int compareNumRoutes(const void *ptr1, const void *ptr2) {
    num_routes ind1 = *(num_routes*)ptr1, ind2 = *(num_routes*)ptr2;
    return ((routesCost[ind1] > routesCost[ind2])-(routesCost[ind1] < routesCost[ind2])) || ((ind1 > ind2)-(ind1 < ind2));
}

int compareAnswers(const void *ptr1, const void *ptr2) {
    num_routes ind1 = *(num_routes*)ptr1, ind2 = *(num_routes*)ptr2;
    return (ind1 > ind2)-(ind1 < ind2);
}

cost calcFlow(num_routes num) {
    num_warehouses i, storeWarehouse, prevWarehouse, previousWarehouses[32];
    num_routes l;
    cost capacity[32][32], flow[32], storeFlow, storeFlow2, totalFlow = 0;
    bool visited[32];
    memset(capacity, 0, sizeof(capacity));
    REPEAT(l, numRoutes) if (l != num && !disabled[l]) capacity[routes[l][0]][routes[l][1]] += routesCost[l];

    while (true) {
        REPEAT(i, numWarehouses) previousWarehouses[i] = -1;
        memset(flow, 0, sizeof(flow)), memset(visited, false, sizeof(visited));
        flow[0] = LONG_MAX;

        while (true) {
            storeFlow = 0, storeWarehouse = -1;
            for (i = numWarehouses-1; i >= 0; i--) if (flow[i] > storeFlow && !visited[i]) storeFlow = flow[i], storeWarehouse = i;
            if (storeWarehouse == -1 || storeWarehouse+1 == numWarehouses) break;
            visited[storeWarehouse] = true;
            REPEAT(i, numWarehouses) if (capacity[storeWarehouse][i]) {
                storeFlow2 = ((storeFlow < capacity[storeWarehouse][i]) ? storeFlow : capacity[storeWarehouse][i]);
                if (flow[i] < storeFlow2) previousWarehouses[i] = storeWarehouse, flow[i] = storeFlow2;
            }
        }
        if (storeWarehouse == -1) break;
        totalFlow += flow[numWarehouses-1];

        storeWarehouse = numWarehouses-1;
        while (storeWarehouse != 0) capacity[previousWarehouses[storeWarehouse]][storeWarehouse] -= flow[numWarehouses-1], capacity[storeWarehouse][previousWarehouses[storeWarehouse]] += flow[numWarehouses-1], storeWarehouse = previousWarehouses[storeWarehouse];
    }

    return totalFlow;
}

num_routes recurse(num_routes prevRoute, num_routes index, cost maxFlow) {
    num_routes i, j, k, answer = SHRT_MAX, storeAnswer;
    cost storeCost;
    bool visited[1000];
    memset(visited, false, sizeof(visited));
    
    for (i = index+1; i < numRoutes; i++) if (!visited[cuttingOrder[i]]) {
        storeCost = calcFlow(cuttingOrder[i]);
        //printf("%hi %hi %li %li %li\n", i, cuttingOrder[i], storeCost, routesCost[cuttingOrder[i]], maxFlow);
        if (storeCost+routesCost[cuttingOrder[i]] == maxFlow) {
             if (!storeCost && (answer || (cuttingOrder[i] < nextRoute[prevRoute]))) answer = 0, nextRoute[prevRoute] = cuttingOrder[i], visited[cuttingOrder[i]] = true;
             else if (answer) {
                 disabled[cuttingOrder[i]] = true;
                 storeAnswer = recurse(cuttingOrder[i], i, storeCost);
                 disabled[cuttingOrder[i]] = false;
                 if (answer > storeAnswer || (answer == storeAnswer && cuttingOrder[i] < nextRoute[prevRoute])) {
                     answer = storeAnswer;
                     nextRoute[prevRoute] = k = cuttingOrder[i];
                     REPEAT(j, answer+1) visited[k] = true, k = nextRoute[k];
                 }
             }
        }
    }

    return ((answer < 0) ? SHRT_MAX : answer+1);
}

int main() {
    char store;
    num_routes i, storeNumRoute;
    
    in = fopen("milk6.in", "r");
    while (FASTIO(store, in) != ' ') FASTEX(numWarehouses, store);
    while (FASTIO(store, in) != '\n') FASTEX(numRoutes, store);
    REPEAT(i, numRoutes) {
        while (FASTIO(store, in) != ' ') FASTEX(routes[i][0], store);
        while (FASTIO(store, in) != ' ') FASTEX(routes[i][1], store);
        routes[i][0]--, routes[i][1]--;
        while (FASTIO(store, in) != '\n') FASTEX(routesCost[i], store);
    }
    fclose(in);

    costAnswer = calcFlow(-1);
    REPEAT(i, numRoutes) cuttingOrder[i] = i;
    qsort(cuttingOrder, numRoutes, sizeof(num_routes), compareNumRoutes);
    nextRoute[1000] = -1;
    answerLength = recurse(1000, -1, costAnswer), storeNumRoute = nextRoute[1000];
    if (nextRoute[1000] == -1) answerLength = 0;
    else {
        REPEAT(i, answerLength) answers[i] = storeNumRoute, storeNumRoute = nextRoute[storeNumRoute];
        qsort(answers, answerLength, sizeof(num_routes), compareAnswers);
    }
    
    out = fopen("milk6.out", "w");
    fprintf(out, "%li %hi\n", costAnswer, answerLength);
    REPEAT(i, answerLength) fprintf(out, "%hi\n", answers[i]+1);
    fclose(out);
    
    exit(0);
}