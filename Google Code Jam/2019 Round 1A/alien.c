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

typedef long long test_cases;
typedef long long num_chars;
typedef long long num_words;
typedef char *string;
typedef struct {
    string suffix;
    num_words index;
} suffix_info;

num_words numWords, numSuffixes, suffixLocations[1010][100], answer;
num_chars wordLengths[1010];
char words[1010][100];
string wordsSorted[1010];
suffix_info suffixes[51000];
bool takenAway[1010], suffixMarked[51000];

int compareStringLengths(const void *ptr1, const void *ptr2) {
    string *str1 = (string*)ptr1, *str2 = (string*)ptr2;
    return strlen(*str2)-strlen(*str1);
}

int compareSuffixes(const void *ptr1, const void *ptr2) {
    suffix_info *str1 = (suffix_info*)ptr1, *str2 = (suffix_info*)ptr2;
    if (strlen(str1->suffix) != strlen(str2->suffix)) return strlen(str2->suffix)-strlen(str1->suffix);
    return strcmp(str1->suffix, str2->suffix);
}

int main() {
    num_words i, k, m;
    num_chars j;
    test_cases l, numTestCases;
    scanf("%lli", &numTestCases);
    
    REPEAT(l, numTestCases) {
        answer = 0;
        scanf("%lli", &numWords);
        REPEAT(i, numWords) {
            scanf("%s", words[i]);
            wordsSorted[i] = words[i];
            takenAway[i] = false;
        }
        qsort(wordsSorted, numWords, sizeof(string), compareStringLengths);
        
        numSuffixes = 0;
        REPEAT(i, numWords) {
            wordLengths[i] = strlen(wordsSorted[i]);
            REPEAT(j, wordLengths[i]) {
                suffixes[numSuffixes].suffix = wordsSorted[i]+j;
                suffixes[numSuffixes].index = i;
                suffixMarked[numSuffixes] = false;
                numSuffixes++;
            }
        }
        qsort(suffixes, numSuffixes, sizeof(suffix_info), compareSuffixes);
        
        REPEAT(i, numSuffixes) suffixLocations[suffixes[i].index][strlen(suffixes[i].suffix)] = i;
        /* REPEAT(i, numSuffixes) printf("%s\n", suffixes[i].suffix);
        puts("");
        REPEAT(i, numWords) REPEAT(j, wordLengths[i]) printf("%s\n", suffixes[suffixLocations[i][j+1]].suffix); // */
        
        REPEAT(i, numSuffixes-1) {
            if (!suffixMarked[i] && !takenAway[suffixes[i].index]) {
                for (m = 1; (i+m < numSuffixes) && (strcmp(suffixes[i].suffix, suffixes[i+m].suffix) == 0); m++) if (!takenAway[suffixes[i+m].index]) {
                    takenAway[suffixes[i].index] = true;
                    takenAway[suffixes[i+m].index] = true;
                    while ((i+m < numSuffixes) && (strcmp(suffixes[i].suffix, suffixes[i+m].suffix) == 0)) suffixMarked[i+m] = true, m++;
                    answer += 2;
                    break;
                }
            }
        }
        printf("Case #%lli: %lli\n", l+1, answer);
    }
    
    exit(0);
}