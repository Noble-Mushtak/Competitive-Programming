#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; ++token)

#ifdef TESTING
#define DEBUG(...) __VA_ARGS__
#else
#define DEBUG(...)
#endif

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t capacity, numStations;
    std::cin >> capacity >> numStations;
    int64_t numPeople = 0;
    while (numStations--) {
        int64_t numLeft, numEnt, numStay;
        std::cin >> numLeft >> numEnt >> numStay;
        numPeople -= numLeft;
        numPeople += numEnt;
        if ((numPeople < 0) || (numPeople > capacity) || ((numStay > 0) && (numPeople < capacity))) {
            std::cout << "impossible\n";
            exit(0);
        }
    }
    std::cout << "possible\n";
    
    return 0;
}
