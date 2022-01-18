package com.edu.lab3_oop.game;

import android.content.res.Resources;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.content.Context;
import android.view.View;

import java.util.ArrayList;

import com.edu.lab3_oop.R;
import com.edu.lab3_oop.cell.CellAnimation;
import com.edu.lab3_oop.cell.Floor;

@SuppressWarnings("deprecation")
public class GameView extends View {

    static final int BASE_ANIM_TIME = 100000000;
    private static final String SIMPLE_NAME = GameView.class.getSimpleName();
    private static final float MERGING_ACCELERATION = (float) -0.5;
    private static final float CELL_MOVING_VELOCITY = (1 - MERGING_ACCELERATION) / 4;
    public final int numCellTypes = 21;
    private final BitmapDrawable[] cellBM = new BitmapDrawable[numCellTypes];
    public final Game game;

    // Локальні змінні
    private final Paint paint = new Paint();
    public boolean isSave = false;
    public boolean isContinueButtonEn = false;
    public int startX;
    public int startY;
    public int endX;
    public int endY;

    // Змінні кнопок
    public int iconButtons;
    public int restartButton;
    public int undoButton;
    public int sifeOfIcon;

    // Інші змінні
    boolean refreshLastTime = true;
    boolean showHelp;

    // Змінні часу
    private long lastFPST = System.nanoTime();

    // Змінні розміру тексту
    private float titleTextSize;
    private float bodyTextSize;
    private float headerTextSize;
    private float creatorTextSize;
    private float gameOverTextSize;

    // Макетні змінні
    private int sizeOfCell = 0;
    private float textSize = 0;
    private float cellTextSize = 0;
    private int gridWidth = 0;
    private int textPaddingSize;
    private int iconPaddingSize;

    // Змінні малювання та растрових вспливаючих вікон
    private Bitmap background = null;
    private BitmapDrawable gameIsOverOverlay;
    private BitmapDrawable gameIsWonContinueOverlay;
    private BitmapDrawable gameIsWonFinishOverlay;
    private Drawable bgRect;
    private Drawable luRect;
    private Drawable fadeRectangle;

    // Текстові змінні
    private int allTextVariables;
    private int startTitle;
    private int startBody;
    private int allY;
    private int highScoreTitle;
    private int scoreTitle;

    public GameView(Context context) {
        super(context);
        Resources resources = context.getResources();
        // Loading resources
        game = new Game(context, this);

        // Ініціалізуємо фонові змінні
        bgRect = resources.getDrawable(R.drawable.background_rectangle);
        luRect = resources.getDrawable(R.drawable.light_up_rectangle);
        fadeRectangle = resources.getDrawable(R.drawable.fade_rectangle);

        this.setBackgroundColor(resources.getColor(R.color.background));

        // Під'єднуємо ClearSans шрифт
        Typeface font = Typeface.createFromAsset(resources.getAssets(), "ClearSans-Bold.ttf");
        paint.setTypeface(font);

        // Ініціалізуємо TouchListener(прилад який буде відслідковувати взаємодію з екраном)
        setOnTouchListener(new TouchListener(this));

        //creating new game
        game.newGame();
    }

    @Override
    public void onDraw(Canvas canvas){
        // Робимо фонові елементи непрозорими
        canvas.drawBitmap(background, 0,0,paint);
        drawTextInScore(canvas);

        // Перевірка на активність гри
        if(!game.isGameActive() && !game.gameGridAnim.isAnimationActive()){
            drawRestartButton(canvas);
        }

        // Малюємо клітинки
        drawCells(canvas);

        // Якщо гра закінчилась, малюємо повідомлення про це
        if(!game.isGameActive()){
            drawEndGameOverlay(canvas);
        }
        // Якщо гра не може продовжуватись в звичайному режимі, переходимо до нескінченної гри
        if(!game.canContinue()){
            drawEndlessText(canvas);
        }

        // При активній анімації постійно оновлюємо екран
        if(game.gameGridAnim.isAnimationActive()) {
            invalidate(startX, startY, endX, endY);
            tick();
        // Оновимо один останній раз на кінці гри
        } else if(!game.isGameActive() && refreshLastTime){
            invalidate();
            refreshLastTime = false;
        }
    }

