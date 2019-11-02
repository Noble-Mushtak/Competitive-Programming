/*
  PROB: http://usaco.org/index.php?page=viewproblem2&cpid=360
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
typedef char byte;
typedef long long_pair[2];
typedef long_pair* pair_arr;
#define repeat(token, num) for (token = 0; token < num; token++)
using namespace std;

ifstream in;
ofstream out;
short answer;
long wormholes[12][2];
pair_arr pairs;
byte numWormholes;
byte record[12];
long_pair _begPair1[1] = {{0, 1}};
long_pair _begPair2[2] = {{0, 1}, {2, 3}};
long_pair _begPair3[3] = {{0, 1}, {2, 3}, {4, 5}};
long_pair _begPair4[4] = {{0, 1}, {2, 3}, {4, 5}, {6, 7}};
long_pair _begPair5[5] = {{0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}};
long_pair _begPair6[6] = {{0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}, {10, 11}};
pair_arr begPairs[6];
long_pair _endPair1[1] = {{0, 1}};
long_pair _endPair2[2] = {{0, 3}, {1, 2}};
long_pair _endPair3[3] = {{0, 5}, {1, 4}, {2, 3}};
long_pair _endPair4[4] = {{0, 7}, {1, 6}, {2, 5}, {3, 4}};
long_pair _endPair5[5] = {{0, 9}, {1, 8}, {2, 7}, {3, 6}, {4, 5}};
long_pair _endPair6[6] = {{0, 11}, {1, 10}, {2, 9}, {3, 8}, {4, 7}, {5, 6}};
pair_arr endPairs[6];

#define getInd(num) num/2-1

/*void printPair(pair_arr pairing, byte length) {
    byte i;
    printf("{");
    repeat(i, length) {
        if (i) printf(", ");
        printf("{%li, %li}", pairing[i][0], pairing[i][1]);
    }
    printf("}\n");
}*/

bool equals(pair_arr arr1, pair_arr arr2, long dim1) {
    byte i, j;
    repeat(i, dim1) if (arr1[i][0] != arr2[i][0] || arr1[i][1] != arr2[i][1]) return false;
    return true;
}

long findPair(pair_arr pairing, int key) {
    byte i;
    repeat(i, 12) {
        if (pairing[i][0] == key) return pairing[i][1];
        if (pairing[i][1] == key) return pairing[i][0];
    }
    return 0;
}

bool checkPair(pair_arr pairing) {
    long leastX, curX, curY;
    byte i, j, moveTo, i2, recordNum;
    //printPair(pairing, numWormholes/2);
    repeat(i2, numWormholes) {
        moveTo = i = i2;
        //printf("%i: ", i);
        repeat(recordNum, numWormholes) {
            leastX = 1000000001;
            curX = wormholes[i][0];
            curY = wormholes[i][1];
            for (j = (i ? 0 : 1); j < numWormholes; j+1 == i ? j += 2 : j++) if (wormholes[j][1] == curY && wormholes[j][0] > curX && wormholes[j][0] < leastX) {
                leastX = wormholes[j][0];
                moveTo = j;
            }
            if (moveTo == i) {/*printf("NOMORE");*/break;}
            moveTo = findPair(pairing, moveTo);
            if (moveTo == i) {/*printf("REP\n\n");*/return true;}
            repeat(j, recordNum) if (record[j] == moveTo) {/*printf("REP(%i)\n\n", moveTo);*/return true;}
            record[recordNum] = i;
            i = moveTo;
            //printf("%i ", i);
        }
        //printf("END\n");
    }
    /*printf("\n");*/return false;
}

long smallest(long *arr, byte length) {

    long smallest = -1;

    byte i;

    repeat(i, length) if (smallest == -1 || arr[i] < smallest) smallest = arr[i];

    return smallest;

}
long next(long *arr, byte length, long item) {
    long nextItem = -1;
    byte i;
    repeat(i, length) if (arr[i] > item && (nextItem == -1 || arr[i] < nextItem)) nextItem = arr[i];
    return nextItem;
}
long biggest(long *arr, byte length) {
    long biggest = -1;
    byte i;
    repeat(i, length) if (arr[i] > biggest) biggest = arr[i];
    return biggest;
}

