#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <set>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t bard;
typedef int64_t num_bards;
typedef int64_t num_evenings;
typedef int64_t song;

num_bards numBards;
num_evenings numEvenings;
std::set<song> songs[200], allSongs;
bool presentNow[200];

int main() {
    scanf("%" PRId64 " %" PRId64, &numBards, &numEvenings);
    num_evenings i;
    num_bards storeBards, j;
    bard storeBard, storeBard2;
    //for (storeBard = 2; storeBard <= numBards; storeBard++) songs[storeBard].insert(storeBard), allSongs.insert(storeBard);
    
    REP(i, numEvenings) {
        scanf("%" PRId64, &storeBards);
        for (storeBard = 1; storeBard <= numBards; storeBard++) presentNow[storeBard] = false;
        REP(j, storeBards) {
            scanf("%" PRId64, &storeBard);
            presentNow[storeBard] = true;
        }
        if (presentNow[1]) {
            allSongs.insert(200+i);
            for (storeBard = 2; storeBard <= numBards; storeBard++) if (presentNow[storeBard]) songs[storeBard].insert(200+i);
        } else {
            for (storeBard = 2; storeBard <= numBards; storeBard++) if (presentNow[storeBard]) {
                for (auto it = songs[storeBard].begin(); it != songs[storeBard].end(); it++) {
                    for (storeBard2 = 2; storeBard2 <= numBards; storeBard2++) if (presentNow[storeBard2]) {
                        songs[storeBard2].insert(*it);
                    }
                }
            }
        }
        /*for (storeBard = 2; storeBard <= numBards; storeBard++) {
            for (auto it = songs[storeBard].begin(); it != songs[storeBard].end(); it++) printf("%" PRId64 "\n", *it);
            puts("");
        }
        puts("------------"); // */
    }
    puts("1");
    for (storeBard = 2; storeBard <= numBards; storeBard++) if (songs[storeBard] == allSongs) printf("%" PRId64 "\n", storeBard);
    return 0;
}