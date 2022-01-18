package com.edu.lab3_oop.game;

import android.content.SharedPreferences;           // Ініціалізуємо сховище опцій гри за допомогою SharedPreferces
import android.os.Bundle;                           // Потрібен для тимчасового зберігання даних
import android.preference.PreferenceManager;
import androidx.appcompat.app.AppCompatActivity;

import com.edu.lab3_oop.cell.Floor;

public class GameActivity extends AppCompatActivity {

    private GameView gameView;

    // Опція відповідальна за збереженя прогресу
    private void save() {
        SharedPreferences options = PreferenceManager.getDefaultSharedPreferences(this);
        SharedPreferences.Editor edit = options.edit();

        Floor[][] floors = gameView.game.gameGrid.field;
        Floor[][] undoFloors = gameView.game.gameGrid.undoField;

        edit.putBoolean("CAN UNDO", gameView.game.isUndoAvailable);
        edit.putInt("GAME STATE", gameView.game.gameState);
        edit.putInt("UNDO GAME STATE", gameView.game.lastGameState);
        edit.putInt("WIDTH", floors.length);
        edit.putInt("HEIGHT", floors.length);
        edit.putLong("SCORE", gameView.game.currentScore);
        edit.putLong("HIGH SCORE", gameView.game.currentHighScore);
        edit.putLong("UNDO SCORE", gameView.game.lastScore);

        for (int xn = 0; xn < floors.length; xn++) {
            for (int yn = 0; yn < floors[0].length; yn++) {

                if (floors[xn][yn] != null) {
                    edit.putInt(xn + " " + yn, floors[xn][yn].getFloorVal());
                } else {
                    edit.putInt(xn + " " + yn, 0);
                }

                if (undoFloors[xn][yn] != null) {
                    edit.putInt("UNDO GRID" + xn + " " + yn, undoFloors[xn][yn].getFloorVal());
                } else {
                    edit.putInt("UNDO GRID" + xn + " " + yn, 0);
                }
            }
        }

        edit.apply();
    }

    // Опція відповідальна за вигрузку попереднього прогресу
    private void load() {
        // Остановка всех анимаций
        gameView.game.gameGridAnim.cancelAnimations();

        SharedPreferences options = PreferenceManager.getDefaultSharedPreferences(this);

        gameView.game.isUndoAvailable = options.getBoolean("CAN UNDO", gameView.game.isUndoAvailable);
        gameView.game.currentScore = options.getLong("SCORE", gameView.game.currentScore);
        gameView.game.currentHighScore = options.getLong("HIGH SCORE", gameView.game.currentHighScore);
        gameView.game.lastScore = options.getLong("UNDO SCORE", gameView.game.lastScore);
        gameView.game.gameState = options.getInt("GAME STATE", gameView.game.gameState);
        gameView.game.lastGameState = options.getInt("UNDO GAME STATE", gameView.game.lastGameState);

        for (int xn = 0; xn < gameView.game.gameGrid.field.length; xn++) {
            for (int yn = 0; yn < gameView.game.gameGrid.field[0].length; yn++) {
                int val = options.getInt(xn + " " + yn, -1);
                if (val > 0) {
                    gameView.game.gameGrid.field[xn][yn] = new Floor(xn, yn, val);
                } else if (val == 0) {
                    gameView.game.gameGrid.field[xn][yn] = null;
                }

                int undoVal = options.getInt("UNDO GRID" + xn + " " + yn, -1);
                if (undoVal > 0) {
                    gameView.game.gameGrid.undoField[xn][yn] = new Floor(xn, yn, undoVal);
                } else if (val == 0) {
                    gameView.game.gameGrid.undoField[xn][yn] = null;
                }
            }
        }
    }

    @Override
    protected void onCreate(Bundle stateOfSavedInstance) {
        super.onCreate(stateOfSavedInstance);
        gameView = new GameView(this);

        SharedPreferences options = PreferenceManager.getDefaultSharedPreferences(this);
        gameView.isSave = options.getBoolean("SAVE STATE", false);

        if (stateOfSavedInstance != null)
            if (stateOfSavedInstance.getBoolean("HAS STATE"))
                load();

        setContentView(gameView);
    }

    @Override
    public void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putBoolean("HAS STATE", true);
        save();
    }

    protected void onResume() {
        super.onResume();
        load();
    }

    protected void onPause() {
        super.onPause();
        save();
    }
}