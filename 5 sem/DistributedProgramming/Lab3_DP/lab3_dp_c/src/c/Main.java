package c;

import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

public class Main {
    private final List<Smoker> SMOKERS;
    private final Mediator MEDIATOR;
    private final AtomicInteger PROCESS_OF_SMOKING;
    private final AtomicBoolean PROCESS_OF_MEDIATING;

    private static SecureRandom rand;

    Main(){
        MEDIATOR = new Mediator(10);
        SMOKERS = new ArrayList<>();
        for (int i = 0; i < 3; i++){
            SMOKERS.add(new Smoker(i));
        }
        rand = new SecureRandom();
        PROCESS_OF_SMOKING = new AtomicInteger(-1);
        PROCESS_OF_MEDIATING = new AtomicBoolean(true);
    }

    public static void main(String[] args){
        Main SmokerMediatorBehaviorProgram = new Main();
        SmokerMediatorBehaviorProgram.execute();
    }

    public void execute(){
        for (Smoker s : SMOKERS){
            s.start();
        }
        MEDIATOR.start();
    }

    private class Smoker extends Thread{
        public Integer item;
        Smoker(Integer item){
            this.item = item;
        }

        @Override
        public void run() {
            while (PROCESS_OF_MEDIATING.get()) {
                if (item.equals(PROCESS_OF_SMOKING.get())) {
                    System.out.println(Thread.currentThread().getName() + " started to smoke " + item);
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println(Thread.currentThread().getName() + " extinguished the goby " + item);
                    PROCESS_OF_SMOKING.set(-1);
                }
            }
        }
    }

    private class Mediator extends Thread{
        public Integer iterations;

        Mediator(Integer iterations){
            this.iterations = iterations;
        }

        @Override
        public void run(){
            int variable;
            for(int i = 0; i < iterations; i++){
                variable = rand.nextInt(3);
                System.out.println(Thread.currentThread().getName() + " variable " + variable );
                PROCESS_OF_SMOKING.set(variable);
                while (PROCESS_OF_SMOKING.get() != -1){
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
            PROCESS_OF_MEDIATING.set(false);
        }
    }
}