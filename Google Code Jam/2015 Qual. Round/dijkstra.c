/* Small Input Only */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
typedef short num_chars;
typedef byte quat;

num_chars length, repeat, stringLength;
quat string[10050], soFar, I = 2, J = 3, K = 4, IJ, IJK;
bool reachedI, reachedJ;

quat mult(quat a, quat b) {
    //(1,2,3,4) -> (1,i,j,k), -n -> -q
    byte sign = ((a > 0) ^ (b > 0)) ? -1 : 1;
    quat first = (a > 0) ? a : -a, second = (b > 0) ? b : -b;
    if (first == 1) return sign*second;
    if (second == 1) return sign*first;
    if (first == second) return -sign;
    if (first == I && second == J) return sign*K;
    if (first == J && second == I) return -sign*K;
    if (first == I && second == K) return -sign*J;
    if (first == K && second == I) return sign*J;
    if (first == J && second == K) return sign*I;
    if (first == K && second == J) return -sign*I;
}

int main() {
    char store;
    num_chars i;
    test_cases numTestCases = 0, l;
    while (FASTIO(store) != '\n') FASTEX(numTestCases, store);
    IJ = mult(I, J);
    IJK = mult(IJ, K);
    PRINTF("%hhi%hhi%hhi", I, IJ, IJK);
    
    REPEAT(l, numTestCases) {
        length = repeat = 0, soFar = 1;
        reachedI = reachedJ = false;
        memset(string, 0, sizeof(string));
        while (FASTIO(store) != ' ') FASTEX(length, store);
        while (FASTIO(store) != '\n') FASTEX(repeat, store);
        stringLength = length*repeat;
        REPEAT(i, length) string[i] = getchar()-'i'+2;
        getchar(); //Newline
        REPEAT(i, repeat-1) memcpy(string+(i+1)*length, string, length*sizeof(char));
        
        REPEAT(i, stringLength) {
            soFar = mult(soFar, string[i]);
            PRINTF("%hhi%hhi", soFar, string[i]);
            reachedI |= (soFar == I);
            reachedJ |= (reachedI && soFar == IJ);
            PRINTF("%hhi%hhi", reachedI, reachedJ);
        }
        PRINTF("\n%hhi %hhi %hhi\n", reachedI, reachedJ, soFar);
        printf("Case #%hhi: %s\n", l+1, (reachedI && reachedJ && soFar == IJK) ? "YES" : "NO");
    }
    
    exit(0);
}