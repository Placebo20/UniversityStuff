package c;

import java.util.concurrent.ForkJoinPool;

public class Main {
    public static void main(String[] args){
        Integer countMonkFighters = 100;
        Competition competition = new Competition(countMonkFighters);
        ForkJoinPool pool = new ForkJoinPool();
        MonkFighter winner = pool.invoke(competition);
        System.out.println("The winner is " + winner.toString());
    }
}
