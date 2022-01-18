package com.edu.lab3_oop.cell;

public class Floor extends Cell{

    private final int floorVal;
    private Floor[] mergingHistory = null;

    public Floor(int x, int y, int floorVal){
        super(x,y);
        this.floorVal = floorVal;
    }

    public Floor(Cell cell, int floorVal) {
        super(cell.getX(), cell.getY());
        this.floorVal = floorVal;
    }

    public void newPosition(Cell cell) {
        this.setX(cell.getX());
        this.setY(cell.getY());
    }

    public int getFloorVal() {return this.floorVal;}
    public Floor[] getMergingHistory() {return mergingHistory;}
    public void setMergingHistory(Floor[] floor){ mergingHistory = floor;}

}
