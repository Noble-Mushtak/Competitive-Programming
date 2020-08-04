/*
    https://codingcompetitions.withgoogle.com/codejam/round/0000000000051679/0000000000146184
*/

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>

#define REP(token, num) for (token = 0; token < num; token++)
#define fgets fgets_unlocked
#define INT64 "%" PRId64
#define DOUBLE "%lf"

#ifdef DEBUG
#define PRINTF printf
#else
#define PRINTF(...)
#endif

typedef int64_t test_cases;
typedef int64_t num_pairs;
typedef __int128 num;

num gcd(num num1, num num2) {
    num remainder = num1, lastRemainder = num2, lastLastRemainder;
    while (remainder) {
        lastLastRemainder = lastRemainder, lastRemainder = remainder;
        remainder = lastLastRemainder % lastRemainder;
    }
    return lastRemainder;
}

struct ratio {
    num numer, denom;
    ratio() {}
    ratio(num n, num d) {
        if (d < 0) n *= -1, d *= -1;
        num commonFactor = gcd(n, d);
        numer = n/commonFactor;
        denom = d/commonFactor;
    }
};

typedef std::vector<num> continued_frac;

test_cases numTestCases;
num_pairs numPairs;
num pairs[500][2];
const num MAX_QUANT = 1000000001;
ratio minRatio, maxRatio;

const num EIGHTEEN_ZEROS = 1000000000000000000;
void printNum(num num) {
    if (num == 0) {
        putchar('0');
        return;
    }
    if (num < 0) {
        putchar('-');
        num *= -1;
    }

    if (num > EIGHTEEN_ZEROS) {
        printNum(num/EIGHTEEN_ZEROS);
        uint64_t trailingDigs = num % EIGHTEEN_ZEROS;
        printf("%.18" PRIu64, trailingDigs);
    } else {
        printf("%" PRIu64, static_cast<uint64_t>(num));
    }
}

void printRatio(ratio rat) {
    printNum(rat.numer);
    putchar(' ');
    printNum(rat.denom);
    putchar('\n');
}

void printCf(continued_frac cf) {
    for (auto it = cf.begin(); it != cf.end(); ++it) {
        printNum(*it);
        putchar('\n');
    }
}

bool operator<(ratio rat1, ratio rat2) {
    return rat1.numer*rat2.denom < rat2.numer*rat1.denom;
}

bool operator==(ratio rat1, ratio rat2) {
    return rat1.numer*rat2.denom == rat2.numer*rat1.denom;
}

bool operator>(ratio rat1, ratio rat2) {
    return rat2 < rat1;
}

bool operator<=(ratio rat1, ratio rat2) {
    return (rat1 == rat2) || (rat1 < rat2);
}

bool operator>=(ratio rat1, ratio rat2) {
    return (rat1 == rat2) || (rat1 > rat2);
}

bool between(ratio test, ratio min, ratio max) {
    return (min < test) && (test < max);
}

continued_frac calcContinuedFrac(ratio rat) {
    continued_frac answer;
    num temp;
    while (rat.denom > 0) {
        answer.push_back(rat.numer/rat.denom);
        rat.numer %= rat.denom;
        temp = rat.numer, rat.numer = rat.denom, rat.denom = temp;
    }
    return answer;
}

continued_frac modifyContinuedFrac(continued_frac orig) {
    continued_frac answer = orig;
    num lastElem = answer.back();
    answer.pop_back();
    answer.push_back(lastElem-1);
    answer.push_back(1);
    return answer;
}

ratio calcRatio(continued_frac cf) {
    ratio answer(1, 0);
    num temp;
    for (auto it = cf.rbegin(); it != cf.rend(); ++it) {
        temp = answer.numer, answer.numer = answer.denom, answer.denom = temp;
        answer.numer += (*it)*answer.denom;
    }
    return answer;
}

