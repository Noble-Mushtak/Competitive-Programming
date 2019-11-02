/*
    PROB: http://usaco.org/index.php?page=viewproblem2&cpid=436
    Only Passes Cases 1-4
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;
#define FASTIO(lvalue, file) (lvalue = fgetc(file))
#define FASTEX(lvalue, char) (lvalue = lvalue*10+(char-'0'))
#define POPQUEUE(arr, len) memmove(arr, arr+1, len*sizeof(arr[0]))
#define REMOVEELEM(arr, off, len) memmove(arr+off, arr+(off+1), (len-off)*sizeof(arr[0]))
#define REMOVEELEMS(arr, off, len, num) memmove(arr+off, arr+(off+num), (len-off)*sizeof(arr[0]))
#define SET(arr, e1, e2) ( \
    (arr[0] = e1), \
    (arr[1] = e2) \
)

typedef byte breed;
typedef byte num_breeds;
typedef long num_cows;
typedef long data;

FILE *in, *out;
num_cows length, numBreeds[100000][8];
num_breeds numNeeded;
data input[100000][2], *realInput[100000], answer;

int compareData(const void *ptr1, const void *ptr2) {
    data *data1 = *(data**)ptr1, *data2 = *(data**)ptr2;
    return (data1[0] > data2[0])-(data1[0] < data2[0]);
}

int main() {
    char store;
    num_cows i, j, expected, cur;
    num_breeds has, k;
    data dist;
    bool equal;
    
    in = fopen("fairphoto.in", "r");
    while (FASTIO(store, in) != ' ') FASTEX(length, store);
    while (FASTIO(store, in) != '\n') FASTEX(numNeeded, store);
    REPEAT(i, length) {
        while (FASTIO(store, in) != ' ') FASTEX(input[i][0], store);
        while (FASTIO(store, in) != '\n') FASTEX(input[i][1], store);
        input[i][1]--;
        realInput[i] = input[i];
    }
    fclose(in);
    
    
    qsort(realInput, length, sizeof(data*), compareData);
    REPEAT(i, length) {
        if (i) memcpy(numBreeds[i], numBreeds[i-1], sizeof(numBreeds[i-1]));
        numBreeds[i][realInput[i][1]]++;
    }
    REPEAT(i, length) REPEAT(j, i) {
        has = 0, equal = true;
        REPEAT(k, 8) if ((cur = (numBreeds[i][k]-(j ? numBreeds[j-1][k] : 0)))) {
            if (!has) expected = cur;
            else if (cur != expected) {
                equal = false;
                break;
            }
            has++;
        }
        if (has >= numNeeded && equal && answer < (dist = (realInput[i][0]-realInput[j][0]))) answer = dist;
    }
    if (answer == 0) answer = -1;
    
    out = fopen("fairphoto.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}