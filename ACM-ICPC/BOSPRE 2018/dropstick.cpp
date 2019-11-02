#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cinttypes>
#include <algorithm>

#define REP(var, token) for (var = 0; var < token; ++var)

typedef long double dimen;

dimen radius, length, d1, d2;
char testCase[10000];

int main() {
    while (true) {
        fgets(testCase, 10000, stdin);
        if (feof(stdin)) break;
        double rD, lD, d1D, d2D;
        sscanf(testCase, "%lf %lf %lf %lf", &rD, &lD, &d1D, &d2D);
        radius = rD, length = lD, d1 = d1D, d2 = d2D;

        bool answer= false;
        if (d1 < radius) answer = true;
        if (d2 < radius) answer = true;
        else {
            dimen d2X = (length*length-d1*d1-d2*d2)/(2*d1);
            dimen d2Y = std::sqrt(d2*d2-d2X*d2X);
            dimen slopeDenom = d2X+d1;
            if (slopeDenom > 1e-6) {
                dimen m = d2Y/(d2X+d1);
                // 0=m * (x+d1) - y
                // minimize x^2+y^2
                // (2x, 2y) = lambda (m, -1)
                // -> x=-y * m
                // 0=m(d1-my)-y=md1-(1+m^2)y
                // -> y=md1/(1+m^2)
                dimen y = m*d1/(1+m*m);
                dimen x = -m*y;
                if ((((x > -d1-1e-6) && (x < d2X+1e-6)) || ((x > d2X-1e-6) && (x < -d1+1e-6))) && ((y > -1e-6) && (y < d2Y+1e-6))) {
                    answer = (x*x+y*y) < radius*radius;
                }
            }
        }
        printf("%.3lf %.3lf %.3lf %.3lf %s\n", rD, lD, d1D, d2D, answer ? "TOUCH" : "NO-TOUCH");
    }
    
    return 0;
}
