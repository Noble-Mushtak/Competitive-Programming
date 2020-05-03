#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_chars;
typedef int64_t test_cases;

num_chars inputLength, answerLength;
char input[500], answer[10000];
test_cases numTestCases;

int main() {
    test_cases l;
    scanf(INT64, &numTestCases);
    REP(l, numTestCases) {
        scanf("%s", input);
        inputLength = strlen(input);
        input[inputLength] = '0';
        
        num_chars i, j;
        num_chars curDepth = 0;
        answerLength = 0;
        REP(i, inputLength+1) {
            num_chars nextDepth = input[i]-'0';
            if (curDepth < nextDepth) {
                REP(j, nextDepth-curDepth) answer[answerLength++] = '(';
            }
            if (curDepth > nextDepth) {
                REP(j, curDepth-nextDepth) answer[answerLength++] = ')';
            }
            curDepth = nextDepth;
            if (i < inputLength) answer[answerLength++] = input[i];
        }
        answer[answerLength] = '\0';
        printf("Case #" INT64 ": %s\n", l+1, answer);
    }
    
    return 0;
}