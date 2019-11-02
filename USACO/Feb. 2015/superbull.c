/*
    PROB: http://www.usaco.org/index.php?page=viewproblem2&cpid=531
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

typedef short num_teams;
typedef long team;
typedef team match[2];
typedef long long xor;

FILE *in, *out;
num_teams numTeams;
team teams[2000];
xor answer = 0, storage[2000][2000];
match prevResults[2000][2000], results[2000][2000];

int main() {
    team newTeam[2];
    match sortable[4000];
    num_teams i, j, k;
    char store;
    
    in = fopen("superbull.in", "r");
    while (FASTIO(store, in) != '\n') FASTEX(numTeams, store);
    REPEAT(i, numTeams) while(FASTIO(store, in) != '\n') FASTEX(teams[i], store);
    fclose(in);
    
    REPEAT(i, numTeams) REPEAT(j, i) storage[i][j] = (teams[i] ^ teams[j]);
    REPEAT(i, numTeams-1) {
        if (i) memcpy(prevResults, results, sizeof(prevResults));
        printf("%i\n", i);
        REPEAT(j, numTeams-i-1) {
            SET(sortable[0], j+i+1, j);
            REPEAT(k, i) memcpy(sortable[2*k+1], prevResults[j][k], 2*sizeof(team)), memcpy(sortable[2*k+2], prevResults[j+1][k], 2*sizeof(team));
            printf("%i %i\n", i, j);
            filter(j, i+1, sortable, 2*i+1);
        }
    }
    REPEAT(i, numTeams-1) answer += storage[results[0][i][0]][results[0][i][1]], printf("%i\n", storage[results[0][i][0]][results[0][i][1]]);
    
    out = fopen("superbull.out", "w");
    fprintf(out, "%lli\n", answer);
    fclose(out);
    
    exit(0);
}