void nextPair(pair_arr pairing) {
    byte i, j;
    long lastThree[3], store, store2;
    lastThree[0] = pairing[getInd(numWormholes)-1][1];
    lastThree[1] = pairing[getInd(numWormholes)][0];
    lastThree[2] = pairing[getInd(numWormholes)][1];
    if (lastThree[0] < lastThree[1] || lastThree[0] < lastThree[2]) {
        pairing[getInd(numWormholes)-1][1] = store = next(lastThree, 3, lastThree[0]);
        pairing[getInd(numWormholes)][0] = (store == lastThree[1]) ? lastThree[2] : lastThree[1];
        pairing[getInd(numWormholes)][1] = lastThree[0];
    } else if (numWormholes > 5) {
        long lastFive[5];
        lastFive[0] = pairing[getInd(numWormholes)-2][1];
        lastFive[1] = pairing[getInd(numWormholes)-1][0];
        repeat(i, 3) lastFive[i+2] = lastThree[i];
        if (lastFive[0] != biggest(lastFive, 5)) {
            long orderedFour[4];
            pairing[getInd(numWormholes)-2][1] = store2 = next(lastFive, 5, lastFive[0]);
            orderedFour[0] = smallest(lastFive, 5);
            for (i = 1; i < 4; i++) {
                store = next(lastFive, 5, orderedFour[i-1]);
                if (store == store2) store = next(lastFive, 5, store);
                orderedFour[i] = store;
            }
            repeat(i, 2) repeat(j, 2) pairing[getInd(numWormholes)-i][j] = orderedFour[2-2*i+j];
        } else if (numWormholes > 7) {
            long lastSeven[7];
            lastSeven[0] = pairing[getInd(numWormholes)-3][1];
            lastSeven[1] = pairing[getInd(numWormholes)-2][0];
            repeat(i, 5) lastSeven[i+2] = lastFive[i];
            if (lastSeven[0] != biggest(lastSeven, 7)) {
                long orderedSix[6];
                pairing[getInd(numWormholes)-3][1] = store2 = next(lastSeven, 7, lastSeven[0]);
                orderedSix[0] = smallest(lastSeven, 7);
                for (i = 1; i < 6; i++) {
                    store = next(lastSeven, 7, orderedSix[i-1]);
                    if (store == store2) store = next(lastSeven, 7, store);
                    orderedSix[i] = store;
                }
                repeat(i, 3) repeat(j, 2) pairing[getInd(numWormholes)-i][j] = orderedSix[4-2*i+j];
            } else if (numWormholes > 9) {
                long lastNine[9];
                lastNine[0] = pairing[getInd(numWormholes)-4][1];
                lastNine[1] = pairing[getInd(numWormholes)-3][0];
                repeat(i, 7) lastNine[i+2] = lastSeven[i];
                if (lastNine[0] != biggest(lastNine, 9)) {
                    long orderedEight[8];
                    pairing[getInd(numWormholes)-4][1] = store2 = next(lastNine, 9, lastNine[0]);
                    orderedEight[0] = smallest(lastNine, 9);
                    for (i = 1; i < 8; i++) {
                        store = next(lastNine, 9, orderedEight[i-1]);
                        if (store == store2) store = next(lastNine, 9, store);
                        orderedEight[i] = store;
                    }
                    repeat(i, 4) repeat(j, 2) pairing[getInd(numWormholes)-i][j] = orderedEight[6-2*i+j];
                } else if (numWormholes > 11) {
                    long lastEleven[11], orderedTen[10];
                    lastEleven[0] = pairing[0][1];
                    lastEleven[1] = pairing[1][0];
                    repeat(i, 9) lastEleven[i+2] = lastNine[i];
                    pairing[0][1] = store2 = next(lastEleven, 11, lastEleven[0]);
                    orderedTen[0] = smallest(lastEleven, 11);
                    for (i = 1; i < 10; i++) {
                        store = next(lastEleven, 11, orderedTen[i-1]);
                        if (store == store2) store = next(lastEleven, 11, store);
                        orderedTen[i] = store;
                    }
                    repeat(i, 5) repeat(j, 2) pairing[getInd(numWormholes)-i][j] = orderedTen[8-2*i+j];
                }
            }
        }
    }
}

void checkAllPairs() {
    pairs = begPairs[getInd(numWormholes)];
    if (checkPair(pairs)) answer++;
    while (!equals(pairs, endPairs[getInd(numWormholes)], numWormholes/2)) {
        nextPair(pairs);
        if (checkPair(pairs)) answer++;
    }
}

int main() {
    byte i;
    char str[3];
    //Init begPairs, endPairs
    begPairs[0] = _begPair1+0;begPairs[1] = _begPair2+0;begPairs[2] = _begPair3+0;begPairs[3] = _begPair4+0;begPairs[4] = _begPair5+0;begPairs[5] = _begPair6+0;endPairs[0] = _endPair1+0;endPairs[1] = _endPair2+0;endPairs[2] = _endPair3+0;endPairs[3] = _endPair4+0;endPairs[4] = _endPair5+0;endPairs[5] = _endPair6+0;
    
    in.open("wormhole.in");
    //in >> numWormholes; treats numWormholes as an actual character instead of a byte.
    str[0] = in.get();
    if (str[0] == '1') {
        str[1] = in.get();
        str[2] = '\0';
    } else str[1] = '\0';
    numWormholes = (byte) atoi(str);
    repeat(i, numWormholes) in >> wormholes[i][0] >> wormholes[i][1];
    //printPair(wormholes+0, numWormholes);
    //printf("\n");
    in.close();
    
    checkAllPairs();
    
    out.open("wormhole.out");
    out << answer << "\n";
    out.close();
    
    return 0;
}