    // Оскільки Android не знає реального розміру при запуску, його потрібно обчислити
    @Override
    protected void onSizeChanged(int width, int height, int oldWidth, int oldHeight) {
        super.onSizeChanged(width, height, oldWidth, oldHeight);
        // Утворюємо растровий макет гри
        getSchema(width, height);
        //Утворюємо растрові клітинки
        newCellsBM();
        //Утворюємо растровий фон
        newBackgroundBM(width, height);
        //Утворюємо растрові повідомлення
        newOverlays();
    }

    // Повертає макет гри
    private void getSchema(int width, int height) {
        sizeOfCell = Math.min(width / (game.gridWidthInSquares + 1), height / (game.gridHeightInSquares + 3));
        gridWidth = sizeOfCell / 7;
        int xMidOnScreen = width / 2;
        int yMidOnScreen = height / 2;
        int boardMidY = yMidOnScreen + sizeOfCell / 2;
        sifeOfIcon = sizeOfCell / 2;

        paint.setTextAlign(Paint.Align.CENTER);
        paint.setTextSize(sizeOfCell);
        textSize = sizeOfCell * sizeOfCell / Math.max(sizeOfCell, paint.measureText("0000"));
        cellTextSize = textSize;
        titleTextSize = textSize / 3;
        bodyTextSize = (int) (textSize / 1.5);
        creatorTextSize = (int) (textSize * 0.5);
        headerTextSize = (int) (textSize * 0.8);
        gameOverTextSize = textSize * 2;
        textPaddingSize = (int) (textSize / 3);
        iconPaddingSize = (int) (textSize / 5);

        //Виміри сітки
        double halfGridWidthInSquares = game.gridWidthInSquares / 2d;
        double halfGridHeightInSquares = game.gridHeightInSquares / 2d;

        startX = (int) (xMidOnScreen - (sizeOfCell + gridWidth) * halfGridWidthInSquares - gridWidth / 2);
        endX = (int) (xMidOnScreen + (sizeOfCell + gridWidth) * halfGridWidthInSquares + gridWidth / 2);
        startY = (int) (boardMidY - (sizeOfCell + gridWidth) * halfGridHeightInSquares - gridWidth / 2);
        endY = (int) (boardMidY + (sizeOfCell + gridWidth) * halfGridHeightInSquares + gridWidth / 2);

        paint.setTextSize(titleTextSize);

        int yTextShift = centreText();

        //Статичні змінні
        allTextVariables = (int) (startY - sizeOfCell * 1.5);
        startTitle = (int) (allTextVariables + textPaddingSize + titleTextSize / 2 - yTextShift);
        startBody = (int) (startTitle + textPaddingSize + titleTextSize / 2 + bodyTextSize / 2);

        highScoreTitle = (int) (paint.measureText(getResources().getString(R.string.highScore)));
        scoreTitle = (int) (paint.measureText(getResources().getString(R.string.score)));
        paint.setTextSize(bodyTextSize);
        yTextShift = centreText();
        allY = (int) (startBody + yTextShift + bodyTextSize / 2 + textPaddingSize);

        iconButtons = (startY + allY) / 2 - sifeOfIcon / 2;
        restartButton = (endX - sifeOfIcon);
        undoButton = restartButton - sifeOfIcon * 3 / 2 - iconPaddingSize;
        resynchronizeTime();
    }

    private void drawBackground(Canvas canvas) {
        toDraw(canvas, bgRect, startX, startY, endX, endY);
    }

