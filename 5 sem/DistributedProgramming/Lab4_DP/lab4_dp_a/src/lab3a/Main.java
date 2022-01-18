package lab3a;

public class Main {
    public static void main(String[] args){
        Data data = new Data();
        WorkThread workThread1 = new WorkThread(1, data);
        WorkThread workThread2 = new WorkThread(2, data);
        WorkThread workThread3 = new WorkThread(3, data);

        workThread1.setDaemon(true);
        workThread2.setDaemon(true);
        workThread3.setDaemon(true);

        try {
            workThread1.start();
            Thread.sleep(500);
            workThread2.start();
            Thread.sleep(500);
            workThread3.start();

            workThread1.join();
            workThread2.join();
            workThread3.join();
        } catch(InterruptedException e){
            e.printStackTrace();
        }
    }
}
