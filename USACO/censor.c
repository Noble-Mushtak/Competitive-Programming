/*
    PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=529
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

typedef long num_chars;

FILE *in, *out;
/*String must end in '\0' for printf, so one more space is added.*/
char string[1000001], substring[1000001], answer[1000001];
num_chars length = 0, subLength = 0, answerLength = 0, backtrack[1000000] = {0, 0};

int main() {
    num_chars i, curPos = 2, curTrack = 0, stringPos;
    char store, *ptrTo;
    bool valid = false;
    
    in = fopen("censor.in", "r");
    while (FASTIO(store, in) != '\n') string[length++] = store;
    while (FASTIO(store, in) != '\n') substring[subLength++] = store;
    fclose(in);
    //printf("%i %i\n", subLength, length);
    
    while (curPos < subLength) {
        if (substring[curPos-1] == substring[curTrack]) curTrack++, backtrack[curPos] = curTrack, curPos++;
        else if (curTrack) curTrack = backtrack[curTrack];
        else backtrack[curPos] = 0, curPos++;
    }
    
    curPos = curTrack = stringPos = 0;
    while (curPos+curTrack < length) {
        while (curPos+curTrack >= answerLength) answer[answerLength++] = string[stringPos++];
        if (substring[curTrack] == answer[curPos+curTrack]) {
            if (curTrack+1 == subLength) length -= subLength, answerLength -= subLength, curPos -= (subLength > curPos ? curPos : subLength), curTrack = 0;
            else curTrack++;
        }
        else curPos += (curTrack ? curTrack-backtrack[curTrack] : 1), curTrack = backtrack[curTrack];
    }
    answer[answerLength] = '\0';
    
    out = fopen("censor.out", "w");
    fprintf(out, "%s\n", answer);
    fclose(out);
    
    exit(0);
}