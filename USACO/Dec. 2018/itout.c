#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

FILE *in, *out;

typedef long long num_cows;
typedef long long cow;

num_cows numCows, factorial[10] = {1, 1, 2, 6, 24, 120, 720}, subsetLength, subset[100010], curSubsetLength, curSubset[100010];
cow arr[100010], arr2[100010];

int main() {
    num_cows bits, i, j, curElem, indexOf, temp;
    
    in = fopen("itout.in", "r");
    fscanf(in, "%lli %lli", &numCows, &temp);
    REPEAT(i, numCows) {
        fscanf(in, "%lli", arr+i);
        arr[i]--;
    }
    fclose(in);

    curSubsetLength = 7;
    REPEAT(bits, (1 << numCows)) {
        subsetLength = 0;
        REPEAT(i, numCows) if ((bits >> i) & 1) subset[subsetLength++] = i;
        REPEAT(i, numCows) arr2[i] = arr[i];
        if ((subsetLength > 0) && (subsetLength < curSubsetLength)) REPEAT(i, factorial[numCows]) {
            curElem = subset[i % subsetLength];
            indexOf = 0;
            while (arr2[indexOf] != curElem) indexOf++;
            while ((indexOf+1 < numCows) && (arr2[indexOf] > arr2[indexOf+1])) {
                temp = arr2[indexOf+1];
                arr2[indexOf+1] = arr2[indexOf];
                arr2[indexOf] = temp;
                indexOf++;
            }
            while ((indexOf > 0) && (arr2[indexOf] < arr2[indexOf-1])) {
                temp = arr2[indexOf-1];
                arr2[indexOf-1] = arr2[indexOf];
                arr2[indexOf] = temp;
                indexOf--;
            }
            //printf("%lli | %lli %lli %lli %lli\n", bits, arr2[0],arr2[1],arr2[2],arr2[3]);
            REPEAT(j, numCows) if (arr2[j] != j) break;
            if (j == numCows) {
                curSubsetLength = subsetLength;
                REPEAT(i, subsetLength) curSubset[i] = subset[i];
                break;
            }
        }
    }
    
    out = fopen("itout.out", "w");
    fprintf(out, "%lli\n", curSubsetLength);
    REPEAT(i, curSubsetLength) fprintf(out, "%lli\n", curSubset[i]+1);
    fclose(out);
    
    exit(0);
}