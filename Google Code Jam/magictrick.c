/*
    https://code.google.com/codejam/contest/2974486/dashboard
*/

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
//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef byte test_cases;
typedef byte row;
typedef byte card;

row answer1, answer2;
card answer;
bool possible[17], answerFound, multFound;

int main() {
    char store;
    test_cases numTestCases = 0, l;
    row i, j;  
    card cur;
    while (FASTIO(store) != '\n') FASTEX(numTestCases, store);
    
    REPEAT(l, numTestCases) {
        memset(possible, false, sizeof(possible));
        answerFound = multFound = false;
        answer1 = answer2 = 0;
        while (FASTIO(store) != '\n') FASTEX(answer1, store);
        answer1--;
        REPEAT(i, 4) REPEAT(j, 4) {
            cur = 0;
            while(FASTIO(store) != ' ' && store != '\n') FASTEX(cur, store);
            if (i == answer1) possible[cur] = true;
        }
        while (FASTIO(store) != '\n') FASTEX(answer2, store);
        answer2--;
        REPEAT(i, 4) REPEAT(j, 4) {
            cur = 0;
            while(FASTIO(store) != ' ' && store != '\n') FASTEX(cur, store);
            if (i == answer2 && possible[cur]) {
                if (!answerFound) answer = cur, answerFound = true;
                else multFound = true;
            }
        }
        if (multFound) printf("Case #%hhi: Bad magician!\n", l+1);
        else if (!answerFound) printf("Case #%hhi: Volunteer cheated!\n", l+1);
        else printf("Case #%hhi: %hhi\n", l+1, answer);
    }
    
    exit(0);
}