/**
 * Functions related to FFT
 * Documentation coming soon!
*/

#include <cmath>
#include <cinttypes>
#define REP(token, num) for (token = 0; token < num; token++)

struct complex {
    double real, imag;
    complex() : real(0), imag(0) {}
    complex(double r, double i) : real(r), imag(i) {}
    
    complex scaleBy(double factor) {
        return complex(real*factor, imag*factor);
    }
    
    complex operator+(complex other) {
        return complex(real+other.real, imag+other.imag);
    }
    complex operator-(complex other) {
        return complex(real-other.real, imag-other.imag);
    }
    complex operator*(complex other) {
        return complex(
            real*other.real - imag*other.imag,
            real*other.imag + imag*other.real
        );
    }
    complex operator/(complex other) {
        double otherMagnitudeSquared = other.real*other.real+other.imag*other.imag;
        //(a+bi)/(c+di)=(a+bi)(c-di)/|c+di|^2
        //(a+bi)(c-di)=(ac+bd) + (bc-ad) i
        return complex(
            (real*other.real + imag*other.imag)/otherMagnitudeSquared,
            (imag*other.real - imag*other.real)/otherMagnitudeSquared
        );
    }
};

namespace FFT {
    typedef int32_t num_nums;
    
    const num_nums ARRAY_SIZE = 262144;
    const num_nums ARRAY_SIZE_POWER = 18;
    complex preFft[ARRAY_SIZE], fft1[ARRAY_SIZE], fft2[ARRAY_SIZE], postFft[ARRAY_SIZE];

    complex rootsOfUnity[300000];
    void calcRootsOfUnity(complex *rootsOfUnity, num_nums arrLengthPower) {
        num_nums i, arrLength = (1 << arrLengthPower);
        rootsOfUnity[0].real = 1, rootsOfUnity[0].imag = 0;
        REP(i, 1 << arrLengthPower) {
            rootsOfUnity[i+1].real = cos((i+1)*2*M_PI/arrLength);
            rootsOfUnity[i+1].imag = sin((i+1)*2*M_PI/arrLength);
        }
    }

    num_nums bitReversed[300000];
    void computeBitReversals(num_nums power) {
        num_nums max = 1 << power, i;
        REP(i, max) bitReversed[i] = (bitReversed[i >> 1] | ((i & 1) << power)) >> 1;
    }

    void FFT(complex *rootsOfUnity, num_nums maxArrLengthPower, complex *arr, num_nums arrLengthPower, complex *fft, bool inverse) {
        if (arrLengthPower == 0) {
            fft[0] = arr[0];
            return;
        }
        num_nums arrLength = 1 << arrLengthPower, maxArrLength = 1 << maxArrLengthPower;
        num_nums i, j, kPower, k, halfK, jumpSizePower, correctIndex1, correctIndex2;
        complex storeNum, *oldFft = arr;
        //In each iteration, the FFTs of groups of k elements are computed.
        //(i.e. groups of 2, then groups of 4, then groups of 8, etc.)
        for (int kPower = 1; kPower <= arrLengthPower; kPower++) {
            k = 1 << kPower;
            halfK = 1 << (kPower-1);
            jumpSizePower = maxArrLengthPower-kPower;
            //In each iteration, FFT of one group of k elements is computed.
            for (int j = 0; j < arrLength; j += k) {
                //In each iteration, FFT values for fft[i+j] and fft[i+j+halfK] are computed.
                for (int i = 0; i < halfK; i++) {
                    correctIndex1 = i+j, correctIndex2 = i+j+halfK;
                    //Indexes in arr must be accessed in bit-reversed order:
                    if (oldFft == arr) {
                        correctIndex1 = bitReversed[correctIndex1] >> (maxArrLengthPower-arrLengthPower);
                        correctIndex2 = bitReversed[correctIndex2] >> (maxArrLengthPower-arrLengthPower);
                    }

                    //Let ind be either i+j or i+j+halfK
                    //FFT_k[ind] = FFT_even,halfK[ind % halfK] + rootOfUnity*FFT_odd,halfK[ind % halfK]
                    //FFT_even,halfK[ind] is oldFft[i+j]
                    //FFT_odd,halfK[ind % halfK] is oldFft[i+j+halfK]
                    //rootOfUnity is positive for ind=i+j, negative for ind=i+j+halfK
                    storeNum = rootsOfUnity[inverse ? (maxArrLength-(i << jumpSizePower)) : (i << jumpSizePower)]*oldFft[correctIndex2];
                    //Note that order of operations is crucial: Otherwise, fft[i+j] will be modified before it can be used to compute fft[i+j+halfK]
                    fft[i+j+halfK] = oldFft[correctIndex1]-storeNum;
                    fft[i+j] = oldFft[correctIndex1]+storeNum;
                }
            }
            //After the first iteration, we have populated fft, so oldFft is now fft.
            oldFft = fft;
        }
        if (inverse) {
            double inverseLength = 1.0/((double)arrLength);
            REP(i, arrLength) fft[i] = fft[i].scaleBy(inverseLength);
        }
    }

    void initFFT() {
        calcRootsOfUnity(rootsOfUnity, ARRAY_SIZE_POWER);
        computeBitReversals(ARRAY_SIZE_POWER);
    }

    void convolution(double *poly1, num_nums poly1Length, double *poly2, num_nums poly2Length, double *poly3, num_nums maxArrLengthPower) {
        num_nums i, maxLength = poly1Length+poly2Length-1, arrLength = 1, arrLengthPower;
        for (arrLengthPower = 1; arrLengthPower <= maxArrLengthPower; arrLengthPower++) {
            arrLength <<= 1;
            if (maxLength < arrLength) break;
        }

        for (i = poly1Length; i < arrLength; i++) poly1[i] = 0;
        for (i = poly2Length; i < arrLength; i++) poly2[i] = 0;
        REP(i, arrLength) preFft[i].real = poly1[i], preFft[i].imag = poly2[i];

        FFT(rootsOfUnity, maxArrLengthPower, preFft, arrLengthPower, fft1, false);
        /*
        http://www.ti.com/lit/an/spra291/spra291.pdf
        Let n be arrLength.
        Transform of poly1 is 1/2 (fft1[i] + conjugate(fft1[n-i]))
        Transform of poly2 is 1/(2i) (fft1[i] - conjugate(fft1[n-i]))
        Transform of convolution is 1/(4i) (fft1[i]^2 - conjugate(fft1[n-i])^2)
        Thus, square fft1 and then put fft1[i] - conjugate(fft1[n-i]) into fft2
        fft2 is now 4i times the transform of the convolution,
        so after FFT, we divide by 4i

        Note that (n-i) & (n-1) is used as a faster way of (n-i) % n, so i=0 case does not fail
        */
        REP(i, arrLength) fft1[i] = fft1[i]*fft1[i];
        REP(i, arrLength) {
            fft2[i].real = fft1[i].real-fft1[(arrLength-i) & (arrLength-1)].real;
            fft2[i].imag = fft1[i].imag+fft1[(arrLength-i) & (arrLength-1)].imag;
        }
        FFT(rootsOfUnity, maxArrLengthPower, fft2, arrLengthPower, postFft, true);
        REP(i, arrLength) {
            poly3[i] = postFft[i].imag/4.0;
        }
    }
}