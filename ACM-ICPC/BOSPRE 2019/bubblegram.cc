#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked

const char *ans(int64_t xp, int64_t yp, int64_t rp, int64_t xe, int64_t ye, int64_t re) {
  int64_t d = (xp - xe) * (xp - xe) + (yp - ye) * (yp - ye);
  if (((rp - re) * (rp - re)) >= d) {
    return "inside";
  } else if (d < (rp + re) * (rp + re)) {
    return "overlap";
  } else if (d > (rp + re) * (rp + re)) {
    return "outside";
  } else {
    return "touch";
  }
}

char inputLine[10000];

int main() {
  int64_t xp, yp, rp, xe, ye, re;
  while (true) {
    //cin >> xp >> yp >> rp >> xe >> ye >> re;                                                                                                 
    fgets(inputLine, 10000, stdin);
    if (feof(stdin)) break;
    sscanf(inputLine, "%" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64, &xp, &yp, &rp, &xe, &ye, &re);
    const char *answer = ans(xp, yp, rp, xe, ye, re);
    printf("%" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %s\n", xp, yp, rp, xe, ye, re, answer);
  }
}
