#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

typedef short num_letters;
typedef long long num_ways;
num_ways pow2s[500] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648LL, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904};

FILE *in, *out;
num_letters length, coords1[10000][2], coords2[10000][2];
num_ways answer, numWays1, numWays2;
const num_ways MOD = 1000000007;
char board[500][500], ways1[10000][500], ways2[10000][500];

int main() {
    char store;
    num_letters i, j, dimenX, dimenY, change, l;
    num_ways curWay, maxWay;
    
    in = fopen("palpath.in", "r");
    while (FASTIO(store, in) != '\n') FASTEX(length, store);
    REPEAT(i, length) {
        REPEAT(j, length) board[i][j] = fgetc(in);
        fgetc(in);
    }
    fclose(in);
    
    maxWay = pow2s[length-1];
    if (!maxWay) while (true);
    REPEAT(curWay, maxWay) REPEAT(l, 2) {
        if ((l ? numWays2 : numWays1) == 10000) while (true);
        change = (l ? -1 : 1);
        dimenX = dimenY = (l ? (length-1) : 0);
        if (l) ways2[numWays2][0] = board[dimenX][dimenY];
        else ways1[numWays1][0] = board[dimenX][dimenY];
        REPEAT(i, length-1) {
            if (curWay & pow2s[i]) dimenX += change;
            else dimenY += change;
            if (l) ways2[numWays2][i+1] = board[dimenX][dimenY];
            else ways1[numWays1][i+1] = board[dimenX][dimenY];
        }
        if (l) SET(coords2[numWays2], dimenX, dimenY), numWays2++;
        else SET(coords1[numWays1], dimenX, dimenY), numWays1++;
        //printf("%s\n", (l ? ways2[numWays2-1] : ways1[numWays1-1]));
    }
    REPEAT(i, numWays1) REPEAT(j, numWays2) if (!memcmp(coords1[i], coords2[j], 2*sizeof(num_letters)) && !memcmp(ways1[i], ways2[j], length*sizeof(char))) {
        answer++;
        if (answer == MOD) answer = 0;
    }
    
    out = fopen("palpath.out", "w");
    fprintf(out, "%li\n", answer);
    fclose(out);
    
    exit(0);
}