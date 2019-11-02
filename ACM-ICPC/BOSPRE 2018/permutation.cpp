#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cinttypes>

#define REP(var, token) for (var = 0; var < token; var++)

typedef int64_t num_letters;
typedef int64_t letter;

std::queue<num_letters> counter1[256], counter2[256];
num_letters strLength;
char name[10000], input[10000], output[10000];

int main() {
    while (true) {
        letter c;
        REP(c, 256) std::queue<num_letters>().swap(counter1[c]), std::queue<num_letters>().swap(counter2[c]);
        
        fgets(name, 10000, stdin);
        if (feof(stdin)) break;
        fgets(input, 10000, stdin);
        fgets(output, 10000, stdin);
        strLength = strlen(input)-1;
        
        num_letters i;
        REP(i, strLength) counter1[input[i]].push(i), counter2[output[i]].push(i);
        REP(c, 256) if (counter1[c].size() != counter2[c].size()) break;
        printf(name);
        if (c != 256) puts("impossible");
        else {
            REP(i, strLength) {
                printf("%c: %" PRId64 " -> %" PRId64 "\n", input[i], i+1, counter2[input[i]].front()+1);
                counter2[input[i]].pop();
            }
        }
    }

    return 0;
}