    //Вивід сітки гри
    private void drawBGGrid(Canvas canvas) {
        Resources resources = getResources();
        Drawable backgroundCell = resources.getDrawable(R.drawable.cell_rectangle);

        for (int xn = 0; xn < game.gridWidthInSquares; xn++) {
            for (int yn = 0; yn < game.gridHeightInSquares; yn++) {

                int xStart = startX + gridWidth + (sizeOfCell + gridWidth) * xn;
                int xEnd = xStart + sizeOfCell;
                int yStart = startY + gridWidth + (sizeOfCell + gridWidth) * yn;
                int yEnd = yStart + sizeOfCell;

                toDraw(canvas, backgroundCell, xStart, yStart, xEnd, yEnd);
            }
        }
    }

    private void toDraw(Canvas canvas, Drawable draw, int startX, int startY, int endX, int endY) {
        // Малюємо границі
        draw.setBounds(startX, startY, endX, endY);
        draw.draw(canvas);
    }

    // Малюємо клітинки
    private void drawCells(Canvas canvas) {
        paint.setTextSize(textSize);
        paint.setTextAlign(Paint.Align.CENTER);

        // Вивід клітинка за клітинкою
        for (int xn = 0; xn < game.gridWidthInSquares; xn++) {
            for (int yn = 0; yn < game.gridHeightInSquares; yn++) {
                int xStart = startX + gridWidth + (sizeOfCell + gridWidth) * xn;
                int endX = xStart + sizeOfCell;
                int yStart = startY + gridWidth + (sizeOfCell + gridWidth) * yn;
                int yEnd = yStart + sizeOfCell;

                Floor currFloor = game.gameGrid.getCellContent(xn, yn);
                if (currFloor != null) {
                    // Отримуємо значення комірки
                    int value = currFloor.getFloorVal();
                    // Логарифм з основою 2 потрібен для корректного відображення значень клітинок
                    int idx = logarithmBase2(value);

                    //Перевіряємо наявність будь-яких активних анімацій
                    ArrayList<CellAnimation> arrayList = game.gameGridAnim.getCellAnimation(xn, yn);
                    boolean anim = false;
                    for (int i = arrayList.size() - 1; i >= 0; i--) {
                        CellAnimation allCells = arrayList.get(i);
                        //Якщо дана анімація не активна, пропускаємо її
                        if (allCells.getTypeOfAnimation() == Game.CREATING_ANIM_TYPE) {
                            anim = true;
                        }
                        if (!allCells.isAnimationActive()) {
                            continue;
                        }

                        if (allCells.getTypeOfAnimation() == Game.CREATING_ANIM_TYPE) { // Визиваємо анімації
                            paint.setTextSize(textSize * 0.5f);
                            float scaleOfCell = sizeOfCell / 2 * (1 - 0.5f);
                            cellBM[idx].setBounds((int) (xStart + scaleOfCell), (int) (yStart + scaleOfCell), (int) (endX - scaleOfCell), (int) (yEnd - scaleOfCell));
                            cellBM[idx].draw(canvas);

                        } else if (allCells.getTypeOfAnimation() == Game.MERGING_ANIM_TYPE) { // Анімація злиття
                            float textScaleSize = (float) (1 + CELL_MOVING_VELOCITY);
                            paint.setTextSize(textSize * textScaleSize);

                            float cellScaleSize = sizeOfCell / 2 * (1 - textScaleSize);
                            cellBM[idx].setBounds((int) (xStart + cellScaleSize), (int) (yStart + cellScaleSize), (int) (endX - cellScaleSize), (int) (yEnd - cellScaleSize));
                            cellBM[idx].draw(canvas);
                        } else if (allCells.getTypeOfAnimation() == Game.MOVING_ANIM_TYPE) {  // Анімація руху
                            double percentDone = allCells.getPercentageDone();
                            int tmpIdx = idx;
                            if (arrayList.size() >= 2) {
                                tmpIdx = tmpIdx - 1;
                            }
                            int prevCellX = allCells.additions[0];
                            int prevCellY = allCells.additions[1];
                            int currFloorX = currFloor.getX();
                            int currFloorY = currFloor.getY();

                            int dX = (int) ((currFloorX - prevCellX) * (sizeOfCell + gridWidth) * (percentDone - 1) * 1.0);
                            int dY = (int) ((currFloorY - prevCellY) * (sizeOfCell + gridWidth) * (percentDone - 1) * 1.0);

                            cellBM[tmpIdx].setBounds(xStart + dX, yStart + dY, endX + dX, yEnd + dY);
                            cellBM[tmpIdx].draw(canvas);
                        }
                        anim = true;
                    }

                    // При відсутності активних анімацій просто малюємо клітинку

                    if (!anim) {
                        cellBM[idx].setBounds(xStart, yStart, endX, yEnd);
                        cellBM[idx].draw(canvas);
                    }
                }
            }
        }
    }

