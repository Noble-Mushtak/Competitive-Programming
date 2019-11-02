#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
static inline long long min(long long length1, long long length2) { return (length1 < length2) ? length1 : length2; }
static inline long long max(long long length1, long long length2) { return (length1 > length2) ? length1 : length2; }

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 1
#endif

typedef long num;
typedef long num_nums;
typedef long test_cases;

const char *correct = "CORRECT", *wrongAnswer = "WRONG_ANSWER", *tooBig = "TOO_BIG", *tooSmall = "TOO_SMALL";
char feedback[100];
num beg, end;
num_nums numGuesses;

int main() {
    test_cases numTestCases;
    num guess;
    
    scanf("%li", &numTestCases);
    while (numTestCases--) {
        scanf("%li %li %li", &beg, &end, &numGuesses);
        beg += 1;
        while (beg <= end) {
            guess = (beg+end)/2;
            printf("%li\n", guess);
            fflush(stdout);
            scanf("%s", feedback);
            if (strcmp(feedback, correct) == 0) break;
            else if (strcmp(feedback, tooBig) == 0) end = guess-1;
            else if (strcmp(feedback, tooSmall) == 0) beg = guess+1;
            else if (strcmp(feedback, wrongAnswer) == 0) exit(0);
            else exit(1);
        }
    }

    exit(0);
}