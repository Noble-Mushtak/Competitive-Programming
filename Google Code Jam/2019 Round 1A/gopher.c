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

typedef long long num_gophers;
typedef long long num_blades;
typedef long long num_queries;
typedef long long test_cases;

enum { NUM_GUESSES=6 };
num_blades guesses[NUM_GUESSES] = {7, 9, 10, 11, 13, 17}, guessesMultiplied[NUM_GUESSES] = {7, 63, 630, 6930, 90090, 1531530}, changed[10];
num_gophers answer;

num_blades calcModuloInverse(num_blades dividend, num_blades MOD) {
    num_blades lastRemainder = dividend, lastInverse = 1, remainder = MOD, inverse = 0, quotient, temp;
    while (remainder) {
        quotient = lastRemainder/remainder;
        temp = remainder, remainder = lastRemainder % remainder, lastRemainder = temp;
        temp = inverse, inverse = lastInverse-quotient*inverse, lastInverse = temp;
    }
    if (lastInverse < 0) lastInverse += MOD;
    return lastInverse;
}

int main() {
    test_cases numTestCases, a, b, l;
    num_queries i;
    num_blades j, k;
    num_gophers multiplier;
    scanf("%lli %lli %lli", &numTestCases, &a, &b);

    REPEAT(l, numTestCases) {
        REPEAT(i, NUM_GUESSES) {
            REPEAT(j, 18) printf("%lli%c", guesses[i], (j+1 == 18) ? '\n' : ' ');
            changed[i] = 0;
            REPEAT(j, 18) {
                scanf("%lli", &k);
                if (k == -1) exit(0);
                changed[i] += k, changed[i] %= guesses[i];
            }
            if (i == 0) answer = changed[i];
            else {
                /*                
                a = x+yc
                a = w+vd
                0= (x-w)+yc+vd
                w-x = yc+vd
                c^(-1)(w-x) = y+ud
                */
                multiplier = calcModuloInverse(guesses[i], guessesMultiplied[i-1])*(answer-changed[i]);
                multiplier %= guessesMultiplied[i-1];
                if (multiplier < 0) multiplier += guessesMultiplied[i-1];
                answer = changed[i]+multiplier*guesses[i];
            }
            PRINTF("%lli\n", answer);
        }
        printf("%lli\n", answer);
        scanf("%lli", &k);
        if (k == -1) exit(0);
    }
    
    exit(0);
}