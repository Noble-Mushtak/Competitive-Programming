#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>

#define REPEAT(token, num) for (token = 0; token < num; token++)
#define fgetc fgetc_unlocked
#define fputc fputc_unlocked

/*
a_1=max(f(1), 1/2*a_2)
a_2=max(f(2), 1/2*a_1+1/2*a_3)
a_3=max(f(3), 1/2*a_2)
->
a_1=f(1)
a_2=max(f(2), 1/2*f(1)+1/2*a_3)
a_3=max(f(3), 1/2*a_2)

_ _ | | _

p2=1/2*p3
p3=1/2+1/2*p2
p2=1/3, p3=2/3
*/

typedef long long value;
typedef long long position;

std::set<position> noFlips;
position boardLength, allPositions[100010];
value board[100010], expectedValueTimes100000[100010];
FILE *in, *out;

int comparePositions(const void *ptr1, const void *ptr2) {
    position position1 = *(position*)ptr1, position2 = *(position*)ptr2;
    return board[position1]-board[position2];
}

value valueOfPos(position pos) {
    if (pos == -1) return 0;
    if (pos == boardLength) return 0;
    return board[pos];
}

int main() {
    position i, j, k;
    std::set<position>::iterator lowerBound, upperBound;
    double calcValue;
    
    in = fopen("balance.in", "r");
    fscanf(in, "%lli", &boardLength);
    REPEAT(i, boardLength) fscanf(in, "%lli", board+i);
    fclose(in);
    noFlips.insert(-1);
    noFlips.insert(boardLength);

    REPEAT(i, boardLength) {
        upperBound = noFlips.upper_bound(i);
        lowerBound = --upperBound;
        j = *lowerBound;
        //printf("%li\n", j);
        for (k = i+1; k <= boardLength; k++) {
            calcValue = k-j;
            calcValue = 1/calcValue;
            calcValue = calcValue*(k-i)*valueOfPos(j)+calcValue*(i-j)*valueOfPos(k);
            if (calcValue > board[i]) break;
        }
        if (k == boardLength+1) noFlips.insert(i);
    }
    REPEAT(i, boardLength) {
        upperBound = noFlips.upper_bound(i);
        k = *upperBound;
        lowerBound = --upperBound;
        j = *lowerBound;
        if (j == i) expectedValueTimes100000[i] = board[i]*100000;
        else {
            expectedValueTimes100000[i] = (k-i)*valueOfPos(j)+(i-j)*valueOfPos(k);
            expectedValueTimes100000[i] *= 100000;
            expectedValueTimes100000[i] /= k-j;
        }
        if (expectedValueTimes100000[i] < board[i]*100000) exit(1);
        //if (i == boardLength-1) printf("%lf %li | %li %li | %li %li\n", expectedValue[i], board[i], j, valueOfPos(j), k, valueOfPos(k));
    }
    
    out = fopen("balance.out", "w");
    REPEAT(i, boardLength) fprintf(out, "%lli\n", expectedValueTimes100000[i]);
    fclose(out);
    
    exit(0);
}