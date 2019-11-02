#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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

typedef double angle;
typedef double area;
typedef double dimen;
typedef struct {
    dimen x, y, z;
} point;
typedef long test_cases;

area target;
angle rotation1, rotation2;
point corner1, corner2, corner3;

int main() {
    test_cases numTestCases, z;
    point storePoint;
    scanf("%li", &numTestCases);
    
    REPEAT(z, numTestCases) {
        scanf("%lf", &target);
        printf("Case #%li:\n", z+1);
        if (target < sqrt(2)) {
            rotation1 = asin(pow(target, 2)-1)/2;
            printf("0.5 0 0\n0 %0.16lf %0.16lf\n0 %0.16lf %0.16lf\n", 0.5*cos(rotation1), 0.5*sin(rotation1), -0.5*sin(rotation1), 0.5*cos(rotation1));
        } else {
            corner1.x = 0.5, corner1.y = 0, corner2.z = 0;
            corner2.x = 0, corner2.y = sqrt(2)/4, corner2.z = sqrt(2)/4;
            corner3.x = 0, corner3.y = -sqrt(2)/4, corner3.z = sqrt(2)/4;
            
            //sqrt(2)*cos(x)+sin(x)=A
            //sin(x)=A-sqrt(2)cos(x)
            //1-cos^2(x)=A^2+2cos^2(x)-2sqrt(2)Acos(x)
            //0=3cos^2(x)-2sqrt(2)Acos(x)+A^2-1
            //cos(x)=(sqrt(2)A+/-sqrt(3-A^2))/3
            rotation2 = acos((sqrt(2)*target-sqrt(3-pow(target, 2)))/3);
            
            inline point rotatePoint(point original) {
                point newPoint;
                newPoint.x = original.x*cos(rotation2)-original.y*sin(rotation2);
                newPoint.y = original.x*sin(rotation2)+original.y*cos(rotation2);
                newPoint.z = original.z;
                return newPoint;
            }
            storePoint = rotatePoint(corner1);
            corner1.x = storePoint.x, corner1.y = storePoint.y;
            storePoint = rotatePoint(corner2);
            corner2.x = storePoint.x, corner2.y = storePoint.y;
            storePoint = rotatePoint(corner3);
            corner3.x = storePoint.x, corner3.y = storePoint.y;
            printf("%0.16lf %0.16lf %0.16lf\n%0.16lf %0.16lf %0.16lf\n%0.16lf %0.16lf %0.16lf\n", corner1.x, corner1.y, corner1.z, corner2.x, corner2.y, corner2.z, corner3.x, corner3.y, corner3.z);
        }
    }
    
    exit(0);
}