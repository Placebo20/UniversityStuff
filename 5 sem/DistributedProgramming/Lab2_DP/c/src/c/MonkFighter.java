package c;

import java.util.Random;

public class MonkFighter implements Comparable {
    private Integer attackPower;
    private String monastery;
    private int monkFighterId;
    private static int countMonkFighters = 0;
    public MonkFighter() {
        Random rand = new Random();
        attackPower = rand.nextInt(100);
        monastery = (rand.nextInt(2) == 0) ? "Huan-un" : "Huan-in";
        monkFighterId = countMonkFighters++;
    }

    @Override
    public String toString() {
        return "Monk-Fighter #" + monkFighterId + " (from " + monastery + " monastery) | Power of Attack: " + attackPower;
    }

    public int compareTo(Object obj) {
        MonkFighter other = (MonkFighter) obj;
        if(this.attackPower > other.attackPower) return 1;
        else if(this.attackPower < other.attackPower) return -1;
        else return 0;
    }
    static MonkFighter FIGHT(MonkFighter left, MonkFighter right){
        if(left.attackPower > right.attackPower) return left;
        else return right;
    }
}
