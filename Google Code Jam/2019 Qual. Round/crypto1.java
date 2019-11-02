import java.math.BigInteger;
import java.security.SecureRandom;
import java.io.*;
import java.util.*;

public class crypto1 {
    public final static SecureRandom randomGen = new SecureRandom();
    
    public static BigInteger random(BigInteger max) {
        BigInteger randomNum = new BigInteger(max.bitLength(), randomGen);
        while (randomNum.compareTo(max) >= 0) randomNum = new BigInteger(max.bitLength(), randomGen);
        return randomNum;
    }
    
    public static BigInteger findDivisor(BigInteger num) {
        BigInteger divisor = BigInteger.ONE;
        BigInteger slowSequence = random(num);
        BigInteger fastSequence = slowSequence;
        while (divisor.compareTo(BigInteger.ONE) == 0) {
            slowSequence = slowSequence.multiply(slowSequence).add(BigInteger.ONE).mod(num);
            fastSequence = fastSequence.multiply(fastSequence).add(BigInteger.ONE).mod(num);
            fastSequence = fastSequence.multiply(fastSequence).add(BigInteger.ONE).mod(num);
            divisor = slowSequence.subtract(fastSequence).gcd(num);
        }
        return divisor;
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        BigInteger int1 = new BigInteger(in.next());
        BigInteger int2 = findDivisor(int1);
        System.out.println(int2.toString());
    }
}