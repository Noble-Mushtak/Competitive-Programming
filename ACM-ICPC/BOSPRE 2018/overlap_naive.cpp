#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <limits>
#include <array>
#include <vector>

#define REPEAT(token, num) for (token = 0; token < num; token++)

//#define DEBUG
#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t dimen;
struct rect {
    dimen minX, maxX, minY, maxY;
};
typedef int64_t num_rects;

char token[100];
num_rects numRects = 0, answer = 0;
rect rectangles[1000010];

int main() {
    while (true) {
        scanf("%s", token);
        if (token[0] == '*') break;
        sscanf(token, "%" PRId64, &(rectangles[numRects].minX));
        scanf("%" PRId64 " %" PRId64 " %" PRId64, &(rectangles[numRects].maxX), &(rectangles[numRects].minY), &(rectangles[numRects].maxY));
        numRects++;
    }
    
    num_rects i, j;
    REPEAT(i, numRects) {
        num_rects tempAnswer = i;
        REPEAT(j, i) {
            if ((rectangles[j].maxX <= rectangles[i].minX) ||
                (rectangles[j].minX >= rectangles[i].maxX) ||
                (rectangles[j].maxY <= rectangles[i].minY) ||
                (rectangles[j].minY >= rectangles[i].maxY)) tempAnswer--;
        }
        answer += tempAnswer;
    }
    printf("%" PRId64 "\n", answer);
    
    exit(0);
}