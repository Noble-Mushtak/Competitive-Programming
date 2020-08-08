//https://www.spoj.com/problems/KQUERY/
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; ++token)

#include "struct_wavelet_tree.h"

typedef int64_t num;
typedef int64_t num_nums;
typedef int64_t num_queries;

num_nums numNums;
num arr[30010], sortedArr[30010];
num_queries numQueries;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> numNums;
    if (numNums > 30000) std::cerr << "OUT OF BOUNDS\n", exit(1);
    
    num_nums i;
    REP(i, numNums) std::cin >> arr[i], sortedArr[i] = arr[i];
    
    std::sort(sortedArr, sortedArr+numNums);
    REP(i, numNums) arr[i] = std::lower_bound(sortedArr, sortedArr+numNums, arr[i])-sortedArr;
    wavelet_tree::tree<num> arrTree(arr, arr+numNums, 0, numNums-1);
    
    std::cin >> numQueries;
    while (numQueries--) {
        num_nums i, j;
        num k;
        std::cin >> i >> j >> k;
        num_nums kCompressed = std::upper_bound(sortedArr, sortedArr+numNums, k)-sortedArr;
        std::cout << arrTree.withinInterval(i-1, j, kCompressed, numNums-1) << "\n";
    }
    
    return 0;
}