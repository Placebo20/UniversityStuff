package lab5_a;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

public class Recruits implements Runnable {
    private static final AtomicBoolean finished = new AtomicBoolean(false);
    private static final List<Boolean> finishedPart = new ArrayList<>();

    private final int[] recruits;
    private final Let let;

    private final int partIndex;
    private final int leftIndex;
    private final int rightIndex;

    public Recruits(int[] recruits, Let let, int partIndex, int leftIndex, int rightIndex) {
        this.recruits = recruits;
        this.let = let;
        this.partIndex = partIndex;
        this.leftIndex = leftIndex;
        this.rightIndex = rightIndex;
    }

    public void run() {
        while (!finished.get()) {
            boolean currentPartFinished = finishedPart.get(partIndex);
            if (!currentPartFinished) {
                if (partIndex == 0) System.out.println(Arrays.toString(recruits));
                boolean isFormatted = true;
                for (int i = leftIndex; i < rightIndex - 1; i++) {
                    if (recruits[i] != recruits[i+1]){
                        if(recruits[i] == 1)
                            recruits[i] = 0;
                        else
                            recruits[i] = 1;
                        isFormatted = false;
                    }
                }
                if(isFormatted) finish();
            }
            try {let.await();}
            catch (InterruptedException e) {e.printStackTrace();}
        }
    }

    private void finish() {
        finishedPart.set(partIndex, true);
        for (boolean part: finishedPart) 
            if (!part) return;              
        finished.set(true);
    }

    public static void fillFinishedArray(int numberOfParts) {
        for (int i = 0; i < numberOfParts; i++) finishedPart.add(false);
        
    }
}