    private void newBackgroundBM(int width, int height) {
        background = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(background);
        drawHeader(canvas);
        drawRestartButton(canvas);
        drawUndoButton(canvas);
        drawBackground(canvas);
        drawBGGrid(canvas);
        drawNameOfCreator(canvas);

    }

    private void newCellsBM() {
        Resources resources = getResources();
        int[] cellRectangleIds = getCellRectID();
        paint.setTextAlign(Paint.Align.CENTER);
        for (int xn = 1; xn < cellBM.length; xn++) {
            int value = (int) Math.pow(2, xn);
            paint.setTextSize(cellTextSize);
            float tempTextSize = cellTextSize * sizeOfCell * 0.9f / Math.max(sizeOfCell * 0.9f, paint.measureText(String.valueOf(value)));
            paint.setTextSize(tempTextSize);
            Bitmap bitmap = Bitmap.createBitmap(sizeOfCell, sizeOfCell, Bitmap.Config.ARGB_8888);
            Canvas canvas = new Canvas(bitmap);
            toDraw(canvas, resources.getDrawable(cellRectangleIds[xn]), 0, 0, sizeOfCell, sizeOfCell);
            drawTextInCell(canvas, value);
            cellBM[xn] = new BitmapDrawable(resources, bitmap);
        }
    }

    // Присвоюємо значення кольору кожному класу клітинок
    private int[] getCellRectID() {
        int[] cellRectID = new int[numCellTypes];

        cellRectID[0] = R.drawable.cell_rectangle;
        cellRectID[1] = R.drawable.cell_rectangle_2;
        cellRectID[2] = R.drawable.cell_rectangle_4;
        cellRectID[3] = R.drawable.cell_rectangle_8;
        cellRectID[4] = R.drawable.cell_rectangle_16;
        cellRectID[5] = R.drawable.cell_rectangle_32;
        cellRectID[6] = R.drawable.cell_rectangle_64;
        cellRectID[7] = R.drawable.cell_rectangle_128;
        cellRectID[8] = R.drawable.cell_rectangle_256;
        cellRectID[9] = R.drawable.cell_rectangle_512;
        cellRectID[10] = R.drawable.cell_rectangle_1024;
        cellRectID[11] = R.drawable.cell_rectangle_2048;

        for (int xn = 12; xn < cellRectID.length; xn++) {
            cellRectID[xn] = R.drawable.cell_rectangle_4096;
        }

        return cellRectID;
    }

    // Малюємо значення в комірці
    private void drawTextInCell(Canvas canvas, int val) {
        // Змінна відступу
        int shift = centreText();
        // Для того щоб було краще видно значення клітинки, змінюємо колір клітинки
        if(val >= 8){paint.setColor(getResources().getColor(R.color.whiteText));}
        else {paint.setColor(getResources().getColor(R.color.blackText));}

        canvas.drawText("" + val, sizeOfCell / 2, sizeOfCell / 2 - shift, paint);
    }

