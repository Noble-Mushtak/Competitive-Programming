//https://codeforces.com/contest/446/problem/C
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; ++token)
#define INT64 "%" PRId64

#include "struct_segtree.h"

typedef int64_t num;
typedef int64_t num_nums;
typedef int64_t num_queries;
typedef int64_t query_type;

const num MOD = 1000000009;
num_nums numNums;
num_queries numQueries;

struct mod_num {
    num val;
    mod_num() {}
    mod_num(num v) : val(v) {}
};
mod_num operator+(mod_num n1, mod_num n2) { return mod_num((n1.val+n2.val) % MOD); }
mod_num operator-(mod_num n1, mod_num n2) { return mod_num((n1.val+MOD-n2.val) % MOD); }
mod_num operator*(mod_num n1, mod_num n2) { return mod_num((n1.val*n2.val) % MOD); }

mod_num arr[300050];
mod_num fibs[300050];

mod_num calcCustomFib(num_nums i, mod_num f0, mod_num f1) {
    if (i == 0) return f0;
    if (i == 1) return f1;
    return fibs[i-1]*f0+fibs[i]*f1;
}
mod_num calcCustomFibPartial(num_nums i, mod_num f0, mod_num f1) {
    return calcCustomFib(i+2, f0, f1)-f1;
}

struct fib_update {
    mod_num f0;
    mod_num f1;
    num_nums start;
    fib_update() {}
    fib_update(mod_num f0_, mod_num f1_, num_nums s)
      : f0(f0_), f1(f1_), start(s) {}
};
fib_update operator+(fib_update up1, fib_update up2) {
    if (up1.start < up2.start) {
        fib_update temp = up1;
        up1 = up2, up2 = temp;
    }
    mod_num newF0 = calcCustomFib(up1.start-up2.start, up2.f0, up2.f1);
    mod_num newF1 = calcCustomFib(up1.start-up2.start+1, up2.f0, up2.f1);
    return fib_update(up1.f0+newF0, up1.f1+newF1, up1.start);
}

mod_num addFibsToInterval(segtree::node_info curNode, mod_num curItem, fib_update curUpdate) {
    mod_num wholePrefixSum = calcCustomFibPartial(curNode.rightB-curUpdate.start, curUpdate.f0, curUpdate.f1);
    mod_num unnecessaryPrefixSum = calcCustomFibPartial(curNode.leftB-curUpdate.start-1, curUpdate.f0, curUpdate.f1);
    return curItem+wholePrefixSum-unnecessaryPrefixSum;
}

segtree::segtree<mod_num, fib_update> segmentTree;

int main() {
    scanf(INT64 " " INT64, &numNums, &numQueries);
    num_nums i;
    REP(i, numNums) scanf(INT64, &(arr[i].val));
    
    fibs[0] = mod_num(0), fibs[1] = mod_num(1);
    for (i = 2; i <= numNums+10; ++i) fibs[i] = fibs[i-1]+fibs[i-2];
    
    segmentTree = segtree::segtree<mod_num, fib_update>(arr, numNums, mod_num(0), addFibsToInterval);
    
    while (numQueries--) {
        query_type curType;
        num_nums start, end;
        scanf(INT64 " " INT64 " " INT64, &curType, &start, &end);
        --start, --end;
        if (curType == 1) segmentTree.updateInterval(start, end, fib_update(1, 1, start));
        else {
            mod_num queryAnswer = segmentTree.calcMerge(start, end);
            printf(INT64 "\n", queryAnswer.val);
        }
    }
    
    return 0;
}