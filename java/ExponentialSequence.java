import java.math.BigInteger;

public class ExponentialSequence {
    private final BigInteger base;
    private final BigInteger multiplier;
    private final int columns;

    public ExponentialSequence(long base, long multiplier, int columns) {
        if (columns <= 0) {
            throw new IllegalArgumentException("Columns must be greater than zero");
        }
        this.base = BigInteger.valueOf(base);
        this.multiplier = BigInteger.valueOf(multiplier);
        this.columns = columns;
    }

    private BigInteger geometricSum(BigInteger s, int count) {
        if (count == 0) return BigInteger.ZERO;
        if (s.equals(BigInteger.ONE)) return BigInteger.valueOf(count);
        BigInteger num = s.multiply(s.pow(count).subtract(BigInteger.ONE));
        BigInteger den = s.subtract(BigInteger.ONE);
        return num.divide(den);
    }

    public BigInteger getTerm(long k) {
        if (k < 1) throw new IllegalArgumentException("k must be >= 1");
        long kMinus1 = k - 1;
        long q = kMinus1 / columns;
        long r = kMinus1 % columns;

        BigInteger termB = base.pow((int)(q + 1));
        BigInteger termS = multiplier.pow((int)(r + 1));
        return termB.multiply(termS);
    }

    public BigInteger sumTerms(long N) {
        if (N == 0) return BigInteger.ZERO;
        long q = N / columns;
        long r = N % columns;

        BigInteger blockSum = geometricSum(multiplier, columns);
        
        BigInteger rowSum;
        if (base.equals(BigInteger.ONE)) {
            rowSum = BigInteger.valueOf(q);
        } else {
            BigInteger num = base.pow((int)q).subtract(BigInteger.ONE).multiply(base);
            BigInteger den = base.subtract(BigInteger.ONE);
            rowSum = num.divide(den);
        }

        BigInteger sumFullBlocks = blockSum.multiply(rowSum);
        BigInteger sumRemaining = BigInteger.ZERO;
        if (r > 0) {
            sumRemaining = base.pow((int)(q + 1)).multiply(geometricSum(multiplier, (int)r));
        }

        return sumFullBlocks.add(sumRemaining);
    }

    public static void main(String[] args) {
        ExponentialSequence seq = new ExponentialSequence(45, 5, 3);
        System.out.println("a_5 = " + seq.getTerm(5));
        System.out.println("Sum for N=10 = " + seq.sumTerms(10));
    }
}
