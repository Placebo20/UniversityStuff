package com.edu.lab3_oop.cell;

// Class describing the properties of the cell
public class Cell {
    private int X;
    private int Y;

    public Cell(int x, int y) {
        this.X = x;
        this.Y = y;
    }

    public int getX() {
        return this.X;
    }

    void setX(int x) {
        this.X = x;
    }

    public int getY() {
        return this.Y;
    }

    void setY(int y) {
        this.Y = y;
    }
}