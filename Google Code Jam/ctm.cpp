/*
    https://codingcompetitions.withgoogle.com/codejam/round/0000000000051679/0000000000146185
*/

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; ++token)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t test_cases;
typedef int64_t metal;
typedef int64_t num_metals;
typedef int64_t weight;

test_cases numTestCases;
num_metals numMetals;
metal children[100010][2];
std::set<metal> parents[100010];
weight quantities[100010];
bool feasible[100010], helpful[100010];
num_metals orderSize;
metal topologicalOrder[100010];
const weight MOD = 1000000007;

metal stack[100010];
void markChildrenFeasible(metal parentMetal) {
    num_metals i, stackSize = 1;
    stack[0] = parentMetal;
    while (stackSize > 0) {
        metal curParent = stack[--stackSize];
        REP(i, 2) {
            metal curChild = children[curParent][i];
            if (!feasible[curChild]) {
                feasible[curChild] = true;
                stack[stackSize++] = curChild;
            }
        }
    }
}

void markParentsHelpful(metal goalMetal) {
    num_metals stackSize = 1;
    stack[0] = goalMetal;
    while (stackSize > 0) {
        metal curChild = stack[--stackSize];
        for (auto parentIt = parents[curChild].begin(); parentIt != parents[curChild].end(); ++parentIt) {
            metal curParent = *parentIt;
            if (feasible[curParent] && !helpful[curParent]) {
                helpful[curParent] = true;
                stack[stackSize++] = curParent;
            }
        }
    }
}

bool straightCycleToZero(metal helpfulChild) {
    while (helpfulChild != 0) {
        if (helpful[children[helpfulChild][0]] ^ helpful[children[helpfulChild][1]]) {
            num_metals helpfulInd = helpful[children[helpfulChild][0]] ? 0 : 1;
            helpfulChild = children[helpfulChild][helpfulInd];
        }
        else return false;
    }
    return true;
}

int main() {
    test_cases l;
    scanf(INT64, &numTestCases);
    REP(l, numTestCases) {
        scanf(INT64, &numMetals);
        num_metals i;
        REP(i, numMetals) parents[i].clear(), feasible[i] = helpful[i] = false;
        
        REP(i, numMetals) {
            scanf(INT64 " " INT64, children[i]+0, children[i]+1);
            --children[i][0], --children[i][1];
            parents[children[i][0]].insert(i);
            parents[children[i][1]].insert(i);
        }
        REP(i, numMetals) scanf(INT64, quantities+i);
        
        REP(i, numMetals) if (!feasible[i] && (quantities[i] > 0)) {
            feasible[i] = true;
            markChildrenFeasible(i);
        }
        if (!feasible[0]) {
            printf("Case #" INT64 ": 0\n", l+1);
            continue;
        }
        helpful[0] = true;
        markParentsHelpful(0);

        metal deletedChild = -1;
        if (helpful[children[0][0]] ^ helpful[children[0][1]]) {
            num_metals helpfulInd = helpful[children[0][0]] ? 0 : 1;
            metal helpfulChild = children[0][helpfulInd];
            if (straightCycleToZero(helpfulChild)) {
                auto parentIt = parents[helpfulChild].find(0);
                if (parentIt == parents[helpfulChild].end()) fprintf(stderr, "Could not find parent node of 0\n"), exit(1);
                parents[helpfulChild].erase(parentIt);
                deletedChild = helpfulChild;
            }
        }

        num_metals numHelpfulMetals = 0;
        orderSize = 0;
        REP(i, numMetals) if (helpful[i]) {
            ++numHelpfulMetals;
            for (auto parentIt = parents[i].begin(); parentIt != parents[i].end();) {
                metal curParent = *parentIt;
                if (!helpful[curParent]) parentIt = parents[i].erase(parentIt);
                else ++parentIt;
            }
            if (parents[i].empty()) topologicalOrder[orderSize++] = i;
        }
        num_metals curLoc;
        REP(curLoc, orderSize) {
            metal curMetal = topologicalOrder[curLoc];
            REP(i, 2) {
                metal curChild = children[curMetal][i];
                if (helpful[curChild] && !((curMetal == 0) && (curChild == deletedChild))) {
                    auto parentIt = parents[curChild].find(curMetal);
                    if ((parentIt == parents[curChild].end())) fprintf(stderr, "Could not find parent node of curMetal\n"), exit(1);
                    parents[curChild].erase(parentIt);
                    if (parents[curChild].empty()) topologicalOrder[orderSize++] = curChild;
                }
            }
        }
        if (orderSize > numHelpfulMetals) fprintf(stderr, "Too many metals in order\n"), exit(1);
        if (orderSize < numHelpfulMetals) {
            printf("Case #" INT64 ": UNBOUNDED\n", l+1);
            continue;
        }
        if (topologicalOrder[orderSize-1] != 0) fprintf(stderr, "Wrong goal\n"), exit(1);
        
        REP(i, orderSize-1) {
            metal curMetal = topologicalOrder[i];
            quantities[children[curMetal][0]] += quantities[curMetal];
            quantities[children[curMetal][0]] %= MOD;
            quantities[children[curMetal][1]] += quantities[curMetal];
            quantities[children[curMetal][1]] %= MOD;
        }
        printf("Case #" INT64 ": " INT64 "\n", l+1, quantities[0]);
    }
    
    return 0;
}