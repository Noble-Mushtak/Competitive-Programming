#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef signed char byte;
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline void POPQUEUE(void *arr, size_t length, size_t itemSize) { memmove(arr, arr+itemSize, length*itemSize); }
static inline void REMOVEELEM(void *arr, size_t offset, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+1)*itemSize), (length-offset)*itemSize); }
static inline void REMOVEELEMS(void *arr, size_t offset, size_t numElems, size_t length, size_t itemSize) { memmove(arr+(offset*itemSize), arr+((offset+numElems)*itemSize), (length-offset)*itemSize); }
#define printf(...) 1

typedef long long num_rooms;
typedef long long num_cows;
typedef byte num_doors;
typedef long long distance;

FILE *in, *out;
num_cows rooms[1000];
num_rooms perimeter;
num_doors doorsUnlocked;
distance answer;

int main() {
    char store;
    num_rooms i, j, k, l;
    distance tempAnswer, tempDist, tempDist2, tempDist3;
    
    in = fopen("cbarn.in", "r");
    fscanf(in, "%lli %hhi", &perimeter, &doorsUnlocked);
    REPEAT(i, perimeter) fscanf(in, "%lli", rooms+i);
    fclose(in);

    answer = -1;
    if (doorsUnlocked == 1) {
        REPEAT(i, perimeter) {
            tempAnswer = 0;
            REPEAT(j, perimeter) {
                tempDist = j-i;
                if (tempDist < 0) tempDist += perimeter;
                tempAnswer += rooms[j]*tempDist;
            }
            if (answer == -1 || tempAnswer < answer) answer = tempAnswer;
        }
    }
    else if (doorsUnlocked == 2) {
        REPEAT(i, perimeter) {
            REPEAT(j, i) {
                tempAnswer = 0;
                REPEAT(k, perimeter) {
                    tempDist = k-j;
                    if (tempDist < 0) tempDist += perimeter;
                    tempDist2 = k-i;
                    if (tempDist2 < 0) tempDist2 += perimeter;
                    if (tempDist2 < tempDist) tempDist = tempDist2;
                    tempAnswer += rooms[k]*tempDist;
                }
                if (answer == -1 || tempAnswer < answer) answer = tempAnswer, printf("%lli %lli %lli\n", i, j, tempAnswer);
            }
        }
    }
    else if (doorsUnlocked == 3) {
        REPEAT(i, perimeter) {
            REPEAT(j, i) {
                REPEAT(l, j) {
                    tempAnswer = 0;
                    REPEAT(k, perimeter) {
                        tempDist = k-j;
                        if (tempDist < 0) tempDist += perimeter;
                        tempDist2 = k-i;
                        if (tempDist2 < 0) tempDist2 += perimeter;
                        if (tempDist2 < tempDist) tempDist = tempDist2;
                        tempDist3 = k-l;
                        if (tempDist3 < 0) tempDist3 += perimeter;
                        if (tempDist3 < tempDist) tempDist = tempDist3;
                        tempAnswer += rooms[k]*tempDist;
                    }
                    if (answer == -1 || tempAnswer < answer) answer = tempAnswer, printf("%lli %lli %lli\n", i, j, tempAnswer);
                }
            }
        }
    }
    else exit(1);
    
    out = fopen("cbarn.out", "w");
    fprintf(out, "%lli\n", answer);
    fclose(out);
    
    exit(0);
}