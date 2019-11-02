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
#define SET(arr, e1, e2) ( \
    (arr[0] = e1), \
    (arr[1] = e2) \
)

typedef long digit;
digit pow10s[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
typedef byte num_digits;
typedef digit bignum[12];
bignum zero, one, two;
const size_t BIGNUM_SIZE = 12*sizeof(digit);

void addBignums(bignum *result, bignum addend) {
    const digit modulo = 1000000000;
    digit overflow;
    num_digits i;
    REPEAT(i, 12) {
        (*result)[i] += addend[i]+overflow;
        overflow = (*result)[i]/modulo;
        (*result)[i] %= modulo;
    }
}
void inputBignum(bignum *input) {
    num_digits pos = 0, cur = 0, length = 0, i;
    char storage[108];
    memset(*input, 0, BIGNUM_SIZE);
    
    while (FASTIO(storage[length]) != ' ' && storage[length] != '\n') length++;
    for (i = length-1; i >= 0; i--) {
        (*input)[pos] += pow10s[cur]*(storage[i]-'0');
        if (cur == 8) pos++, cur = 0;
        else cur++;
    }
}
void printBignum(bignum query) {
    bignum output;
    num_digits i, j;
    bool started = false;
    memcpy(output, query, BIGNUM_SIZE);
    
    for (i = 11; i >= 0; i--) {
        if (!started && (output[i] || !i)) printf("%li", output[i]), started = true;
        else if (started) for (j = 8; j >= 0; j--) putchar((output[i]/pow10s[j])+'0'), output[i] %= pow10s[j];
    }
    putchar('\n'), fflush(stdout);
}

typedef long num_queries;
bignum answer, stack[70000] = {{1}};
num_queries stackPos = 1;

int main() {
    char store;
    bignum storeBignum;
    num_queries l, j;
    memset(zero, 0, BIGNUM_SIZE), memset(one, 0, BIGNUM_SIZE), memset(two, 0, BIGNUM_SIZE), memset(answer, 0, BIGNUM_SIZE);
    one[0] = answer[0] = 1, two[0] = 2;
    
    while (stackPos) {
        stackPos--;
        printBignum(stack[stackPos]);
        REPEAT(l, 2) {
            inputBignum(&storeBignum);
            if (memcmp(storeBignum, zero, BIGNUM_SIZE)) {
                //if (storeBignum[0] == 0) {
                
                //}
                addBignums(&answer, one);
                if (stackPos == 70000) while (true);
                else memcpy(stack[stackPos], storeBignum, BIGNUM_SIZE), stackPos++;
            }
        }
    }
    printf("Answer "), printBignum(answer);
    
    exit(0);
}