package c;

import java.util.concurrent.RecursiveTask;

public class Competition extends RecursiveTask<MonkFighter> {
    private MonkFighter[] monkFighters;
    private int start;
    private int end;

    public Competition(Integer countMonkFighters) {
        this.monkFighters = new MonkFighter[countMonkFighters];
        for(int i = 0; i < countMonkFighters; i++) {
            this.monkFighters[i] = new MonkFighter();
            System.out.println(this.monkFighters[i].toString());
        }
        this.start = 0;
        this.end = monkFighters.length - 1;
    }
    private Competition(MonkFighter[] monkFighters, int end, int start) {
        this.monkFighters = monkFighters;
        this.start = start;
        this.end = end;
    }
    protected MonkFighter compute() {
        int length = end - start;
        if(length == 0)return monkFighters[end];
        else if(length == 1) return MonkFighter.FIGHT(monkFighters[end], monkFighters[start]);
        else {
            Competition leftChampion = new Competition(monkFighters, start, (end + start)/2);
            leftChampion.fork();

            Competition rightChampion = new Competition(monkFighters,(end + start)/2+1,end);
            rightChampion.fork();

            return MonkFighter.FIGHT(leftChampion.join(), rightChampion.join());
        }
    }
}
