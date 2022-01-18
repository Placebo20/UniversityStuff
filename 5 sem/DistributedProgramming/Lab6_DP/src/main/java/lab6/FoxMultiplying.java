package lab6;

public class FoxMultiplying {

    private static int[][] a;
    private static int[][] b;
    private static int amountOfProcess;
    private static int[][] result;

    public static int[][] multiply(int[][] a, int[][] b, int amountOfProcess){
        FoxMultiplying.a = a;
        FoxMultiplying.b = b;
        FoxMultiplying.amountOfProcess = amountOfProcess;

        result = new int[a.length][a.length];

        for(int i = 0; i < a.length; i++){
            for(int j = 0; j < a.length; j++){
                result[i][j] = 0;
            }
        }

        Thread[] tasks = new Thread[amountOfProcess];
        for(int i = 0; i < tasks.length; i++){
            tasks[i] = new Thread(new Fox(i));
        }

        for (Thread task : tasks) {
            task.start();

        }

        for (Thread task : tasks) {
            try {
                task.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        return result;
    }

    private static class Fox implements Runnable{

        private final int idx;
        public Fox(int part_index){
            this.idx = part_index;
        }

        @Override
        public void run() {
            int pivot = (int) Math.ceil(a.length / (double) amountOfProcess);
            for (int row = idx * pivot; row < (idx + 1) * pivot && row < a.length; row++) {
                int counter = 0;
                int row1 = row;
                int row2 = row;
                while (counter < a.length) {
                    for (int i = 0; i < a.length; i++) {
                        result[row][i] += a[row][row2] * b[row1][i];
                    }

                    row1 = (row1 + 1) % a.length;
                    row2 = (row2 + 1) % a.length;
                    counter++;
                }
            }
        }
    }
}