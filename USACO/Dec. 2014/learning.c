#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
/*#define SET(arr, e1, e2) ( \
     ((arr[0] = e1) || true) && \
     ((arr[1] = e2)) \
)*/
typedef signed char byte;

int lessThan(const void *a, const void *b) {
    long num1 = *(long*)a, num2 = *(long*)b;
    return (num1 % 1000000001)-(num2 % 1000000001);
}

FILE *in, *out;
long lowerLimit, upperLimit, cows[50000], minimum, maximum, store1, store2, answer = 0, numCows;
char store;

int main() {
    long i;
    
    in = fopen("learning.in", "r");
    fscanf(in, "%hi %li %li\n", &numCows, &lowerLimit, &upperLimit);
    REPEAT(i, numCows) {
        fscanf(in, "%c", &store);
        if (store == 'N') fscanf(in, "S");
        fscanf(in, "%li\n", cows+i);
        if (store == 'S') cows[i] += 1000000001;
    }
    fclose(in);
    
    qsort(cows, numCows, sizeof(long), lessThan);
    #define GETWEIGHT(ind) (cows[ind] % 1000000001)
    #define GETSPOTS(ind) (cows[ind] > 1000000001)
    REPEAT(i, numCows) printf("%s %li\n", GETSPOTS(i) ? "S" : "NS", GETWEIGHT(i));
    REPEAT(i, numCows) {
        if (i > 0 && GETWEIGHT(i-1) > upperLimit) break;
        if ((i+1 == numCows || GETWEIGHT(i+1) > lowerLimit) && GETSPOTS(i)) {
            minimum = GETWEIGHT(i) < lowerLimit ? lowerLimit : GETWEIGHT(i);
            maximum = i+1 != numCows ? (GETWEIGHT(i+1) > upperLimit+1 ? upperLimit+1 : GETWEIGHT(i+1)) : upperLimit+1;
            printf("(%li %li %li) %li ", i, minimum, maximum, answer);
            if (maximum > minimum && (i+1 == numCows || GETSPOTS(i+1))) {
                answer += maximum-minimum;
                printf("(n %li) ", maximum-minimum);
            }
            else if (maximum > minimum) {
                store1 = (GETWEIGHT(i+1)-minimum)/2+1;
                store2 = maximum-minimum;
                printf("(2 %li) ", store1 < store2 ? store1 : store2);
                answer += store1 < store2 ? store1 : store2;
            }
            if (i > 0 && !GETSPOTS(i-1) && GETWEIGHT(i) > lowerLimit) {
                store2 = GETWEIGHT(i-1);
                store1 = (minimum-store2)/2;
                if (minimum > maximum) store1 -= minimum-maximum;
                if (store2 < lowerLimit) store1 -= lowerLimit-(store2+minimum)/2;
                printf("(s %li %li %li) ", store1 > 0 ? store1 : 0, store2, minimum);
                answer += store1 > 0 ? store1 : 0;
            }
            printf("%li\n", answer);
        }
    }
    
    out = fopen("learning.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}