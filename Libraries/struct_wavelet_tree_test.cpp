//https://www.spoj.com/problems/MKTHNUM/
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; ++token)

#include "struct_wavelet_tree.h"

typedef int64_t num;
typedef int64_t num_nums;
typedef int64_t num_queries;

const num MAX_NUM = 1000000000;
num_queries numQueries;
num_nums numNums;
num arr[100010], sortedArr[100010];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> numNums >> numQueries;
    num_nums i;
    REP(i, numNums) {
        std::cin >> arr[i];
        sortedArr[i] = arr[i];
    }
    
    std::sort(sortedArr, sortedArr+numNums);
    REP(i, numNums) arr[i] = std::lower_bound(sortedArr, sortedArr+numNums, arr[i])-sortedArr;
    wavelet_tree::tree<num> curTree(arr, arr+numNums, 0, numNums);

    while (numQueries--) {
        num_nums i, j, k;
        std::cin >> i >> j >> k;
        std::cout << sortedArr[curTree.kthSmallest(i-1, j, k-1)] << "\n";
    }
}