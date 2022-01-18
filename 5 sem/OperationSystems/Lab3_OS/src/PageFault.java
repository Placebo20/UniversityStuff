import java.util.*;

public class PageFault {

    private static int clockPointer = 0;

    /* @param mem це вектор, котрий містить у собі симульовані сторінки
    * mem повинен здійснити пошук, щоб знайти потрібну сторінку для видалення та змінити ії аби зазначити будь-які зміни
    * @param virtPageNum це число віртуальних сторінок в симуляторі
    * @param replacePageNum це індекс сторінки котра викликала помилку відсутньої сторінки
    * @param controlPanel змінна котра займається графічним виведенням лабораторної роботи
     */
    public static void replacePage(Vector<Page> mem, int virtPageNum, int replacePageNum, ControlPanel controlPanel){
        int deportedPageNum;

        while(true){
            // Вилучаємо сторінку, на котру вказує стрілка годинника (clockPointer)
            Page page = mem.get(clockPointer);

            // Перевірка на помилку відсутності сторінки (Якщо page.physical == -1 )
            if (page.physical != -1) {
                // Якщо R == 1, то біт R = 0 і стрілка годинника переміщується на наступну сторінку
                if (page.R == 1) {
                    page.R = 0;
                // Якщо R == 0, сторінка виселяється і на її місце в циферблаті встановлюється нова сторінка
                } else {
                    deportedPageNum = clockPointer;
                    break;
                }
            }

            clockPointer++;
            if (clockPointer == virtPageNum) {
                clockPointer = 0;
            }
        }

        Page deportedPage = mem.get(deportedPageNum); // Сторінка котра була виселена
        Page replacingPage = mem.get(replacePageNum); // Сторінка котра була заселена на місце попередньої

        replacingPage.physical = deportedPage.physical;
        deportedPage.inMemTime = 0;
        deportedPage.lastTouchTime = 0;
        deportedPage.R = 0;
        deportedPage.M = 0;
        deportedPage.physical = -1;

        controlPanel.removePhysicalPage(deportedPageNum);
        controlPanel.addPhysicalPage(replacingPage.physical, replacePageNum);
    }
}