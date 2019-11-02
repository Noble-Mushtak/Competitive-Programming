import java.math.BigInteger;
import java.io.*;
import java.util.*;

public class crypto {
    static int numTestCases, numNums, numPrimes;
    static BigInteger[] nums;
    static TreeSet<BigInteger> primesSet;
    static BigInteger[] primes;
    static int[][] indices;
    static int[] letterIndices;
    static boolean unknown;
    
    static void printPrimesSet() {
        TreeSet<BigInteger> copyPrimesSet = new TreeSet<>(primesSet);
        while (!primesSet.isEmpty()) {
            System.out.print(primesSet.first()+" ");
            primesSet.remove(primesSet.first());
        }
        System.out.println("");
        primesSet = copyPrimesSet;
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        numTestCases = in.nextInt();
        
        for (int l = 0; l < numTestCases; l++) {
            primesSet = new TreeSet<BigInteger>();
            in.nextInt(); //Discard N
            numNums = in.nextInt();
            
            nums = new BigInteger[numNums];
            for (int i = 0; i < numNums; i++) {
                nums[i] = new BigInteger(in.next());
                if (i > 0) {
                    BigInteger gcd = nums[i].gcd(nums[i-1]);
                    if (gcd.compareTo(nums[i]) != 0) primesSet.add(gcd);
                }
            }
            for (int i = 0; i < numNums; i++) {
                Iterator<BigInteger> primesItr = primesSet.iterator();
                while (primesItr.hasNext()) {
                    BigInteger curPrime = primesItr.next();
                    if (nums[i].mod(curPrime).compareTo(BigInteger.ZERO) == 0) {
                        primesSet.add(nums[i].divide(curPrime));
                        break;
                    }
                }
            }
            
            numPrimes = 0;
            primes = new BigInteger[primesSet.size()];
            while (!primesSet.isEmpty()) {
                primes[numPrimes++] = primesSet.first();
                primesSet.remove(primesSet.first());
            }
            if (numPrimes != 26) {
                System.err.println("ERROR: NUMBER OF PRIMES IS "+numPrimes);
                System.exit(1);
            }
            
            indices = new int[numNums][2];
            for (int i = 0; i < numNums; i++) {
                for (int j = 0; j < numPrimes; j++) {
                    if (nums[i].mod(primes[j]).compareTo(BigInteger.ZERO) == 0) {
                        indices[i][0] = j;
                        BigInteger otherPrime = nums[i].divide(primes[j]);
                        int minIndex = 0, maxIndex = numPrimes-1, mid = 0;
                        while (minIndex <= maxIndex) {
                            mid = (minIndex+maxIndex)/2;
                            int comparison = otherPrime.compareTo(primes[mid]);
                            if (comparison == 0) break;
                            if (comparison > 0) minIndex = mid+1;
                            else maxIndex = mid-1;
                        }
                        indices[i][1] = mid;
                    }
                }
            }
            
            unknown = true;
            letterIndices = new int[numNums+1];
            for (int j = 0; j < 2; j++) {
                if ((indices[0][j] != indices[1][0]) && (indices[0][j] != indices[1][1])) {
                     letterIndices[0] = indices[0][j];
                     unknown = false;
                     break;
                }
            }
            for (int i = 0; i < numNums; i++) {
                if (unknown) {
                    for (int j = 0; j < 2; j++) {
                        if ((indices[i][j] != indices[i+1][0]) && (indices[i][j] != indices[i+1][1])) {
                             letterIndices[i] = indices[i][j];
                             for (int k = i-1; k >= 0; k--) {
                                 int m;
                                 for (m = 0; m < 2; m++) {
                                      if (indices[k][m] != letterIndices[k+1]) {
                                           letterIndices[k] = indices[k][m];
                                           break;
                                      }
                                 }
                                 if (m == 2) letterIndices[k] = letterIndices[k+1];
                             }
                             unknown = false;
                             break;
                        }
                    }
                }
                int m;
                for (m = 0; m < 2; m++) {
                    if (indices[i][m] != letterIndices[i]) {
                        letterIndices[i+1] = indices[i][m];
                        break;
                    }
                }
                if (m == 2) letterIndices[i+1] = letterIndices[i];
            }
            System.out.print("Case #"+(l+1)+": ");
            for (int i = 0; i < numNums+1; i++) System.out.print((char)(letterIndices[i]+65));
            System.out.println("");
        }
    }
}