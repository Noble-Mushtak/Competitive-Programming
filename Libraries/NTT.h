/**
 * Functions related to NTT
 * Documentation coming soon!
*/

#include <cinttypes>
#define REP(token, num) for (token = 0; token < num; token++)

namespace NTT {
    typedef int32_t num;
    typedef int32_t num_nums;
    typedef int64_t long_num;

    const num_nums ARRAY_SIZE = 131072;
    const num_nums ARRAY_SIZE_POWER = 17;
    num poly3a[ARRAY_SIZE], poly3b[ARRAY_SIZE], ntt1a[ARRAY_SIZE], ntt2a[ARRAY_SIZE], ntt1b[ARRAY_SIZE], ntt2b[ARRAY_SIZE];

    num calcModuloInverse(num dividend, num MOD) {
        num lastRemainder = dividend, lastInverse = 1, remainder = MOD, inverse = 0, quotient, temp;
        while (remainder) {
            quotient = lastRemainder/remainder;
            temp = remainder, remainder = lastRemainder % remainder, lastRemainder = temp;
            temp = inverse, inverse = lastInverse-quotient*inverse, lastInverse = temp;
        }
        if (lastInverse < 0) lastInverse += MOD;
        return lastInverse;
    }
    
    /*num multiplyMod(num num1, num num2, num MOD) {
        num result;
        __asm__ volatile ("mulq %2 \n\t divq %3" : "=d" (result): "r" (num1), "r" (num2), "r" (MOD) : "cc");
        return result;
    } // */
    num multiplyMod(num num1, num num2, num MOD) { return ((long_num)num1*num2) % MOD; }

    num calcModuloExp(num base, num exp, num MOD) {
        num result = 1, cur = base;
        while (exp) {
            if (exp & 1) result = multiplyMod(result, cur, MOD);
            cur = multiplyMod(cur, cur, MOD), exp >>= 1;
        }
        return result;
    }

    num MOD1 = 998244353, rootsOfUnity1[300000], r1 = 119, k1 = 23, g1 = 3;
    num MOD2 = 1004535809, rootsOfUnity2[300000], r2 = 479, k2 = 21, g2 = 3;
    num MOD3 = 2013265921, rootsOfUnity3[300000], r3 = 15, k3 = 27, g3 = 31;
    void calcRootsOfUnity(num MOD, num *rootsOfUnity, num r, num k, num g, num arrLengthPower) {
        num rootOfUnity = calcModuloExp(g, r << (k-arrLengthPower), MOD);
        num_nums i;
        rootsOfUnity[0] = 1;
        REP(i, 1 << arrLengthPower) rootsOfUnity[i+1] = multiplyMod(rootsOfUnity[i], rootOfUnity, MOD);
    }

    num_nums bitReversed[300000];
    void computeBitReversals(num_nums power) {
        num_nums max = 1 << power, i;
        REP(i, max) bitReversed[i] = (bitReversed[i >> 1] | ((i & 1) << power)) >> 1;
    }

