#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
typedef byte dimen;

dimen rows, columns, omino;
bool answer;

int main() {
    char store;
    test_cases numTestCases, l;
    dimen i;
    while (FASTIO(store) != '\n') FASTEX(numTestCases, store);
    
    REPEAT(l, numTestCases) {
        omino = rows = columns = 0, answer = true;
        while (FASTIO(store) != ' ') FASTEX(omino, store);
        while (FASTIO(store) != ' ') FASTEX(rows, store);
        while (FASTIO(store) != '\n') FASTEX(columns, store);
        PRINTF("%hhi %hhi %hhi\n", omino, rows, columns);
        
        REPEAT(i, omino/2+1) PRINTF("%hhi %hhi %hhi %hhi %hhi\n", i+1, omino-i, rows, columns, ((rows >= i+1 && columns >= omino-i) || (rows >= omino-i && columns >= i+1))), answer &= ((rows >= i+1 && columns >= omino-i) || (rows >= omino-i && columns >= i+1));
        answer &= (((rows*columns) % omino) == 0);
        printf("Case #%hhi: %s\n", l+1, answer ? "GABRIEL" : "RICHARD");
    }
    
    exit(0);
}