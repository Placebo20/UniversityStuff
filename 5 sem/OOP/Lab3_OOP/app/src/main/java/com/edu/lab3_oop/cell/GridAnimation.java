package com.edu.lab3_oop.cell;

import java.util.ArrayList;

public class GridAnimation {

    private int activeAnimations = 0;
    private boolean oneMoreFrame = false;
    public final ArrayList<CellAnimation> globalCellAnim = new ArrayList<>();
    private final ArrayList<CellAnimation>[][] cellAnimField;

    public GridAnimation(int x, int y){
        cellAnimField = new ArrayList[x][y];
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++)
                cellAnimField[i][j] = new ArrayList<>();
    }

    // Функція розпочинає анімації
    public void animationStart(int x, int y, int animationType, long animationTime, long delayTime, int[] additions){
        CellAnimation animationToAdd = new CellAnimation(x,y,animationType, animationTime, delayTime, additions);
        if(x == -1 && y == -1) globalCellAnim.add(animationToAdd);
        else cellAnimField[x][y].add(animationToAdd);
        activeAnimations = activeAnimations + 1;
    }
    // Функція зупиняє анімацію
    private void animationCancel(CellAnimation animation){
        if(animation.getX() == -1 && animation.getY() == -1) globalCellAnim.remove(animation);
        else cellAnimField[animation.getX()][animation.getY()].remove(animation);
    }

    // Перевірка активності анімації
    public boolean isAnimationActive() {
        if(activeAnimations != 0) {
            oneMoreFrame = true;
            return true;
        } else if(oneMoreFrame) {
            oneMoreFrame = false;
            return true;
        } else {return false;}
    }

    // Функція повертає дані про анімацію клітинки
    public ArrayList<CellAnimation> getCellAnimation(int x, int y){ return cellAnimField[x][y]; }
    // Функція зупиняє усі анімації в сітці
    public void cancelAnimations() {
        for(ArrayList<CellAnimation>[] arr : cellAnimField)
            for(ArrayList<CellAnimation> list : arr)
                list.clear();
        globalCellAnim.clear();
        activeAnimations = 0;
    }

    // Функція обчислює повний час виконання анімації
    public void tickAllAnimations(long runtime){
        ArrayList<CellAnimation> cancelledAnimations = new ArrayList<>();

        for(CellAnimation cellAnim : globalCellAnim){
            cellAnim.tick(runtime);
            if(cellAnim.isAnimationDone()){
                cancelledAnimations.add(cellAnim);
                activeAnimations = activeAnimations - 1;
            }
        }
        for(ArrayList<CellAnimation>[] arr : cellAnimField) {
            for(ArrayList<CellAnimation> list : arr){
                for(CellAnimation cellAnim : list){
                    cellAnim.tick(runtime);
                    if(cellAnim.isAnimationDone()){
                        cancelledAnimations.add(cellAnim);
                        activeAnimations--;
                    }
                }
            }
        }
        for(CellAnimation animation : cancelledAnimations)
            animationCancel(animation);
    }
}
