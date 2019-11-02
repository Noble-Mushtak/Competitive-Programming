#include <stdio.h>
#include <stdlib.h>
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

typedef long num_bales;
typedef long data;

FILE *in, *out;
num_bales length, leftMin = 0;
data answer = 0, input[100000][2], *bales[100000];

int compareData(const void *ptr1, const void *ptr2) {
    data *arr1 = *(data**)ptr1, *arr2 = *(data**)ptr2;
    return (arr1[1] > arr2[1])-(arr1[1] < arr2[1]);
}

int main() {
    char store;
    num_bales i, leftEnd, rightEnd;
    
    in = fopen("trapped.in", "r");
    while (FASTIO(store, in) != '\n') FASTEX(length, store);
    REPEAT(i, length) {
        while (FASTIO(store, in) != ' ') FASTEX(input[i][0], store);
        while (FASTIO(store, in) != '\n') FASTEX(input[i][1], store);
        bales[i] = input[i];
    }
    fclose(in);
    
    qsort(bales, length, sizeof(data*), compareData);
    //REPEAT(i, length) printf("%li %li\n", bales[i][0], bales[i][1]);
    answer = bales[length-1][1]-bales[0][1];
    REPEAT(i, length-1) {
        leftEnd = i, rightEnd = i+1;
        while (leftEnd >= leftMin && rightEnd < length && (bales[leftEnd][0] < bales[rightEnd][0] ? bales[leftEnd][0] : bales[rightEnd][0]) < bales[rightEnd][1]-bales[leftEnd][1]) {
            //else if because otherwise, leftEnd may be < 0 in second loop
            if (bales[leftEnd][0] < bales[rightEnd][1]-bales[leftEnd][1]) leftEnd--;
            else if (bales[rightEnd][0] < bales[rightEnd][1]-bales[leftEnd][1]) rightEnd++;
        }
        if (leftEnd < leftMin || rightEnd == length) leftMin = i, answer -= (bales[i+1][1]-bales[i][1]);
    }
    
    out = fopen("trapped.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}