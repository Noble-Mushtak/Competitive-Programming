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

typedef long num_chars;

FILE *in, *out;
/*String must end in '\0' for printf, so one more space is added.*/
char string[1000001], substring[1000001];
num_chars length = 0, subLength = 0, indexOf, offset = 0;

int main() {
    num_chars i;
    char store, *ptrTo;
    bool valid = false;
    
    in = fopen("censor.in", "r");
    while (FASTIO(store, in) != '\n') string[length++] = store;
    while (FASTIO(store, in) != '\n') substring[subLength++] = store;
    fclose(in);
    
    while (!valid) {
        ptrTo = strstr(string+offset, substring), valid = (ptrTo == NULL);
        if (!valid) {
            indexOf = (num_chars)(ptrTo-string);
            offset = indexOf < subLength ? 0 : indexOf-subLength+1;
            length -= subLength;
            REMOVEELEMS(string, indexOf, length, subLength);
            string[length] = '\0';
        }
    }
    
    out = fopen("censor.out", "w");
    fprintf(out, "%s\n", string);
    fclose(out);
    
    exit(0);
}