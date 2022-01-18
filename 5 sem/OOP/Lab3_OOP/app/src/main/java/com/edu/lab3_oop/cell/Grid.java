package com.edu.lab3_oop.cell;

import java.util.ArrayList;

// Class describing the properties and behavior of the game grid
public class Grid {

    public final Floor[][] field; // Current grid
    public final Floor[][] undoField; // Previous grid
    private final Floor[][] bufferField; // Buffer grid (Use for saving floors)

    public Grid(int sizeX, int sizeY){
        field = new Floor[sizeX][sizeY];
        undoField = new Floor[sizeX][sizeY];
        bufferField = new Floor[sizeX][sizeY];
        clearGrid();
        clearUndoGrid();
    }

    // Returns a random empty cell to fill
    public Cell randomAvailableCell() {
        ArrayList<Cell> availableCells = getAvailableCells();
        if(availableCells.size() >= 1){
            return availableCells.get((int) Math.floor(Math.random() * availableCells.size()));
        }
        return null;
    }

    // Returns a random empty cell array
    private ArrayList<Cell> getAvailableCells() {
        ArrayList<Cell> availableCells = new ArrayList<>();
        for(int xn = 0; xn < field.length; xn++){
            for(int yn = 0; yn < field[0].length; yn++){
                if(field[xn][yn] == null) {
                    availableCells.add(new Cell(xn, yn));
                }
            }
        }
        return availableCells;
    }

    // Checking for empty cells
    public boolean isCellsAvailable() {
        return (getAvailableCells().size() >= 1);
    }

    // Checking for the emptiness of a specific cell
    public boolean isCellAvailable(Cell cell) {
        return !isCellOccupied(cell);
    }

    // Checking for the fullness of a specific cell
    public boolean isCellOccupied(Cell cell) {
        return (getCellContent(cell) != null);
    }

    // Returns cell data
    public Floor getCellContent(Cell cell) {
        if(cell != null && isCellWithinBounds(cell)) {
            return field[cell.getX()][cell.getY()];
        } else {return null;}
    }

    // Returns cell data
    public Floor getCellContent(int x, int y) {
        if(isCellWithinBounds(x, y)) {
            return field[x][y];
        } else {return null;}
    }

    // Checking for the presence of borders at the cell
    public boolean isCellWithinBounds(Cell cell) {
        return 0 <= cell.getX() && cell.getX() < field.length
                && 0 <= cell.getY() && cell.getY() < field[0].length;
    }

    // Checking for the presence of borders at the cell
    private boolean isCellWithinBounds(int x, int y) {
        return 0 <= x && x < field.length && 0 <= y && y < field[0].length;
    }

    // Floor insertion function
    public void insertFloors(Floor floor){
        field[floor.getX()][floor.getY()] = floor;
    }

    // Floor removing function
    public void removeFloors(Floor floor) {
        field[floor.getX()][floor.getY()] = null;
    }

    // Floor saving function
    public void saveFloors() {
        for(int xn = 0; xn < bufferField.length; xn++){
            for(int yn = 0; yn < bufferField[0].length; yn++){
                if(bufferField[xn][yn] == null)
                    undoField[xn][yn] = null;
                else
                    undoField[xn][yn] = new Floor(xn, yn, bufferField[xn][yn].getFloorVal());
            }
        }
    }

    // Saving current field (For revert to previous field)
    public void prepareSaveFloors(){
        for(int xn = 0; xn < field.length; xn++){
            for(int yn = 0; yn < field[0].length; yn++){
                if(field[xn][yn] == null)
                    bufferField[xn][yn] = null;
                else
                    bufferField[xn][yn] = new Floor(xn, yn, field[xn][yn].getFloorVal());
            }
        }
    }

    // Revert to previous grid
    public void revertFloors() {
        for(int xn = 0; xn < undoField.length; xn++){
            for(int yn = 0; yn < undoField[0].length; yn++){
                if(undoField[xn][yn] == null)
                    field[xn][yn] = null;
                else
                    field[xn][yn] = new Floor(xn, yn, undoField[xn][yn].getFloorVal());
            }
        }
    }

    // Cleaning the current grid
    public void clearGrid(){
        for(int xn = 0; xn < field.length; xn++) {
            for(int yn = 0; yn < field.length; yn++) {
                field[xn][yn] = null;
            }
        }
    }

    // Clearing the previous grid
    public void clearUndoGrid() {
        for(int xn = 0; xn < field.length; xn++) {
            for(int yn = 0; yn < field.length; yn++) {
                undoField[xn][yn] = null;
            }
        }
    }
}
