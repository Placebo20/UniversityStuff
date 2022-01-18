package lab5_b;

import java.util.Arrays;

public class Checker {
    private boolean isRunning = true;
    private int threadsCounter = 0;
    private final int threadsNumber;
    private final int[] threadsInfo;
    private boolean aBoolean = false;

    public Checker(int threadNum) {
        threadsNumber = threadNum;
        threadsInfo = new int[threadNum];
    }

    public boolean isRunning() {
        return isRunning;
    }

    public void equalityCheck() {
        boolean isEqual = true;
        Arrays.sort(threadsInfo);
        for (int i = 1; i < threadsInfo.length - 2; i++) {
            if (threadsInfo[i] != threadsInfo[i + 1]) {
                isEqual = false;
                break;
            }
        }
        if (isEqual) {
            if (threadsInfo[0] == threadsInfo[1] || threadsInfo[threadsInfo.length - 1] == threadsInfo[1]) {
                isRunning = false;
                System.out.println("Are equal");
            }
        }
    }

    public synchronized void getInfo(int data) {
        threadsInfo[threadsCounter] = data;
        threadsCounter++;
        if (threadsCounter == threadsNumber) {
            notifyAll();
            aBoolean = true;
        }
        while (!aBoolean) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        threadsCounter--;
        if (threadsCounter == 0) {
            equalityCheck();
            aBoolean = false;
        }
    }
}
