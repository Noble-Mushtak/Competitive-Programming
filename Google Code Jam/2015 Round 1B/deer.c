#include <stdio.h>
#include <stdlib.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;
#define FASTIO(lvalue) (lvalue = getchar())
#define FASTEX(lvalue, char) (lvalue = lvalue*10+(char-'0'))
#define POPQUEUE(arr, len) memmove(arr, arr+1, len*sizeof(arr[0]))
#define REMOVEELEM(arr, off, len) memmove(arr+off, arr+(off+1), (len-off)*sizeof(arr[0]))
#define REMOVEELEMS(arr, off, len, num) memmove(arr+off, arr+(off+num), (len-off)*sizeof(arr[0]))
//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef byte test_cases;
typedef short degree;
typedef short num_groups;
typedef byte num_hikers;
typedef long speed;
typedef struct {
    degree pos;
    speed fastness;
} hiker;
typedef byte num_encounters;
typedef long product;
num_groups hikerGroups;
num_hikers groupLength, place;
hiker hikers[10];
num_encounters answer;
product deerToEnd, hikerToDeer;

int main() {
    char store;
    test_cases numTestCases = 0, l;
    hiker storeHiker;
    degree storeDegree;
    num_groups i;
    num_hikers j;
    while (FASTIO(store) != '\n') FASTEX(numTestCases, store);
    
    REPEAT(l, numTestCases) {
        hikerGroups = place = answer = 0;
        while (FASTIO(store) != '\n') FASTEX(hikerGroups, store);
        REPEAT(i, hikerGroups) {
            groupLength = 0;
            hikers[place].pos = hikers[place].fastness = 0;
            while (FASTIO(store) != ' ') FASTEX(hikers[place].pos, store);
            while (FASTIO(store) != ' ') FASTEX(groupLength, store);
            while (FASTIO(store) != '\n') FASTEX(hikers[place].fastness, store);
            REPEAT(j, groupLength-1) {
                hikers[place+j+1].pos = hikers[place+j].pos;
                hikers[place+j+1].fastness = hikers[place+j].fastness+1;
            }
            place += groupLength;
        }
        if ((hikers[0].pos > hikers[1].pos) || (hikers[0].pos == hikers[1].pos && hikers[0].fastness > hikers[1].fastness)) storeHiker = hikers[0], hikers[0] = hikers[1], hikers[1] = storeHiker;
        //deerToEnd = ((float)(360-hikers[0].pos))/((float)hikers[0].fastness);
        //hikerToDeer = ((float)(360-hikers[1].pos))/((float)hikers[1].fastness);
        hikerToDeer = 360-hikers[1].pos;
        hikerToDeer *= hikers[0].fastness;
        deerToEnd = 360-hikers[0].pos;
        deerToEnd *= hikers[1].fastness;
        if (hikerToDeer > deerToEnd) answer = 1;
        else {
            //hikerToDeer += ((float)360)/((float)hikers[1].fastness);
            hikerToDeer += 360*hikers[0].fastness;
            answer = (hikerToDeer < deerToEnd);
        }
        printf("%li %li %hhi\n", hikerToDeer, deerToEnd, answer);
        printf("Case #%hhi: %hhi\n", l+1, answer);
    }
    
    exit(0);
}