    // Малюємо значення в рахунку
    private void drawTextInScore(Canvas canvas) {
        // Тут HS - HighScore, S - Score
        paint.setTextSize(bodyTextSize);
        paint.setTextAlign(Paint.Align.CENTER);
        int widthHS = (int) (paint.measureText("" + game.currentHighScore));
        int widthS = (int) (paint.measureText("" + game.currentScore));

        int textWidthHS = Math.max(highScoreTitle, widthHS) + textPaddingSize * 2;
        int textWidthS = Math.max(scoreTitle, widthS) + textPaddingSize * 2;

        int midTextHS = textWidthHS / 2;
        int midTextS = textWidthS / 2;

        int endXHS = endX;
        int startXHS = endXHS - textWidthHS;

        int endXS = startXHS - textPaddingSize;
        int startXS = endXS - textWidthS;

        // Вивід high-score комірки
        bgRect.setBounds(startXHS, allTextVariables, endXHS, allY);
        bgRect.draw(canvas);
        paint.setTextSize(titleTextSize);
        paint.setColor(getResources().getColor(R.color.brownText));
        canvas.drawText(getResources().getString(R.string.highScore), startXHS + midTextHS, startTitle, paint);
        paint.setTextSize(bodyTextSize);
        paint.setColor(getResources().getColor(R.color.whiteText));
        canvas.drawText(String.valueOf(game.currentHighScore), startXHS + midTextHS, startBody, paint);


        // Вивід score комірки
        bgRect.setBounds(startXS, allTextVariables, endXS, allY);
        bgRect.draw(canvas);
        paint.setTextSize(titleTextSize);
        paint.setColor(getResources().getColor(R.color.brownText));
        canvas.drawText(getResources().getString(R.string.score), startXS + midTextS, startTitle, paint);
        paint.setTextSize(bodyTextSize);
        paint.setColor(getResources().getColor(R.color.whiteText));
        canvas.drawText(String.valueOf(game.currentScore), startXS + midTextS, startBody, paint);
    }

    // Малюємо кнопку перезапуску
    private void drawRestartButton(Canvas canvas) {

        toDraw(canvas, bgRect, restartButton, iconButtons, restartButton + sifeOfIcon, iconButtons + sifeOfIcon);

        toDraw(canvas, getResources().getDrawable(R.drawable.ic_action_refresh),
                restartButton + iconPaddingSize,
                iconButtons + iconPaddingSize,
                restartButton + sifeOfIcon - iconPaddingSize,
                iconButtons + sifeOfIcon - iconPaddingSize
        );
    }

    // Малюємо кнопку кроку назад
    private void drawUndoButton(Canvas canvas) {

        toDraw(canvas, bgRect, undoButton, iconButtons, undoButton + sifeOfIcon, iconButtons + sifeOfIcon);

        toDraw(canvas,
                getResources().getDrawable(R.drawable.ic_action_undo),
                undoButton + iconPaddingSize,
                iconButtons + iconPaddingSize,
                undoButton + sifeOfIcon - iconPaddingSize,
                iconButtons + sifeOfIcon - iconPaddingSize
        );
    }

    // Малюємо назву
    private void drawHeader(Canvas canvas) {

        //Drawing the header
        paint.setTextSize(headerTextSize);
        paint.setColor(getResources().getColor(R.color.blackText));
        paint.setTextAlign(Paint.Align.LEFT);
        int textShiftY = centreText() * 2;
        int headerStartY = allTextVariables - textShiftY;
        canvas.drawText("2048 by Hushchadi", startX, headerStartY, paint);
    }

    // Малюємо підпис автора
    private void drawNameOfCreator(Canvas canvas) {

        //Drawing the creator's name
        paint.setTextSize(creatorTextSize);
        paint.setTextAlign(Paint.Align.LEFT);
        int textShiftY = centreText() * 2;
        canvas.drawText(getResources().getString(R.string.creator),
                startX, endY - textShiftY + textPaddingSize, paint);
    }

