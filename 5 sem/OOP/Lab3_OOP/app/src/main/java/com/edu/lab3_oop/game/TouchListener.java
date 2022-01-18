package com.edu.lab3_oop.game;

import android.view.View;
import android.view.MotionEvent; // Для відстеження взаємодій з екраном

public class TouchListener implements View.OnTouchListener {

    private final GameView gameView;

    // Локальні змінні
    private float X;
    private float Y;
    private float deltaX;
    private float deltaY;
    private float xStart;
    private float yStart;
    private float xPrevious;
    private float yPrevious;
    private int previousDirect = 1;
    private int lastDirection = 1;

    // Змінні перевірки
    private boolean isMoved = false;
    private boolean isIconTappedFirst = false;

    // Фіксовані обмежувальні змінні руху
    private static final int THRESHOLD_OF_SWIPE = 25;
    private static final int THRESHOLD_OF_MOVE = 250;
    private static final int MINIMAL_DISTANCE_OF_SWIPE = 0;
    private static final int RESTART = 10;

    public TouchListener(GameView view){
        super();
        this.gameView = view;
    }

    public boolean onTouch(View view, MotionEvent event) {
        switch (event.getAction()) {

            case MotionEvent.ACTION_MOVE:
                X = event.getX();
                Y = event.getY();

                if (gameView.game.isGameActive() && !isIconTappedFirst) {
                    float xDelta = X - xPrevious;
                    if (Math.abs(this.deltaX + xDelta) < Math.abs(this.deltaX) + Math.abs(xDelta) && Math.abs(xDelta) > RESTART
                            && Math.abs(X - xStart) > MINIMAL_DISTANCE_OF_SWIPE) {
                        xStart = X;
                        yStart = Y;
                        this.deltaX = xDelta;
                        previousDirect = lastDirection;
                    }

                    if (this.deltaX == 0) {
                        this.deltaX = xDelta;
                    }

                    float yDelta = Y - yPrevious;
                    if (Math.abs(this.deltaY + yDelta) < Math.abs(this.deltaY) + Math.abs(yDelta) && Math.abs(yDelta) > RESTART
                            && Math.abs(Y - yStart) > MINIMAL_DISTANCE_OF_SWIPE) {
                        xStart = X;
                        yStart = Y;
                        this.deltaY = yDelta;
                        previousDirect = lastDirection;
                    }
                    if (this.deltaY == 0) {
                        this.deltaY = yDelta;
                    }
                    if (pathChanged() > MINIMAL_DISTANCE_OF_SWIPE * MINIMAL_DISTANCE_OF_SWIPE && !isMoved) {
                        boolean moved = false;

                        // Vertical interaction
                        if (((yDelta >= THRESHOLD_OF_SWIPE && Math.abs(yDelta) >= Math.abs(xDelta)) || Y - yStart >= THRESHOLD_OF_MOVE)
                                && previousDirect % 2 != 0) {
                            moved = true;
                            previousDirect = previousDirect * 2;
                            lastDirection = 2;
                            gameView.game.move(2);
                        }
                        else if (((yDelta <= -THRESHOLD_OF_SWIPE && Math.abs(yDelta) >= Math.abs(xDelta)) || Y - yStart <= -THRESHOLD_OF_MOVE)
                                && previousDirect % 3 != 0) {
                            moved = true;
                            previousDirect = previousDirect * 3;
                            lastDirection = 3;
                            gameView.game.move(0);
                        }

                        // Horizontal interaction
                        if (((xDelta >= THRESHOLD_OF_SWIPE && Math.abs(xDelta) >= Math.abs(yDelta)) || X - xStart >= THRESHOLD_OF_MOVE)
                                && previousDirect % 5 != 0) {
                            moved = true;
                            previousDirect = previousDirect * 5;
                            lastDirection = 5;
                            gameView.game.move(1);
                        } else if (((xDelta <= -THRESHOLD_OF_SWIPE && Math.abs(xDelta) >= Math.abs(yDelta)) || X - xStart <= -THRESHOLD_OF_MOVE)
                                && previousDirect % 7 != 0) {
                            moved = true;
                            previousDirect = previousDirect * 7;
                            lastDirection = 7;
                            gameView.game.move(3);
                        }
                        if (moved) {
                            isMoved = true;
                            xStart = X;
                            yStart = Y;
                        }
                    }
                }

                xPrevious = X;
                yPrevious = Y;
                return true;

            case MotionEvent.ACTION_UP:
                X = event.getX();
                Y = event.getY();
                previousDirect = 1;
                lastDirection = 1;

                if (!isMoved) {
                    if (isIconPressed(gameView.restartButton, gameView.iconButtons)) {
                        gameView.game.newGame();
                    } else if (isIconPressed(gameView.undoButton, gameView.iconButtons)) {
                        gameView.game.returnPreviousGrid();
                    } else if (isScreenTapped(2) && isInRange(gameView.startX, X, gameView.endX)
                            && isInRange(gameView.startY, X, gameView.endY) && gameView.isContinueButtonEn) {
                        gameView.game.setEndlessMode();
                    }
                }

            case MotionEvent.ACTION_DOWN:
                X = event.getX();
                Y = event.getY();

                xStart = X;
                yStart = Y;
                xPrevious = X;
                yPrevious = Y;

                deltaX = 0;
                deltaY = 0;

                isMoved = false;
                isIconTappedFirst = isIconPressed(gameView.restartButton, gameView.iconButtons) || isIconPressed(gameView.undoButton, gameView.iconButtons);
                return true;
        }
        return true;
    }

    private float pathChanged() {
        return (X - xStart) * (X - xStart) + (Y - yStart) * (Y - yStart);
    }

    private boolean isIconPressed(int x, int y) {
        return isScreenTapped(1) && isInRange(x, X, x + gameView.sifeOfIcon)
                && isInRange(y, Y, y + gameView.sifeOfIcon);
    }

    private boolean isInRange(float starting, float check, float ending) {
        return (starting <= check && check <= ending);
    }

    private boolean isScreenTapped(int factor) {
        return pathChanged() <= gameView.sifeOfIcon * gameView.sifeOfIcon * factor;
    }

}
