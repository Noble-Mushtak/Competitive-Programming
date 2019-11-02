#include <stdio.h>
#include <stdlib.h>
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

typedef byte cell;
typedef short num_cells;
typedef short num_people;
typedef byte test_cases;

cell people[1000];
num_people standing = 0, answer = 0;
num_cells length, last;

int main() {
    char store;
    test_cases numTestCases, l;
    num_cells i;
    while (FASTIO(store) != '\n') FASTEX(numTestCases, store);
    
    REPEAT(l, numTestCases) {
        length = answer = standing = 0;
        while (FASTIO(store) != ' ') FASTEX(length, store);
        length++;
        REPEAT(i, length) people[i] = getchar()-'0';
        getchar(); //Newline
        
        REPEAT(i, length) {
            if (standing >= i) standing += people[i], last = i;
            else if (people[i] > 0) answer += i-standing, standing = i+people[i];
        }
        
        printf("Case #%hhi: %hi\n", l+1, answer);
    }
    
    exit(0);
}