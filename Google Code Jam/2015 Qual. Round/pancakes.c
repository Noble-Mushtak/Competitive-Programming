#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REPEAT(token, num) for (token = 0; token < num; token++)
typedef signed char byte;
#define FASTIO(lvalue) (lvalue = getchar())
#define FASTEX(lvalue, char) (lvalue = lvalue*10+(char-'0'))
#define POPQUEUE(arr, len) memmove(arr, arr+1, len*sizeof(arr[0]))
#define REMOVEELEM(arr, off, len) memmove(arr+off, arr+(off+1), (len-off)*sizeof(arr[0]))
#define REMOVEELEMS(arr, off, len, num) memmove(arr+off, arr+(off+num), (len-off)*sizeof(arr[0]))
#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef byte test_cases;
typedef short num_pancakes;
typedef short num_stacks;
typedef short time;

num_pancakes max;
num_stacks quantities[1001], length;
time answer, curTime;

int main() {
    char store;
    test_cases numTestCases = 0, l;
    num_stacks i;
    num_pancakes storePancakes, sum;
    while (FASTIO(store) != '\n') FASTEX(numTestCases, store);
    
    REPEAT(l, numTestCases) {
        length = answer = curTime = max = 0;
        memset(quantities, 0, sizeof(quantities));
        while (FASTIO(store) != '\n') FASTEX(length, store);
        REPEAT(i, length) {
            storePancakes = 0;
            while (FASTIO(store) != ' ' && store != '\n') FASTEX(storePancakes, store);
            quantities[storePancakes]++;
            if (max < storePancakes) max = answer = storePancakes;
        }
        
        sum = 0;
        REPEAT(i, max+1) PRINTF("%i %i |", i, quantities[i]), sum += quantities[i]*i;
        PRINTF("%i %i %i %i\n", answer, curTime, max, sum);
        while (max > 1 && curTime < answer) {
            quantities[max/2] += quantities[max];
            quantities[max-max/2] += quantities[max];
            curTime += quantities[max];
            quantities[max] = 0;
            while (quantities[max] == 0) max--;
            if (answer > curTime+max) answer = curTime+max;
            sum = 0;
            REPEAT(i, max+1) PRINTF("%i %i |", i, quantities[i]), sum += quantities[i]*i;
            PRINTF("%i %i %i %i\n", answer, curTime, max, sum);
        }
        
        printf("Case #%hhi: %hi\n", l+1, answer);
    }
    
    exit(0);
}