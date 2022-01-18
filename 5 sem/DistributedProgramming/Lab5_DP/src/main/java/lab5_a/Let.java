package lab5_a;

public class Let {
    private final int partiesAtStart;
    private int partiesAwait;

    public Let(int parties) {
        this.partiesAtStart = parties;
        this.partiesAwait = parties;
    }

    public synchronized void await() throws InterruptedException {
        partiesAwait--;
        if(partiesAwait > 0) this.wait();


        partiesAwait = partiesAtStart;
        notifyAll();
    }
}