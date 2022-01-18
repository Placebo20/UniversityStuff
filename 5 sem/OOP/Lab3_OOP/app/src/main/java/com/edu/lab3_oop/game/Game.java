package com.edu.lab3_oop.game;
import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

import com.edu.lab3_oop.cell.Cell;
import com.edu.lab3_oop.cell.Floor;
import com.edu.lab3_oop.cell.Grid;
import com.edu.lab3_oop.cell.GridAnimation;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Game {

    // Змінні статусу
    int gameState = GAME_ACTIVE;
    int lastGameState = GAME_ACTIVE;
    private int stateBuff = GAME_ACTIVE;

    // Параметри сітки гри
    public final int gridWidthInSquares = 4;
    public final int gridHeightInSquares = 4;

    // Активні змінні
    private final Context gameContext;
    private final GameView gameView;
    public Grid gameGrid = null;
    public GridAnimation gameGridAnim;

    // Локальні змінні
    boolean isUndoAvailable;
    public long currentScore = 0;
    public long currentHighScore = 0;
    long lastScore = 0;
    private long scoreBuff = 0;

    // Змінні типу анімації
    static final int FADE_GLOBAL_ANIM_TYPE = 0;
    static final int MOVING_ANIM_TYPE = 0;
    static final int MERGING_ANIM_TYPE = 1;
    static final int CREATING_ANIM_TYPE = -1;

    private static final long MOVING_ANIM_TIME = GameView.BASE_ANIM_TIME;
    private static final long SPAWN_ANIM_TIME = GameView.BASE_ANIM_TIME;
    private static final long NOTIFY_ANIM_TIME = GameView.BASE_ANIM_TIME * 5;
    private static final long NOTIFYING_DELAY_TIME = MOVING_ANIM_TIME + SPAWN_ANIM_TIME;

    // Значення, яке гравцю потрібно досягнути
    private static final int GAME_START_MAX_VALUE = 2048;
    private static int GAME_END_MAX_VALUE;

    // Статус гри
    private static final int GAME_WON = 1; //Виграш = active + 1
    private static final int GAME_LOST = -1; //Непарне значення = гра не активна
    private static final int GAME_ACTIVE = 0; //Парне значення = гра активна
    private static final int ENDLESS_GAME = 2;
    private static final int ENDLESS_GAME_WON = 3;

    Game(Context context, GameView view) {
        gameContext = context;
        gameView = view;
        GAME_END_MAX_VALUE = (int) Math.pow(2, view.numCellTypes - 1);
    }

    // Функція створює нову гру
    public void newGame() {
        if (gameGrid == null) {
            gameGrid = new Grid(gridWidthInSquares, gridHeightInSquares);
        } else {
            preparePreviousGrid();
            saveUndoData();
            gameGrid.clearGrid();
        }
        gameGridAnim = new GridAnimation(gridWidthInSquares, gridHeightInSquares);
        currentHighScore = getHighScore();

        if (currentScore >= currentHighScore) {
            currentHighScore = currentScore;
            recordHighScore();
        }

        currentScore = 0;
        gameState = GAME_ACTIVE;
        addStartFloors();
        gameView.showHelp = initializingRun();

        gameView.refreshLastTime = true;
        gameView.resynchronizeTime();
        gameView.invalidate();
    }

    // Зберігаємо попередні дані аби зробити крок назад, якщо буде потрібно
    private void preparePreviousGrid() {
        gameGrid.prepareSaveFloors();
        scoreBuff = currentScore;
        stateBuff = gameState;
    }

    // Зберігаємо попередні дані аби зробити крок назад, якщо буде потрібно
    private void saveUndoData() {
        gameGrid.saveFloors();
        isUndoAvailable = true;
        lastScore = scoreBuff;
        lastGameState = stateBuff;
    }

    // Функція яка повертає рекордне значення
    private long getHighScore() {
        SharedPreferences options = PreferenceManager.getDefaultSharedPreferences(gameContext);
        return options.getLong("HIGH SCORE", -1);
    }

    // Функція яка зберегіає рекордне значення
    private void recordHighScore() {
        SharedPreferences options = PreferenceManager.getDefaultSharedPreferences(gameContext);
        SharedPreferences.Editor editor = options.edit();
        editor.putLong("HIGH SCORE", currentHighScore);
        editor.apply();
    }

    // Додаємо стартові комірки
    private void addStartFloors() {
        int startFloors = 2;
        for (int i = 0; i < startFloors; i++) {
            this.addRandomFloor();
        }
    }

    // Випадково розташовуємо ці комірки
    private void addRandomFloor() {
        if (gameGrid.isCellsAvailable()) {
            int val = Math.random() < 0.9 ? 2 : 4;
            Floor floor = new Floor(gameGrid.randomAvailableCell(), val);

            spawnFloor(floor);
        }
    }

    // Функція породжує нову комірку
    private void spawnFloor(Floor floor) {
        gameGrid.insertFloors(floor);
        gameGridAnim.animationStart(floor.getX(), floor.getY(), CREATING_ANIM_TYPE, SPAWN_ANIM_TIME, MOVING_ANIM_TIME, null);
    }

    // Перший запуск гри
    private boolean initializingRun() {
        SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(gameContext);

        if (settings.getBoolean("INITIALIZING RUN", true)) {
            SharedPreferences.Editor edit = settings.edit();
            edit.putBoolean("INITIALIZING RUN", false);
            edit.apply();
            return true;
        }
        return false;
    }

    // Підготовка комірок
    private void prepareFloors() {
        for (Floor[] arr : gameGrid.field) {
            for (Floor floor : arr) {
                if (gameGrid.isCellOccupied(floor)) {
                    floor.setMergingHistory(null);
                }
            }
        }
    }

    // Функція яка визначає переміщення комірок
    private void moveFloor(Floor floor, Cell cell) {
        gameGrid.field[floor.getX()][floor.getY()] = null;
        gameGrid.field[cell.getX()][cell.getY()] = floor;

        floor.newPosition(cell);
    }

    // Робимо крок назад
    void returnPreviousGrid() {
        if (isUndoAvailable) {
            isUndoAvailable = false;
            gameGridAnim.cancelAnimations();
            gameGrid.revertFloors();
            currentScore = lastScore;
            gameState = lastGameState;
            gameView.refreshLastTime = true;
            gameView.invalidate();
        }
    }

    // Функція пояснююча переміщення клітинок
    void move(int direction) {
        gameGridAnim.cancelAnimations();
        if (!isGameActive()) return;

        preparePreviousGrid();
        Cell vector = getVector(direction);
        List<Integer> detoursX = buildDetoursX(vector);
        List<Integer> detoursY = buildDetoursY(vector);
        boolean isMove = false;

        prepareFloors();

        for (int xn : detoursX) {
            for (int yn : detoursY) {
                Cell currentCell = new Cell(xn, yn);
                Floor currentFloor = gameGrid.getCellContent(currentCell);

                if (currentFloor != null) {
                    Cell[] farthestEmptyCells = farthestEmtyCell(currentCell, vector);
                    Floor floorProbablyToMerge = gameGrid.getCellContent(farthestEmptyCells[1]);

                    // Перевірка на можливість злиття двух комірок
                    if (floorProbablyToMerge != null
                            && floorProbablyToMerge.getFloorVal() == currentFloor.getFloorVal()
                            && floorProbablyToMerge.getMergingHistory() == null) {
                        Floor mergedFloor = new Floor(farthestEmptyCells[1], currentFloor.getFloorVal() * 2);
                        Floor[] temporary = {currentFloor, floorProbablyToMerge};
                        mergedFloor.setMergingHistory(temporary);

                        gameGrid.insertFloors(mergedFloor);
                        gameGrid.removeFloors(currentFloor);

                        // Зливаємо позиції двух комірок
                        currentFloor.newPosition(farthestEmptyCells[1]);

                        int[] additions = {xn, yn};
                        gameGridAnim.animationStart(mergedFloor.getX(), mergedFloor.getY(), MOVING_ANIM_TYPE, MOVING_ANIM_TIME, 0, additions);
                        gameGridAnim.animationStart(mergedFloor.getX(), mergedFloor.getY(), MERGING_ANIM_TYPE, SPAWN_ANIM_TIME, MOVING_ANIM_TIME, null);

                        // Оновлюємо рахунок
                        currentScore = currentScore + mergedFloor.getFloorVal();
                        currentHighScore = Math.max(currentScore, currentHighScore);
                        if (currentScore >= currentHighScore) {
                            currentHighScore = currentScore;
                            recordHighScore();
                        }

                        // Якщо гравець набрав 2048
                        if (mergedFloor.getFloorVal() >= winVal() && !gameWon()) {
                            gameState = gameState + GAME_WON;
                            endGame();
                        }
                    } else {
                        moveFloor(currentFloor, farthestEmptyCells[0]);
                        int[] additions = {xn, yn, 0};
                        gameGridAnim.animationStart(farthestEmptyCells[0].getX(), farthestEmptyCells[0].getY(), MOVING_ANIM_TYPE, MOVING_ANIM_TIME, 0, additions); //Direction: 1 = MOVING NO MERGE
                    }

                    if (!positionsEqual(currentCell, currentFloor)) isMove = true;

                }
            }
        }

        if (isMove) {
            saveUndoData();
            addRandomFloor();
            endGameIfLose();
        }
        gameView.resynchronizeTime();
        gameView.invalidate();
    }

    // Завершення гри у випадку програшу
    private void endGameIfLose() {
        if (!movesAvailable() && !gameWon()) {
            gameState = GAME_LOST;
            endGame();
        }
    }

    // Завершення гри
    private void endGame() {
        gameGridAnim.animationStart(-1, -1, FADE_GLOBAL_ANIM_TYPE, NOTIFY_ANIM_TIME, NOTIFYING_DELAY_TIME, null);
        if (currentScore >= currentHighScore) {
            currentHighScore = currentScore;
            recordHighScore();
        }
    }

    // Повертає можливі напрями руху
    private Cell getVector(int dir) {
        Cell[] cellDirections = {
                new Cell(0, -1), // Вгору
                new Cell(1, 0),  // Вправо
                new Cell(0, 1),  // Вниз
                new Cell(-1, 0)  // Вліво
        };
        return cellDirections[dir];
    }

    // Повертає список клітинок які потрібно буде обійти для руху клітинки
    private List<Integer> buildDetoursX(Cell vector) {
        List<Integer> detours = new ArrayList<>();

        for (int i = 0; i < gridWidthInSquares; i++) detours.add(i);
        if (vector.getX() == 1) Collections.reverse(detours);

        return detours;
    }

    // Повертає список клітинок які потрібно буде обійти для руху клітинки
    private List<Integer> buildDetoursY(Cell vector) {
        List<Integer> detours = new ArrayList<>();

        for (int i = 0; i < gridHeightInSquares; i++) detours.add(i);
        if (vector.getY() == 1) Collections.reverse(detours);

        return detours;
    }

    // Повертає масив клітинок, де 0 елемент є найдальшим елементом
    private Cell[] farthestEmtyCell(Cell currentCell, Cell directionVector) {
        Cell previousCell;
        Cell nextCell = new Cell(currentCell.getX(), currentCell.getY());
        do {
            previousCell = nextCell;
            nextCell = new Cell(previousCell.getX() + directionVector.getX(), previousCell.getY() + directionVector.getY());
        } while (gameGrid.isCellWithinBounds(nextCell) && gameGrid.isCellAvailable(nextCell));

        return new Cell[]{previousCell, nextCell};
    }

    // Функція перевіряє чи є клітинки які можуть злитися
    private boolean floorMatchesAvailable() {
        Floor floorThatChecks;

        for (int i = 0; i < gridWidthInSquares; i++) {
            for (int j = 0; j < gridHeightInSquares; j++) {
                floorThatChecks = gameGrid.getCellContent(new Cell(i, j));

                if (floorThatChecks != null) {
                    for (int direction = 0; direction < 4; direction++) {
                        Cell directionVector = getVector(direction);
                        Cell cellOnTheWay = new Cell(i + directionVector.getX(), j + directionVector.getY());

                        Floor otherFloor = gameGrid.getCellContent(cellOnTheWay);

                        if (otherFloor != null && otherFloor.getFloorVal() == floorThatChecks.getFloorVal()) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    private int winVal() {
        if (!canContinue()) return GAME_END_MAX_VALUE;
         else return GAME_START_MAX_VALUE;

    }

    void setEndlessMode() {
        gameState = ENDLESS_GAME;
        gameView.invalidate();
        gameView.refreshLastTime = true;
    }

    // Функція перевіряє чи можливий рух в якусь зі сторін
    private boolean movesAvailable() { return gameGrid.isCellsAvailable() || floorMatchesAvailable(); }
    // Функція порівнює позиції
    private boolean positionsEqual(Cell firstCell, Cell secondCell) { return firstCell.getX() == secondCell.getX() && firstCell.getY() == secondCell.getY(); }
    // Функція перевіряє чи може гра бути продовжена
    public boolean canContinue() { return !(gameState == ENDLESS_GAME || gameState == ENDLESS_GAME_WON); }
    // Перевірка прогресу гри
    boolean gameWon() { return (gameState > 0 && gameState % 2 != 0); }
    // Перевірка прогресу гри
    boolean gameLost() { return (gameState == GAME_LOST); }
    // Перевірка прогресу гри
    public boolean isGameActive() { return !(gameWon() || gameLost()); }
}
