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

typedef short num_teams;
typedef long team;
typedef long long xor;

FILE *in, *out;
num_teams numTeams;
team teams[2000];
xor answer, distance[2000];
bool used[2000];

int main() {
    num_teams i, max, j;
    char store;
    
    in = fopen("superbull.in", "r");
    while (FASTIO(store, in) != '\n') FASTEX(numTeams, store);
    REPEAT(i, numTeams) while(FASTIO(store, in) != '\n') FASTEX(teams[i], store);
    fclose(in);
    
    REPEAT(i, numTeams) {
        max = -1;
        REPEAT(j, numTeams) if (!used[j] && (max == -1 || distance[j] > distance[max])) max = j;
        answer += distance[max];
        used[max] = true;
        REPEAT(j, numTeams) if (!used[j] && (teams[j]^teams[max]) > distance[j]) distance[j] = teams[j]^teams[max];
    }
    
    out = fopen("superbull.out", "w");
    fprintf(out, "%lli\n", answer);
    fclose(out);
    
    exit(0);
}