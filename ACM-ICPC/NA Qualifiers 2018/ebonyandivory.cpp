#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>

#define REP(token, num) for (token = 0; token < num; token++)

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t difficulty;
typedef int64_t num_difficulties;
typedef int64_t finger;
typedef int64_t note;
typedef int64_t num_notes;

num_notes numNotes;
note notes[20000];
num_difficulties whiteWhite, whiteBlack, blackWhite, blackBlack;
difficulty difficulties[2][2][10][10][20], minDifficulties[20000][10];
bool valid[2][2][10][10];

bool isBlack(note curNote) {
    note curNoteMod12 = curNote % 12;
    return (curNoteMod12 == 0) || (curNoteMod12 == 2) || (curNoteMod12 == 5) || (curNoteMod12 == 7) || (curNoteMod12 == 10);
}

bool isValid(note firstNote, note secondNote, finger firstFinger, finger secondFinger) {
    if (firstNote < secondNote) return valid[isBlack(firstNote)][isBlack(secondNote)][firstFinger][secondFinger];
    else return valid[isBlack(secondNote)][isBlack(firstNote)][secondFinger][firstFinger];
}

difficulty calcDifficulty(note firstNote, note secondNote, finger firstFinger, finger secondFinger) {
    if (firstNote < secondNote) return difficulties[isBlack(firstNote)][isBlack(secondNote)][firstFinger][secondFinger][secondNote-firstNote];
    else return difficulties[isBlack(secondNote)][isBlack(firstNote)][secondFinger][firstFinger][firstNote-secondNote];
}

int main() {
    scanf("%" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 " %" PRId64, &whiteWhite, &whiteBlack, &blackWhite, &blackBlack, &numNotes);
    
    num_difficulties i, j;
    finger startFinger, endFinger;
    REP(i, whiteWhite) {
        scanf("%" PRId64 " %" PRId64, &startFinger, &endFinger);
        valid[0][0][startFinger][endFinger] = true;
        REP(j, 12) scanf("%" PRId64, difficulties[0][0][startFinger][endFinger]+(j+1));
    }
    REP(i, whiteBlack) {
        scanf("%" PRId64 " %" PRId64, &startFinger, &endFinger);
        valid[0][1][startFinger][endFinger] = true;
        REP(j, 12) scanf("%" PRId64, difficulties[0][1][startFinger][endFinger]+(j+1));
    }
    REP(i, blackWhite) {
        scanf("%" PRId64 " %" PRId64, &startFinger, &endFinger);
        valid[1][0][startFinger][endFinger] = true;
        REP(j, 12) scanf("%" PRId64, difficulties[1][0][startFinger][endFinger]+(j+1));
    }
    REP(i, blackBlack) {
        scanf("%" PRId64 " %" PRId64, &startFinger, &endFinger);
        valid[1][1][startFinger][endFinger] = true;
        REP(j, 12) scanf("%" PRId64, difficulties[1][1][startFinger][endFinger]+(j+1));
    }
    
    num_notes l;
    REP(l, numNotes) scanf("%" PRId64, notes+l);
    finger storeFinger, storeFinger2;
    REP(storeFinger, 5) minDifficulties[0][storeFinger+1] = 0;
    REP(l, numNotes-1) {
        if (notes[l+1] == notes[l]) {
            REP(storeFinger, 5) minDifficulties[l+1][storeFinger+1] = minDifficulties[l][storeFinger+1];
            continue;
        }
        REP(storeFinger, 5) minDifficulties[l+1][storeFinger+1] = 1000000000;
        
        for (storeFinger = 1; storeFinger <= 5; storeFinger++) {
            for (storeFinger2 = 1; storeFinger2 <= 5; storeFinger2++) if (isValid(notes[l], notes[l+1], storeFinger, storeFinger2)) {
                minDifficulties[l+1][storeFinger2] = std::min(
                    minDifficulties[l+1][storeFinger2],
                    minDifficulties[l][storeFinger]+calcDifficulty(notes[l], notes[l+1], storeFinger, storeFinger2)
                );
            }
        }
    }
    difficulty answer = 1000000000;
    REP(storeFinger, 5) answer = std::min(answer, minDifficulties[numNotes-1][storeFinger+1]);
    printf("%" PRId64 "\n", answer);
    
    return 0;
}