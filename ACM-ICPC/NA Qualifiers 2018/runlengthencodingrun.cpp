#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>

#define REPEAT(token, num) for (token = 0; token < num; token++)

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t num_letters;

char command[200], string[200], answer[10000];
num_letters stringLength, answerLength;

int main() {
    scanf("%s %s", command, string);
    stringLength = strlen(string);
    if (command[0] == 'E') {
        num_letters i, counter = 0;
        REPEAT(i, stringLength) {
            if ((i == 0) || (string[i] == string[i-1])) counter++;
            else {
                answer[answerLength++] = string[i-1];
                answer[answerLength++] = counter+'0';
                counter = 1;
            }
        }
        answer[answerLength++] = string[stringLength-1];
        answer[answerLength++] = counter+'0';
        answer[answerLength] = '\0';
        puts(answer);
    } else {
       num_letters i, j;
       REPEAT(i, stringLength) {
           REPEAT(j, string[i+1]-'0') answer[answerLength++] = string[i];
           i++;
       }
       answer[answerLength] = '\0';
       puts(answer);
    }
    
    exit(0);
}