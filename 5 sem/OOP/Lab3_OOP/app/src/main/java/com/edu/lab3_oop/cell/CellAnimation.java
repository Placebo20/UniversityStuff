package com.edu.lab3_oop.cell;

public class CellAnimation extends Cell{

    private final int typeOfAnimation; // Тип анімації
    private final long timeOfAnimation; // Час анімації клітинки
    private final long timeOfDelaying; // Час затримки клітинки
    private long runtimeOfAnimation; // Час виконання анімації клітинки
    public final int[] additions;

    public CellAnimation(int x, int y, int typeOfAnimation, long timeOfAnimation, long timeOfDelaying, int[] additions){
        super(x,y);
        this.typeOfAnimation = typeOfAnimation;
        this.timeOfAnimation = timeOfAnimation;
        this.timeOfDelaying = timeOfDelaying;
        this.additions = additions;
    }

    public int getTypeOfAnimation() {return typeOfAnimation;}
    // Підрахунок часу виконання
    public void tick(long animationRuntime){this.runtimeOfAnimation += animationRuntime;}
    // Перевірка на завершення процесу анімації
    public boolean isAnimationDone() {return timeOfAnimation + timeOfDelaying < runtimeOfAnimation;}
    // Виконання процесу анімації у процентах
    public double getPercentageDone() {return Math.max(0, 1.0 * (runtimeOfAnimation - timeOfDelaying) / timeOfAnimation);}
    // Перевірка на активність процесу анімації
    public boolean isAnimationActive() {return (runtimeOfAnimation >= timeOfDelaying);}

}
