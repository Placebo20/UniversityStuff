package lab5_b;

import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class Swaper implements Runnable {
    private final Random random = new Random();
    private String currStr;
    private final CyclicBarrier barrier;
    private final Checker checker;
    private boolean running = true;
    private int counterAB;
    private final int idx;

    public Swaper(String str, CyclicBarrier barrier, Checker checker, int idx){
        this.currStr = str;
        this.barrier = barrier;
        this.checker = checker;
        this.counterAB = countAbMentioning(str);
        this.idx = idx;
    }

    @Override
    public void run(){
        while(running) {
            int randIndex = random.nextInt(currStr.length());
            switch (currStr.charAt(randIndex)) {
                case 'A': {
                    currStr = currStr.substring(0, randIndex) + 'C' + currStr.substring(randIndex + 1);
                    counterAB--;
                    break;
                }
                case 'B': {
                    currStr = currStr.substring(0, randIndex) + 'D' + currStr.substring(randIndex + 1);
                    counterAB--;
                    break;
                }
                case 'C': {
                    currStr = currStr.substring(0, randIndex) + 'A' + currStr.substring(randIndex + 1);
                    counterAB++;
                    break;
                }
                case 'D': {
                    currStr = currStr.substring(0, randIndex) + 'B' + currStr.substring(randIndex + 1);
                    counterAB++;
                    break;
                }
            }
            checker.getInfo(counterAB);
            System.out.println("Thread #" + this.idx + " " + currStr + " " + counterAB);
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
            if(this.idx == 1) {
                System.out.println();
            }
            running = checker.isRunning();
        }
    }

    private int countAbMentioning(String str) {
        int count = 0;
        for(int i = 0; i < str.length(); i++){
            if(str.charAt(i) == 'A' || str.charAt(i) == 'B'){
                count++;
            }
        }
        return count;
    }
}