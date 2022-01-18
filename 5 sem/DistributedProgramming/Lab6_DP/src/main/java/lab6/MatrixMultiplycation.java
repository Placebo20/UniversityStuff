package lab6;

import java.security.SecureRandom;
import java.util.Arrays;

public class MatrixMultiplycation {
    private static final int[] SIZES = {10, 100, 500, 1000, 1500, 2000, 2500, 3000};


    public static void main(String[] args){
        SecureRandom random = new SecureRandom();
        long start;
        long end;
        System.out.println("SIZE\t\tSIMPLE\t\tTAPE(2)\t\tTAPE.(4)\t\tFOX(2)\t\tFOX(4)\t\tCANNON(2)\t\tCANNON(4)\n");
        for (int size : SIZES) {
            int[][] a = new int[size][size];
            int[][] b = new int[size][size];

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    a[i][j] = random.nextInt(10);
                    b[i][j] = random.nextInt(10);
                }
            }

            long[] results = new long[7];
            start = System.currentTimeMillis();
            int[][] simple = simpleMultiplying(a, b);
            end = System.currentTimeMillis();
            results[0] = end - start;
            start = System.currentTimeMillis();
            int[][] tape2 = TapeMultiplying.multiply(a, b, 2);
            end = System.currentTimeMillis();
            results[1] = end - start;
            start = System.currentTimeMillis();
            int[][] tape4 = TapeMultiplying.multiply(a, b, 4);
            end = System.currentTimeMillis();
            results[2] = end - start;
            start = System.currentTimeMillis();
            int[][] fox2 = FoxMultiplying.multiply(a, b, 2);
            end = System.currentTimeMillis();
            results[3] = end - start;
            start = System.currentTimeMillis();
            int[][] fox4 = FoxMultiplying.multiply(a, b, 4);
            end = System.currentTimeMillis();
            results[4] = end - start;
            start = System.currentTimeMillis();
            int[][] cannon2 = CannonMultiplying.multiply(a, b, 2);
            end = System.currentTimeMillis();
            results[5] = end - start;
            start = System.currentTimeMillis();
            int[][] cannon4 = CannonMultiplying.multiply(a, b, 4);
            end = System.currentTimeMillis();
            results[6] = end - start;

            System.out.println("Arrays equal:");
            System.out.println(Arrays.deepEquals(simple, tape2)
                    + " " + Arrays.deepEquals(simple, fox2)
                    + " " + Arrays.deepEquals(simple, cannon2));

            System.out.print(size);
            for (long r : results) {
                System.out.print("\t\t" + r + " ms");
            }
            System.out.println();
        }
    }

    public static int[][] simpleMultiplying(int[][] a, int[][] b){
        int[][] res = new int[a.length][a.length];

        for(int i = 0; i < a.length; i++){
            for(int j = 0; j < a.length; j++){
                res[i][j] = 0;
                for(int k = 0; k < a.length; k++){
                    res[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return res;
    }
}