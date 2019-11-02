/*
   PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=490
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
#define printf(...) 1
typedef signed char byte;
#define SENTINEL 1000000001

typedef long num_cows;
typedef long limit;

int compareCows(const void *ptr1, const void *ptr2) {
    num_cows store1 = *(num_cows*)ptr1, store2 = *(num_cows*)ptr2;
    store1 %= SENTINEL;
    store2 %= SENTINEL;
    return store1-store2;
}

FILE *in, *out;
num_cows listLength, list[50000], answer = 0;
limit lower, upper, upTo = 0;

int main() {
    num_cows i, listEntry;
    char store[3];
    
    in = fopen("learning.in", "r");
    fscanf(in, "%li %li %li\n", &listLength, &lower, &upper);
    REPEAT(i, listLength) {
        fscanf(in, "%s %li", store, &listEntry);
        list[i] = listEntry;
        if (store[0] == 'S') list[i] += SENTINEL;
    }
    fclose(in);
    
    qsort(list, listLength, sizeof(num_cows), compareCows);
    #define GETVAL(i) (list[i] % SENTINEL)
    #define GETBOOL(i) (list[i] > SENTINEL)
    printf("%li %li\n", lower, upper);
    REPEAT(i, listLength) {
        if (upTo == upper) break;
        if (i+1 < listLength) {
            if (GETVAL(i+1) < lower) continue;
            if (i && GETVAL(i-1) < lower && GETVAL(i) >= lower) continue;
            if (GETVAL(i) < lower && GETVAL(i+1) >= lower) {
                if (GETBOOL(i)) {
                    answer = (GETVAL(i+1)-GETVAL(i)-1)/2;
                    answer -= lower-GETVAL(i)-1;
                    if (answer < 0) answer = 0;
                    if ((GETVAL(i)+GETVAL(i-1))/2-1 > upper) {
                        answer -= (GETVAL(i)+GETVAL(i-1))/2-upper;
                        upTo = upper;
                    }
                    if (!GETBOOL(i+1) && !((GETVAL(i+1)-GETVAL(i)) % 2) && (GETVAL(i+1)+GETVAL(i))/2 >= lower) answer++;
                    printf("%li\n", answer);
                }
                if (GETBOOL(i+1)) {
                    answer += (GETVAL(i+1)-GETVAL(i))/2+1;
                    if (upper < GETVAL(i)) {
                        answer -= (GETVAL(i)-GETVAL(i-1))/2+1;
                        if ((GETVAL(i)+GETVAL(i-1))/2 <= upper) answer += upper-(GETVAL(i)+GETVAL(i-1))/2+1;
                        upTo = upper;
                    }
                    if (lower > (GETVAL(i+1)+GETVAL(i))/2+1) answer -= lower-(GETVAL(i+1)+GETVAL(i))/2-1;
                }
                if (upTo != upper) upTo = GETVAL(i+1);
            } else if (!i && GETVAL(i) >= lower) {
                if (GETBOOL(i)) {
                    if (GETVAL(i) > upper) {
                        answer = upper-lower+1;
                        upTo = upper;
                    } else answer = GETVAL(i)-lower+1;
                }
                if (upTo != upper) upTo = GETVAL(i);
            } else {
                if (GETBOOL(i-1)) {
                    answer += (GETVAL(i)-GETVAL(i-1)-1)/2;
                    if ((GETVAL(i)+GETVAL(i-1))/2-1 > upper) {
                        answer -= (GETVAL(i)+GETVAL(i-1))/2-upper;
                        upTo = upper;
                    }
                    if (!GETBOOL(i) && !((GETVAL(i)-GETVAL(i-1)) % 2) && (GETVAL(i)+GETVAL(i-1))/2 >= lower) answer++;
                }
                if (GETBOOL(i)) {
                    answer += (GETVAL(i)-GETVAL(i-1))/2+1;
                    if (upper < GETVAL(i)) {
                        answer -= (GETVAL(i)-GETVAL(i-1))/2+1;
                        if ((GETVAL(i)+GETVAL(i-1))/2 <= upper) answer += upper-(GETVAL(i)+GETVAL(i-1))/2+!GETBOOL(i-1);
                        upTo = upper;
                    }
                }
                if (upTo != upper) upTo = GETVAL(i);
            }
        } else {
            if (GETVAL(i) < lower) {
                if (GETBOOL(i)) answer = upper-lower+1;
            } else {
                if (GETBOOL(i-1)) {
                    answer += (GETVAL(i)-GETVAL(i-1)-1)/2;
                    if ((GETVAL(i)+GETVAL(i-1))/2-1 > upper) answer -= (GETVAL(i)+GETVAL(i-1))/2-upper;
                    if (!GETBOOL(i) && !((GETVAL(i)-GETVAL(i-1)) % 2) && (GETVAL(i)+GETVAL(i-1))/2 >= lower) answer++;
                }
                if (GETBOOL(i)) {
                    answer += (GETVAL(i)-GETVAL(i-1))/2+1;
                    if (upper < GETVAL(i)) {
                        answer -= (GETVAL(i)-GETVAL(i-1))/2+1;
                        if ((GETVAL(i)+GETVAL(i-1))/2 <= upper) answer += upper-(GETVAL(i)+GETVAL(i-1))/2+1;
                    }
                    if (GETVAL(i) < upper) answer += upper-GETVAL(i);
                }
            }
        }
        printf("%li %li %li\n", answer, GETVAL(i), GETBOOL(i));
    }
    #undef GETVAL
    #undef GETBOOL
    
    out = fopen("learning.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}