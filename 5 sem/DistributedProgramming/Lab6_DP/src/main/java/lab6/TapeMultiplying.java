package lab6;

public class TapeMultiplying {

    private static int[][] a;
    private static int[][] b;
    private static int amountOfProcess;
    private static int[][] res;

    public static int[][] multiply(int[][] a, int[][] b, int process_amount){
        TapeMultiplying.a = a;
        TapeMultiplying.b = b;
        TapeMultiplying.amountOfProcess = process_amount;

        res = new int[a.length][a.length];

        for(int i = 0; i < a.length; i++){
            for(int j = 0; j < a.length; j++){
                res[i][j] = 0;
            }
        }

        Thread[] tapes = new Thread[process_amount];
        for(int i = 0; i < tapes.length; i++){
            tapes[i] = new Thread(new Tape(i));
        }

        for (Thread tape : tapes) {
            tape.start();
        }

        for (Thread tape : tapes) {
            try {
                tape.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        return res;
    }

    private static class Tape implements Runnable{

        private final int idx;
        public Tape(int part_index){
            this.idx = part_index;
        }

        @Override
        public void run() {

            int pivot = (int) Math.ceil(a.length / (double) amountOfProcess);
            for (int row = idx * pivot; row < (idx + 1) * pivot && row < a.length; row++) {
                int counter = 0;
                int index = row;
                while (counter < a.length) {
                    int cell = 0;
                    for (int i = 0; i < a.length; i++) {
                        cell += a[row][i] * b[i][index];
                    }

                    res[row][index] = cell;
                    counter++;
                    index = (index + 1) % a.length;
                }
            }
        }
    }
}