#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <algorithm>
#include <limits>
#include <array>
#include <vector>
#include <iostream>
#include <sstream>

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

char curLine[1000], name[100];
num_rects numRects = 0, answer = 0;
rect rectangles[1000010];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (true) {
        std::cin.getline(name, 100);
        if (std::cin.eof()) break;
        
        while (true) {
            std::cin.getline(curLine, 1000);
            if (curLine[0] == '*') break;
            
            std::stringstream curLineStream(curLine);
            curLineStream >> rectangles[numRects].minX >> rectangles[numRects].maxX >> rectangles[numRects].minY >> rectangles[numRects].maxY;
            numRects++;
        }

        num_rects i, j;
        REPEAT(i, numRects) {
            num_rects tempAnswer = i;
            REPEAT(j, i) {
                if ((rectangles[j].maxX <= rectangles[i].minX) ||
                    (rectangles[j].minX >= rectangles[i].maxX) ||
                    (rectangles[j].maxY <= rectangles[i].minY) ||
                    (rectangles[j].minY >= rectangles[i].maxY)) --tempAnswer;
            }
            answer += tempAnswer;
        }
        std::cout << name << "\n" << answer << "\n";
    }
    
    exit(0);
}