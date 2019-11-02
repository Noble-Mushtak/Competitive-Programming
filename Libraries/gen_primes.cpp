#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

/**
 * Prime Generator
 * Can generate all primes under 2^30 in about two seconds (assuming there is no -g debugging flag turned on)
 * 
 * num_nums primes::MAX_NUM_PRIMES
 * * This number controls the number of primes computed by genPrimes().
 * 
 * num primes::primes[]
 * * This array holds all of the primes computed by genPrimes().
 * * More specifically, primes[i] is the (i+1)th least prime.
 * * 
 * * Make sure the space in this array is at least MAX_NUM_PRIMES+1000000
 * * in order to avoid an index-out-of-bounds error.
 * 
 * void primes::genPrimes()
 * * This function generates the primes and stores them in the primes[] array.
 * * Call this function at the beginning of your program.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>

typedef int32_t num;
typedef int32_t num_nums;

namespace primes {
    num primes[56000000];
    const num_nums MAX_NUM_PRIMES = 54400028;

    uint64_t mask[64] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648LL, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808ULL};
    void setBit(uint64_t *boolArr, num num1) { boolArr[num1 >> 6] |= mask[num1 & 63]; }
    bool getBit(uint64_t *boolArr, num num1) { return (boolArr[num1 >> 6] & mask[num1 & 63]) == 0; }

    const num SIEVE_SIZE = 1 << 20;
    const num SQRT_MAX = 1 << 15;
    const num SQRT_SQRT_MAX = 182;
    const num_nums PATTERN_SIZE = 960960;
    num_nums PRIMES_UNDER_SQRT_MAX;
    num_nums PRIMES_UNDER_SQRT_SQRT_MAX;
    num_nums numPrimes = 0;
    //Note: 8192 is SIEVE_SIZE/128
    //Note: Wheel size is 3*5*7*11*13, or PATTERN_SIZE/64. Size of wheelPattern array is twice the wheel size, so the pattern is repreated twice.
    uint64_t isPrime[8192], wheelPattern[30030];

    void genPrimes() {
        //For some reason, adding the primes one by one avoids any errors on CodeChef
        //while putting all of the primes in an initializer list causes a "file limit size exceeded" error.
        primes[numPrimes++] = 2;
        primes[numPrimes++] = 3;
        primes[numPrimes++] = 5;
        primes[numPrimes++] = 7;
        primes[numPrimes++] = 11;
        primes[numPrimes++] = 13;
        primes[numPrimes++] = 17;
        primes[numPrimes++] = 19;
        primes[numPrimes++] = 23;
        primes[numPrimes++] = 29;
        primes[numPrimes++] = 31;
        primes[numPrimes++] = 37;
        primes[numPrimes++] = 41;
        primes[numPrimes++] = 43;
        primes[numPrimes++] = 47;
        primes[numPrimes++] = 53;
        primes[numPrimes++] = 59;
        primes[numPrimes++] = 61;
        primes[numPrimes++] = 67;
        primes[numPrimes++] = 71;
        primes[numPrimes++] = 73;
        primes[numPrimes++] = 79;
        primes[numPrimes++] = 83;
        primes[numPrimes++] = 89;
        primes[numPrimes++] = 97;
        primes[numPrimes++] = 101;
        primes[numPrimes++] = 103;
        primes[numPrimes++] = 107;
        primes[numPrimes++] = 109;
        primes[numPrimes++] = 113;
        primes[numPrimes++] = 127;
        primes[numPrimes++] = 131;
        primes[numPrimes++] = 137;
        primes[numPrimes++] = 139;
        primes[numPrimes++] = 149;
        primes[numPrimes++] = 151;
        primes[numPrimes++] = 157;
        primes[numPrimes++] = 163;
        primes[numPrimes++] = 167;
        primes[numPrimes++] = 173;
        primes[numPrimes++] = 179;
        primes[numPrimes++] = 181;
        PRIMES_UNDER_SQRT_SQRT_MAX = numPrimes;

        num i;
        num_nums j;
        //getBit(isPrime, i) is 0 if and only if 2*i+1 is prime
        //Do simple sieve to generate all primes under SQRT_MAX
        for (j = 1; j < PRIMES_UNDER_SQRT_SQRT_MAX; j++) {
            for (i = (primes[j]*primes[j]) >> 1; i < SQRT_MAX >> 1; i += primes[j]) setBit(isPrime, i);
        }
        //Add the primes under SQRT_MAX to primes array
        for (i = SQRT_SQRT_MAX >> 1; i < SQRT_MAX >> 1; i++) if (getBit(isPrime, i)) primes[numPrimes++] = 2*i+1;
        PRIMES_UNDER_SQRT_MAX = numPrimes;

        //getBit(wheelPattern, i) is 0 if and only if 2*i+1 is not divisible by 3, 5, 7, 11, 13
        for (i = 1; i < PATTERN_SIZE; i += 3) setBit(wheelPattern, i);
        for (i = 2; i < PATTERN_SIZE; i += 5) setBit(wheelPattern, i);
        for (i = 3; i < PATTERN_SIZE; i += 7) setBit(wheelPattern, i);
        for (i = 5; i < PATTERN_SIZE; i += 11) setBit(wheelPattern, i);
        for (i = 6; i < PATTERN_SIZE; i += 13) setBit(wheelPattern, i);

        /*for (i = 0; i < 15015; i++) if (getBit(wheelPattern, i)) printf("%i\n", 2*i+1);
        exit(0); // */

        //Copy the pattern so that it appears twice in the array.
        //This makes copying the pattern from the middle easier.
        memcpy(wheelPattern+15015, wheelPattern, 15015*sizeof(uint64_t));

        //Each segment is SIEVE_SIZE numbers long; keep looping until we have at least MAX_NUM_PRIMES
        for (num begInterval = SQRT_MAX; numPrimes < MAX_NUM_PRIMES; begInterval += SIEVE_SIZE) {
            //printf("%i %i\n", begInterval, numPrimes);
            /*
            So far, we've gone through begInterval numbers, meaning we've gone through begInterval/2 odd numbers.
            Thus, we should start the pattern from getBit(wheelPattern, begInterval/2 % 960960) since the pattern repeats every 960960 odd numbers.
            Since each uint64_t represents 64 odd numbers,
            this really means we should start the pattern from wheelPattern[(begInterval/128) % 15015]
            */
            memcpy(isPrime, wheelPattern+((begInterval >> 7) % 15015), 8192*sizeof(uint64_t));

            //By inspecting only odd numbers and using the wheel pattern, we've taken care of the first 6 primes, so go from there up until the greatest prime under SQRT_MAX:
            for (j = 6; j < PRIMES_UNDER_SQRT_MAX; j++) {
                //Find smallest integer for which primes[j] is smallest prime:
                num multiple = primes[j]*primes[j];
                //If it's too big, then we don't need to check through any more rpimes:
                if (multiple > begInterval+SIEVE_SIZE-1) break;

                //If multiple is greater than begInterval, then start from multiple.
                //getBit(isPrime, multipleIndex) should be 0 if and only if begInterval+2*multipleIndex+1 is prime
                //Thus, we set multipleIndex so that begInterval+2*multipleInde+1 == multiple
                num_nums multipleIndex = (multiple-begInterval) >> 1;

                //If multiple is less than begInterval, find the least odd multiple of primes[j] greater than begInterval:
                //(Note that it is not "greater than or equal to" begInterval because, even if begInterval is a multiple of primes[j], begInterval is even and we want an odd multiple.)
                if (multiple < begInterval) {
                    //This is how much we need to add to begInterval to get a multiple of primes[j];
                    num_nums remainderToAdd = primes[j]-(begInterval % primes[j]);
                    //If this multiple is even, make it odd:
                    if ((remainderToAdd & 1) == 0) remainderToAdd += primes[j];
                    //multiple = begInterval+remainderToAdd
                    //Therefore, multipleIndex = (multiple-begInterval) >> 1 = remainderToAdd >> 1
                    multipleIndex = remainderToAdd >> 1;
                }

                //We are currently inspecting a set of SIEVE_SIZE/2 odd numbers.
                //Therefore, starting from multiple, go through this set of odd numbers and mark the multiples of primes[j] as composite.
                while (multipleIndex < (SIEVE_SIZE >> 1)) {
                    setBit(isPrime, multipleIndex);
                    //Add by 2*primes[j] so that the multiple is still odd.
                    //Adding multiple by 2*primes[j] is the same as adding multipleIndex by primes[j]:
                    multipleIndex += primes[j];
                }
            }
            //Add the primes to the array of primes
            for (num_nums i = 0; i < SIEVE_SIZE >> 1; i++) if (getBit(isPrime, i)) primes[numPrimes++] = begInterval+2*i+1;
        }
    }
}

int main() {
    primes::genPrimes();
    printf("%" PRId32 "\n", primes::primes[primes::MAX_NUM_PRIMES-1]);
    exit(0);
}