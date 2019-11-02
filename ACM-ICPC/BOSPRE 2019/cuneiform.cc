#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked

typedef int64_t num;
char testCase[10000], output[10000];

int main() {
    while (true) {
        fgets(testCase, 10000, stdin);
        if (feof(stdin)) break;
        strcpy(output, testCase);
        char *curPtr = strtok(testCase, " ");
        num answer = 0;
        while (curPtr != nullptr) {
            answer *= 60;
            while (*curPtr == '<') answer += 10, curPtr++;
            while (*curPtr == 'v') answer += 1, curPtr++;
            curPtr = strtok(nullptr, " ");
        }
        num size = strlen(output);
        output[size-1] = '\0';
        printf("%s %" PRId64 "\n", output, answer);
    }

    exit(0);
}