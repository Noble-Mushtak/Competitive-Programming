/*
ID: noble.m1
PROB: telecow
LANG: C
*/
//From USACO Training Site: http://train.usaco.org
//Section 5.4, Problem 3, TeleCowmunication
//Saved because of min node cut algorithm

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

typedef short num_warehouses;
typedef short warehouse;
typedef short num_routes;
typedef warehouse route[2];
typedef long cost;

FILE *in, *out;
num_warehouses numWarehouses;
route routes[2000];
num_routes numRoutes, cuttingOrder[2000], nextRoute[2001], answers[2000], answerLength;
cost routesCost[2000], answerCost, costAnswer;
bool disabled[2000];
warehouse mappingIn[100], mappingOut[100], reverseMapping[2000];

int compareAnswers(const void *ptr1, const void *ptr2) {
    num_routes ind1 = *(num_routes*)ptr1, ind2 = *(num_routes*)ptr2;
    return (ind1 > ind2)-(ind1 < ind2);
}

cost capacity[200][200];
cost calcFlow(num_routes num) {
    num_warehouses i, storeWarehouse, prevWarehouse, previousWarehouses[200];
    num_routes l;
    cost flow[200], storeFlow, storeFlow2, totalFlow = 0;
    bool visited[200];
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
    bool visited[2000];
    memset(visited, false, sizeof(visited));
    
    for (i = index+1; i < numRoutes; i++) if (!visited[cuttingOrder[i]]) {
        storeCost = calcFlow(cuttingOrder[i]);
        //printf("%li %li %li | %hi %hi %hi\n", maxFlow, storeCost, routesCost[cuttingOrder[i]], cuttingOrder[i], routes[cuttingOrder[i]][0], routes[cuttingOrder[i]][1]);
        if (storeCost+routesCost[cuttingOrder[i]] == maxFlow) {
             if (!storeCost && (answer || (cuttingOrder[i] < nextRoute[prevRoute]))) answer = 0, nextRoute[prevRoute] = cuttingOrder[i], visited[cuttingOrder[i]] = true;
             else if (answer) {
                 disabled[cuttingOrder[i]] = true;
                 storeAnswer = recurse(cuttingOrder[i], i, storeCost);
                 disabled[cuttingOrder[i]] = false;
                 if (storeAnswer > 0 && answer > storeAnswer || (answer == storeAnswer && cuttingOrder[i] < nextRoute[prevRoute])) {
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
    warehouse storeWarehouse[2] = {0, 0}, offset = 2, l;
    
    in = fopen("telecow.in", "r");
    while (FASTIO(store, in) != ' ') FASTEX(numWarehouses, store);
    while (FASTIO(store, in) != ' ') FASTEX(numRoutes, store);
    while (FASTIO(store, in) != ' ') FASTEX(storeWarehouse[0], store);
    mappingIn[--storeWarehouse[0]] = 0, mappingOut[storeWarehouse[0]] = 1;
    while (FASTIO(store, in) != '\n') FASTEX(storeWarehouse[1], store);
    mappingIn[--storeWarehouse[1]] = 2*numWarehouses-2, mappingOut[storeWarehouse[1]] = 2*numWarehouses-1;
    REPEAT(l, numWarehouses) {
        if (l == storeWarehouse[0] || l == storeWarehouse[1]) offset -= 2, routes[2*numRoutes+(mappingIn[l] > 0)][0] = mappingIn[l], routes[2*numRoutes+(mappingIn[l] > 0)][1] = mappingOut[l], routesCost[2*numRoutes+(mappingIn[l] > 0)] = SHRT_MAX;
        else mappingIn[l] = 2*l+offset, mappingOut[l] = 2*l+offset+1, routes[2*numRoutes+mappingIn[l]/2+1][0] = mappingIn[l], routes[2*numRoutes+mappingIn[l]/2+1][1] = mappingOut[l], routesCost[2*numRoutes+mappingIn[l]/2+1] = 1, reverseMapping[2*numRoutes+mappingIn[l]/2+1] = l;
        //printf("%hi %hi %hi\n", l, mappingIn[l], mappingOut[l]);
    }
    for (i = 0; i < 2*numRoutes; i += 2) {
        while (FASTIO(store, in) != ' ') FASTEX(routes[i][0], store);
        while (FASTIO(store, in) != '\n') FASTEX(routes[i][1], store);
        routes[i][0]--, routes[i][1]--;
        routes[i+1][0] = mappingOut[routes[i][1]], routes[i+1][1] = mappingIn[routes[i][0]];
        routes[i][0] = mappingOut[routes[i][0]], routes[i][1] = mappingIn[routes[i][1]];
        routesCost[i+1] = routesCost[i] = 1;
    }
    numRoutes *= 2, numRoutes += numWarehouses, numWarehouses *= 2;
    fclose(in);

    costAnswer = calcFlow(-1);
    //printf("FLOW: %li\n", costAnswer);
    REPEAT(i, numRoutes) cuttingOrder[i] = i;
    nextRoute[numRoutes] = -1;
    answerLength = recurse(numRoutes, numRoutes-numWarehouses/2+1, costAnswer), storeNumRoute = nextRoute[numRoutes];
    //printf("%hi %hi\n", answerLength, storeNumRoute);
    if (storeNumRoute == -1) answerLength = 0;
    else {
        REPEAT(i, answerLength) answers[i] = storeNumRoute, storeNumRoute = nextRoute[storeNumRoute];
        qsort(answers, answerLength, sizeof(num_routes), compareAnswers);
    }
    
    out = fopen("telecow.out", "w");
    fprintf(out, "%hi\n", answerLength);
    REPEAT(i, answerLength) fprintf(out, "%hi%c", reverseMapping[answers[i]]+1, i+1 == answerLength ? '\n' : ' ');
    fclose(out);
    
    exit(0);
}