ratio calcBestRationalCf(continued_frac cf1, continued_frac cf2) {
    continued_frac cfAnswer;
    auto it1 = cf1.begin();
    auto it2 = cf2.begin();
    while ((it1 != cf1.end()) && (it2 != cf2.end()) && (*it1 == *it2)) {
        cfAnswer.push_back(*it1);
        ++it1, ++it2;
    }
    if (it1 == cf1.end()) cfAnswer.push_back(1+*it2);
    else if (it2 == cf2.end()) cfAnswer.push_back(1+*it1);
    else cfAnswer.push_back(1+std::min(*it1, *it2));
    return calcRatio(cfAnswer);
}

ratio calcBestRational(ratio minR, ratio maxR) {
    continued_frac min1 = calcContinuedFrac(minR);
    continued_frac min2 = modifyContinuedFrac(min1);
    continued_frac max1 = calcContinuedFrac(maxR);
    continued_frac max2 = modifyContinuedFrac(max1);

    ratio bestRatio = calcBestRationalCf(min1, max1);
    ratio otherRatios[3];
    otherRatios[0] = calcBestRationalCf(min1, max2);
    otherRatios[1] = calcBestRationalCf(min2, max1);
    otherRatios[2] = calcBestRationalCf(min2, max2);

    num i;
    REP(i, 3) {
        if (between(otherRatios[i], minRatio, maxRatio) && (!between(bestRatio, minRatio, maxRatio) || (otherRatios[i].denom < bestRatio.denom) || ((otherRatios[i].denom == bestRatio.denom) && (otherRatios[i].numer < bestRatio.numer)))) bestRatio = otherRatios[i];
    }
    return bestRatio;
}

int main() {
    test_cases l;
    scanf(INT64, &numTestCases);
    REP(l, numTestCases) {
        scanf(INT64, &numPairs);
        num_pairs i, j;
        REP(i, numPairs) {
            int64_t store0, store1;
            scanf(INT64 " " INT64, &store0, &store1);
            pairs[i][0] = store0, pairs[i][1] = store1;
        }

        minRatio = ratio(1, MAX_QUANT);
        maxRatio = ratio(MAX_QUANT, 1);
        bool flag = false;
        REP(i, numPairs) {
            REP(j, i) {
                num codiDiff = pairs[i][0]-pairs[j][0];
                num jamarDiff = pairs[i][1]-pairs[j][1];
                // codiDiff * C + jamarDiff * J > 0
                // jamarDiff * J > -codiDiff * C
                // J/C > -codiDiff/jamarDiff
                
                if (codiDiff == 0) {
                    flag |= (pairs[i][1] <= pairs[j][1]);
                    continue;
                }
                if (jamarDiff == 0) {
                    flag |= (pairs[i][0] <= pairs[j][0]);
                    continue;
                }
                bool lessThanRatio = (jamarDiff < 0);
                if (lessThanRatio) jamarDiff *= -1, codiDiff *= -1;
                if (codiDiff > 0) {
                    flag |= lessThanRatio;
                    continue;
                }
                
                ratio newRatio(-codiDiff, jamarDiff);
                /* putchar(lessThanRatio ? 'L' : 'G');
                putchar(':');
                putchar(' ');
                printNum(newRatio.numer);
                putchar(' ');
                printNum(newRatio.denom);
                putchar('\n'); // */
                if (lessThanRatio) {
                    if (maxRatio > newRatio) maxRatio = newRatio;
                } else {
                    if (minRatio < newRatio) minRatio = newRatio;
                }
            }
        }
        //minRatio >= maxRatio
        if (flag || (minRatio >= maxRatio)) {
            printf("Case #" INT64 ": IMPOSSIBLE\n", l+1);
            continue;
        }
        /* printNum(minRatio.numer);
        putchar(' ');
        printNum(minRatio.denom);
        putchar('\n');
        printNum(maxRatio.numer);
        putchar(' ');
        printNum(maxRatio.denom);
        putchar('\n'); // */

        ratio answer = calcBestRational(minRatio, maxRatio);
        printf("Case #" INT64 ": ", l+1);
        printNum(answer.denom);
        putchar(' ');
        printNum(answer.numer);
        putchar('\n');
    }
    
    return 0;
}