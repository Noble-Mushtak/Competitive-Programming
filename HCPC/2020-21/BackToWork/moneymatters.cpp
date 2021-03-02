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

int64_t money[10010];
std::list<int64_t> friends[10010];
int64_t components[10010];

void markComponent(int64_t first, int64_t mark) {
    std::queue<int64_t> people;
    people.push(first);
    while (!people.empty()) {
        int64_t person = people.front();
        people.pop();
        components[person] = mark;
        for (int64_t cur_friend : friends[person]) {
            if (components[cur_friend] == -1) {
                people.push(cur_friend);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int64_t numPeople, numFriendships;
    std::cin >> numPeople >> numFriendships;
    int64_t i;
    REP(i, numPeople) {
        std::cin >> money[i];
        components[i] = -1;
    }
    REP(i, numFriendships) {
        int64_t person1, person2;
        std::cin >> person1 >> person2;
        friends[person1].push_back(person2);
        friends[person2].push_back(person1);
    }
    int64_t numComponents = 0;
    REP(i, numPeople) {
        if (components[i] == -1) {
            markComponent(i, numComponents);
            numComponents++;
        }
    }
    REP(i, numComponents) {
        int64_t j, sum = 0;
        REP(j, numPeople) {
            if (components[j] == i) sum += money[j];
        }
        if (sum < 0) {
            std::cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
    std::cout << "POSSIBLE\n";

    return 0;
}