    void NTT(num MOD, num *rootsOfUnity, num_nums maxArrLengthPower, num *arr, num_nums arrLengthPower, num *ntt, bool inverse) {
        if (arrLengthPower == 0) {
            ntt[0] = arr[0];
            return;
        }
        num_nums arrLength = 1 << arrLengthPower, maxArrLength = 1 << maxArrLengthPower;
        num_nums i, j, kPower, k, halfK, jumpSizePower, correctIndex1, correctIndex2;
        num storeNum, *oldNtt = arr;
        //In each iteration, the NTTs of groups of k elements are computed.
        //(i.e. groups of 2, then groups of 4, then groups of 8, etc.)
        for (int kPower = 1; kPower <= arrLengthPower; kPower++) {
            k = 1 << kPower;
            halfK = 1 << (kPower-1);
            jumpSizePower = maxArrLengthPower-kPower;
            //In each iteration, NTT of one group of k elements is computed.
            for (int j = 0; j < arrLength; j += k) {
                //In each iteration, NTT values for ntt[i+j] and ntt[i+j+halfK] are computed.
                for (int i = 0; i < halfK; i++) {
                    correctIndex1 = i+j, correctIndex2 = i+j+halfK;
                    //Indexes in arr must be accessed in bit-reversed order:
                    if (oldNtt == arr) {
                        correctIndex1 = bitReversed[correctIndex1] >> (maxArrLengthPower-arrLengthPower);
                        correctIndex2 = bitReversed[correctIndex2] >> (maxArrLengthPower-arrLengthPower);
                    }

                    //Let ind be either i+j or i+j+halfK
                    //NTT_k[ind] = NTT_even,halfK[ind % halfK] + rootOfUnity*NTT_odd,halfK[ind % halfK]
                    //NTT_even,halfK[ind] is oldNtt[i+j]
                    //NTT_odd,halfK[ind % halfK] is oldNtt[i+j+halfK]
                    //rootOfUnity is positive for ind=i+j, negative for ind=i+j+halfK
                    storeNum = multiplyMod(rootsOfUnity[inverse ? (maxArrLength-(i << jumpSizePower)) : (i << jumpSizePower)], oldNtt[correctIndex2], MOD);
                    //Note that order of operations is crucial: Otherwise, ntt[i+j] will be modified before it can be used to compute ntt[i+j+halfK]
                    ntt[i+j+halfK] = oldNtt[correctIndex1]-storeNum;
                    if (ntt[i+j+halfK] < 0) ntt[i+j+halfK] += MOD;
                    ntt[i+j] = oldNtt[correctIndex1]+storeNum;
                    if (ntt[i+j] >= MOD) ntt[i+j] -= MOD;
                }
            }
            //After the first iteration, we have populated ntt, so oldNtt is now ntt.
            oldNtt = ntt;
        }
        if (inverse) {
            num_nums inverseLength = calcModuloInverse(arrLength, MOD);
            REP(i, arrLength) ntt[i] = multiplyMod(ntt[i], inverseLength, MOD);
        }
    }

    void initNTT() {
        calcRootsOfUnity(MOD1, rootsOfUnity1, r1, k1, g1, ARRAY_SIZE_POWER);
        calcRootsOfUnity(MOD2, rootsOfUnity2, r2, k2, g2, ARRAY_SIZE_POWER);
        computeBitReversals(ARRAY_SIZE_POWER);
    }

    void convolution(num *poly1, num_nums poly1Length, num *poly2, num_nums poly2Length, long_num *poly3, num_nums maxArrLengthPower) {
        num_nums i, maxLength = poly1Length+poly2Length-1, arrLength = 1, arrLengthPower;
        for (arrLengthPower = 1; arrLengthPower <= maxArrLengthPower; arrLengthPower++) {
            arrLength <<= 1;
            if (maxLength < arrLength) break;
        }

        for (i = poly1Length; i < arrLength; i++) poly1[i] = 0;
        for (i = poly2Length; i < arrLength; i++) poly2[i] = 0;

        NTT(MOD1, rootsOfUnity1, maxArrLengthPower, poly1, arrLengthPower, ntt1a, false);
        NTT(MOD1, rootsOfUnity1, maxArrLengthPower, poly2, arrLengthPower, ntt2a, false);
        REP(i, arrLength) ntt1a[i] = multiplyMod(ntt1a[i], ntt2a[i], MOD1);
        NTT(MOD1, rootsOfUnity1, maxArrLengthPower, ntt1a, arrLengthPower, poly3a, true);

        NTT(MOD2, rootsOfUnity2, maxArrLengthPower, poly1, arrLengthPower, ntt1b, false);
        NTT(MOD2, rootsOfUnity2, maxArrLengthPower, poly2, arrLengthPower, ntt2b, false);
        REP(i, arrLength) ntt1b[i] = multiplyMod(ntt1b[i], ntt2b[i], MOD2);
        NTT(MOD2, rootsOfUnity2, maxArrLengthPower, ntt1b, arrLengthPower, poly3b, true);

        long_num multiplier;
        num mod1Inverse = calcModuloInverse(MOD1, MOD2);
        REP(i, arrLength) {
            multiplier = multiplyMod(mod1Inverse, poly3b[i]-poly3a[i], MOD2);
            if (multiplier < 0) multiplier += MOD2;
            poly3[i] = poly3a[i]+multiplier*MOD1;
            //printf("F %i %i %i\n", i, poly3a[i], poly3b[i]);
        }
        //puts("HEY");
    }
}