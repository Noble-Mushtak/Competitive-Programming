#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

typedef long long num;

FILE *in, *out;
num numChars, intervalLength, curIntervalLength, answer;
char string[300010];

int main() {
    num i;
    
    in = fopen("redistricting.in", "r");
    fscanf(in, "%lli %lli", &numChars, &intervalLength);
    fscanf(in, "%s", string);
    fclose(in);

    REPEAT(i, numChars+1) {
        if ((i == numChars) || (string[i] == 'H')) {
           answer += (curIntervalLength+intervalLength-1)/intervalLength;
           curIntervalLength = 0;
        } else curIntervalLength++;
    }
    
    out = fopen("redistricting.out", "w");
    fprintf(out, "%lli\n", answer);
    fclose(out);
    
    exit(0);
}