//https://www.spoj.com/problems/HORRIBLE/
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define USE_STATIC
#include "struct_segtree.h"

typedef int64_t test_cases;
typedef int64_t num;
typedef int64_t num_nums;
typedef int64_t num_queries;
typedef int64_t query_type;

struct all_zeroes {
    num operator[](std::size_t curIndex) { return 0; }
};
all_zeroes allZeroes;

num addToNode(segtree::node_info curNode, num curItem, num curUpdate) {
    return curItem+(curNode.rightB-curNode.leftB+1)*curUpdate;
}

test_cases numTestCases;
segtree::segtree<num, num> segmentTree;
num_nums numNums;
num_queries numQueries;

int main() {
    scanf("%" PRId64, &numTestCases);
    while (numTestCases--) {
        scanf("%" PRId64 " " "%" PRId64, &numNums, &numQueries);
        segmentTree = segtree::segtree<num, num>(allZeroes, numNums, 0, addToNode);
        while (numQueries--) {
            query_type curQueryType;
            scanf("%" PRId64, &curQueryType);
            if (curQueryType == 0) {
                num_nums start, end;
                num update;
                scanf("%" PRId64 " " "%" PRId64 " " "%" PRId64, &start, &end, &update);
                --start, --end;
                segmentTree.updateInterval(start, end, update);
            } else {
                num_nums start, end;
                scanf("%" PRId64 " " "%" PRId64, &start, &end);
                --start, --end;
                printf("%" PRId64 "\n", segmentTree.calcMerge(start, end));
            }
        }
    }
    
    return 0;
}