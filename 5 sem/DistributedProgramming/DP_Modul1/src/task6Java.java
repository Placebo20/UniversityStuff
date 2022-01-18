import java.util.Queue;
import java.util.LinkedList;
import java.util.List;

class Client {
    private String name;
    private int task;
    public Client(String name, int task){
        this.name = name;
        this.task = task;
    }
    public String getName() { return name; }
    public int getTask() { return task; }
    @Override
    public String toString() { return getName(); }
}

class Cashbox extends Thread {
    volatile private Queue<Client> clientQueue;
    public Cashbox(String name, Queue<Client> clientQueue){
        super(name);
        this.clientQueue = clientQueue;
        this.setDaemon(true);
        start();
    }
    @Override
    public void run() {
        while(true){
            try {
                Client curClient = null;
                synchronized (clientQueue) {
                    while (clientQueue.size() == 0) {
                        clientQueue.wait();
                    }
                    curClient = clientQueue.poll();
                    clientQueue.notifyAll();
                }
                System.out.println(this + " started to help " + curClient);
                Thread.sleep(1000 * curClient.getTask());
                System.out.println(curClient.getTask() + " was done " + curClient + " by " + this);
            }catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    @Override
    public String toString() { return getName(); }
}

public class task6Java {
    public static void main(String[] args) throws InterruptedException {
        List<Cashbox> cashboxes = new LinkedList<>();
        Queue<Client> clients = new LinkedList<Client>();
        for(int i = 0; i < 3; i++){
            cashboxes.add(new Cashbox("Cashbox " + i, clients));
        }
        for(int i = 0; i < 10; i++){
            synchronized (clients) {
                clients.add(new Client("Client "+ i, i + (int)((9 * Math.random()))));
                clients.notifyAll();
            }
        }
        synchronized (clients){
            while(!clients.isEmpty()){
                clients.wait();
            }
        }
        System.out.println("All is done!");
    }
}
