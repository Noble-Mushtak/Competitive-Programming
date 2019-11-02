#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_fish;
typedef int64_t num_fishmongers;
typedef int64_t fish;
typedef int64_t price;

std::priority_queue<fish> fishWeights;
std::priority_queue<std::tuple<price, num_fish>> fishMongers;

int main() {
    num_fish numFish;
    num_fishmongers numFishmongers;
    scanf(INT64 " " INT64, &numFish, &numFishmongers);
    
    num_fish i;
    REP(i, numFish) {
        fish storeFish;
        scanf(INT64, &storeFish);
        fishWeights.push(storeFish);
    }
    REP(i, numFishmongers) {
        num_fish numWilling;
        price curPrice;
        scanf(INT64 " " INT64, &numWilling, &curPrice);
        fishMongers.push(std::tuple<price, num_fish>(curPrice, numWilling));
    }
    price answer = 0;
    while (!fishWeights.empty() && !fishMongers.empty()) {
        auto curMonger = fishMongers.top();
        num_fish numWilling = std::get<1>(curMonger);
        price curPrice = std::get<0>(curMonger);
        fishMongers.pop();
        REP(i, numWilling) {
            if (fishWeights.empty()) break;
            fish storeFish = fishWeights.top();
            answer += storeFish*curPrice;
            fishWeights.pop();
        }
    }
    printf(INT64 "\n", answer);
    
    return 0;
}