    // Малюємо напівпрозоре повідомлення
    private void newEndGameState(Canvas canvas, boolean isWon, boolean showBu) {
        int width = endX - startX;
        int length = endY - startY;

        int xMid = width / 2;
        int yMid = length / 2;

        if (isWon) {
            luRect.setAlpha(127);
            toDraw(canvas, luRect, 0, 0, width, length);
            luRect.setAlpha(255);
            paint.setColor(getResources().getColor(R.color.whiteText));
            paint.setAlpha(255);
            paint.setTextSize(gameOverTextSize);
            paint.setTextAlign(Paint.Align.CENTER);
            int textBottom = yMid - centreText();
            canvas.drawText(getResources().getString(R.string.playerWin), xMid, textBottom, paint);
            paint.setTextSize(bodyTextSize);
            String text = showBu ? getResources().getString(R.string.tapToEndlessMode) :
                    getResources().getString(R.string.forNow);
            canvas.drawText(text, xMid, textBottom + textPaddingSize * 2 - centreText() * 2, paint);
        } else {
            fadeRectangle.setAlpha(127);
            toDraw(canvas, fadeRectangle, 0, 0, width, length);
            fadeRectangle.setAlpha(255);
            paint.setColor(getResources().getColor(R.color.blackText));
            paint.setAlpha(255);
            paint.setTextSize(gameOverTextSize);
            paint.setTextAlign(Paint.Align.CENTER);
            canvas.drawText(getResources().getString(R.string.gameIsOver), xMid, yMid - centreText(), paint);
        }
    }

    // Ініціалізація вспливаючих станів
    private void newOverlays() {
        Resources res = getResources();

        Bitmap bm = Bitmap.createBitmap(endX - startX, endY - startY, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bm);
        newEndGameState(canvas, true, true);
        gameIsWonContinueOverlay = new BitmapDrawable(res, bm);

        bm = Bitmap.createBitmap(endX - startX, endY - startY, Bitmap.Config.ARGB_8888);
        canvas = new Canvas(bm);
        newEndGameState(canvas, true, false);
        gameIsWonFinishOverlay = new BitmapDrawable(res, bm);

        bm = Bitmap.createBitmap(endX - startX, endY - startY, Bitmap.Config.ARGB_8888);
        canvas = new Canvas(bm);
        newEndGameState(canvas, false, false);
        gameIsOverOverlay = new BitmapDrawable(res, bm);
    }

    // Малюємо вспливаюче вікно при програші
    private void drawEndGameOverlay(Canvas canvas) {
        double alphaCh = 1;
        isContinueButtonEn = false;
        for (CellAnimation animation : game.gameGridAnim.globalCellAnim) {
            if (animation.getTypeOfAnimation() == Game.FADE_GLOBAL_ANIM_TYPE) {
                alphaCh = animation.getPercentageDone();
            }
        }
        BitmapDrawable exhibitOverlay = null;
        if (game.gameWon()) {
            if (game.canContinue()) {
                isContinueButtonEn = true;
                exhibitOverlay = gameIsWonContinueOverlay;
            } else {
                exhibitOverlay = gameIsWonFinishOverlay;
            }
        } else if (game.gameLost()) {
            exhibitOverlay = gameIsOverOverlay;
        }

        if (exhibitOverlay != null) {
            exhibitOverlay.setBounds(startX, startY, endX, endY);
            exhibitOverlay.setAlpha((int) (255 * alphaCh));
            exhibitOverlay.draw(canvas);
        }
    }

    // Малює надпис нескінченної гри
    private void drawEndlessText(Canvas canvas) {

        paint.setTextAlign(Paint.Align.LEFT);
        paint.setTextSize(bodyTextSize);
        paint.setColor(getResources().getColor(R.color.blackText));
        canvas.drawText(getResources().getString(R.string.endlessMode), startX, iconButtons - centreText() * 2, paint);
    }

    // Контроль часу
    private void tick() {
        long currentTime = System.nanoTime();
        game.gameGridAnim.tickAllAnimations(currentTime - lastFPST);
        lastFPST = currentTime;
    }

    // Контроль часу
    public void resynchronizeTime() {
        lastFPST = System.nanoTime();
    }
    // Центрування тексту
    private int centreText() {
        return (int) ((paint.descent() + paint.ascent()) / 2);
    }
    // Логарифм з основою 2
    private static int logarithmBase2(int n){
        return 31 - Integer.numberOfLeadingZeros(n);
    }

}