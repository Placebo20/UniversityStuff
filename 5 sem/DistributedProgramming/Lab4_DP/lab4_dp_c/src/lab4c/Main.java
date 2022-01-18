package lab4c;

public class Main {
    public static void main(String[] args) {
        Matrix matrix = new Matrix(5);
        WorkThread workThread1 = new WorkThread(matrix, 1);
        WorkThread workThread2 = new WorkThread(matrix, 2);
        WorkThread workThread3 = new WorkThread(matrix, 3);
        WorkThread workThread4 = new WorkThread(matrix, 4);

        workThread1.setDaemon(true);
        workThread2.setDaemon(true);
        workThread3.setDaemon(true);
        workThread4.setDaemon(true);

        try {
            workThread4.start();
            workThread1.start();
            Thread.sleep(500);
            workThread2.start();
            Thread.sleep(500);
            workThread3.start();

            workThread1.join();
            workThread2.join();
            workThread3.join();
            workThread4.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
