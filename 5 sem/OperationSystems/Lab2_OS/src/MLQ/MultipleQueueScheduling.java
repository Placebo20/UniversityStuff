package MLQ;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;

import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.DataFormatter;
import org.apache.poi.ss.usermodel.Row;

public class MultipleQueueScheduling {

    int[] priority = new int[500];              // Пріоритет
    int[] burstTime = new int[500];             // Час витрачений на виконання центральним процесором процесу
    int[] completionTime = new int[500];        // Час виконання процесу
    int[] waitingTime = new int[500];           // Час очікування
    int[] turnaroundTime = new int[500];        // Час обертання (CompletionTime - ArrivalTime)

    static int n;                               // Кількість процесів
    static int timeQuantum = 4;                 // Квант часу
    static int arrivalTime = 0;                 // Час, коли процес поступає в стан готовності
    static int[] p = new int[500];              // Масив номерів процесів
    static float totalWaitingTime;              // Час витрачений на очікування усіх процесів
    static float totalTurnaroundTime;           // Час витрачений на обертання усіх процесів

    public static void main(String[] args) throws IOException {
        long startTime = System.currentTimeMillis();
        MultipleQueueScheduling multipleQueueScheduling = new MultipleQueueScheduling();
        Object[] returnArrayOfObjects = multipleQueueScheduling.excelReader("D:\\PROJECTS\\University-VSem\\OperationSystems\\Lab2_OS\\InputData.xls");
        @SuppressWarnings("unused")
        int[] burstTime = (int[])returnArrayOfObjects[0];
        @SuppressWarnings("unused")
        int[] priority = (int[])returnArrayOfObjects[1];
        multipleQueueScheduling.multipleQueueScheduling();
        long finishTime = System.currentTimeMillis();
        long totalTime = finishTime - startTime;
        System.out.println("Total time taken for execution of the code is " + totalTime + " millisec.");
    }

    public void multipleQueueScheduling() {
        // Розподіляємо процеси по пріорітетності
        ArrayList<Integer> highPriorityProcessList = new ArrayList<Integer>();
        ArrayList<Integer> lowPriorityProcessList = new ArrayList<Integer>();
        int z = 0;

        //Виконання черги з високим пріоритетом за алгоритмом планування FCFS
        for (int i = 0; i < n; i++){
            p[i] = i;                                               // Ітеративний процес для виводу (0, 1, 2, ...)
            if(priority[i] == 1) {
                highPriorityProcessList.add(priority[i]);
                completionTime[i] = completionTime[z] + burstTime[i];
                z = i;
                turnaroundTime[i] = completionTime[i] - arrivalTime;
                waitingTime[i] = turnaroundTime[i] - burstTime[i];
            }
        }

        //Виконання черги з низьким пріоритетом за алгоритмом планування Round-Robin
        for(int i = 0; i < n; i++){
            if(priority[i] == 0)
                lowPriorityProcessList.add(i); // lowPriorityProcessList містить у собі всі низькопріоритетні процеси (як p2, p3, p4)
        }

        int[] lowPriorityProcessArray = new int[50];
        // Копіювання процесів з lowPriorityProcessList в lowPriorityProcessArray
        for (int i = 0; i < lowPriorityProcessList.size(); i++)
            lowPriorityProcessArray[i] = lowPriorityProcessList.get(i);

        //Копіюємо час потрібний для виконання програм заради зберігання часу який залишився на виконання програм
        int[] remainingBurstTime = new int[lowPriorityProcessList.size()];
        for(int i = 0; i < lowPriorityProcessList.size(); i++)
            remainingBurstTime[i] = burstTime[lowPriorityProcessArray[i]]; //BurstTime низькопріоритетних процесів скопійовано в remainingBurstTime

        int completionTimeZ = completionTime[z];

        //Продовжуємо обхід усіх процесів циклічно, поки усі вони не будуть виконані
        while(true){
            boolean isDone = true;

            //Проходимо по усім процесам один за одним декілька разів
            for(int i = 0; i < lowPriorityProcessList.size(); i++) {

                //Якщо час виконання процесу на ЦП більше ніж 0, то потрібно продовжувати обробку
                if (remainingBurstTime[i] > 0) {

                    isDone = false; // Існує незавершений процес

                    if (remainingBurstTime[i] > timeQuantum) {

                        // Збільшення значення t, це показує скільки часу процес оброблюється
                        completionTimeZ += timeQuantum;

                        //Зменшуємо час виконання даного процесу на ЦП на квант часу
                        remainingBurstTime[i] -= timeQuantum;
                    }

                    //Якщо час виконання менше або рівне кванту часу, виконуємо останній цикл для цього процесу
                    else {
                        // Збільшення значення t, це показує за скільки часу був оброблений процес
                        completionTimeZ += remainingBurstTime[i];
                        completionTime[lowPriorityProcessArray[i]] = completionTimeZ;

                        //Коли процес повністю виконається, час виконання буде рівний 0
                        remainingBurstTime[i] = 0;
                    }
                }
            }
            //Якщо всі процеси завершені
            if(isDone)
                break;
        }

        //Рахуємо час очікування і час повороту для всіх процесів в низькорівневій черзі
        for(int j = 0; j < lowPriorityProcessList.size(); j++){
            turnaroundTime[lowPriorityProcessArray[j]] = completionTime[lowPriorityProcessArray[j]];
            waitingTime[lowPriorityProcessArray[j]] = turnaroundTime[lowPriorityProcessArray[j]] - burstTime[lowPriorityProcessArray[j]];
        }

        System.out.println("\nPROCESS\t|\tPRIORITY|\tBURST TIME|\tCOMPLETION TIME |\tWAITING TIME|\tTURNAROUNDTIME");
        for(int i = 0; i < n; i++){
            System.out.println("\n" + p[i] + "\t\t|\t" + priority[i] + "\t\t|\t" + burstTime[i] + "\t\t  |\t" + completionTime[i] + "\t\t\t\t|\t" + waitingTime[i] + "\t\t\t|\t" + turnaroundTime[i]);
            totalWaitingTime += waitingTime[i];
            totalTurnaroundTime += turnaroundTime[i];
        }

        System.out.println("\nAverage Waiting Time is: " + totalWaitingTime /n);
        System.out.println("Average Turnaround Time is: " + totalTurnaroundTime /n);
    }

    public Object[] excelReader(String filepath) throws IOException {

        FileInputStream fileInputStream = new FileInputStream(new File(filepath));

        // Створюємо екземпляр книги, який посилається на файл .xls
        HSSFWorkbook hssfWorkbook = new HSSFWorkbook(fileInputStream);

        // Створюємо об'єкт листа для вилучення листа
        HSSFSheet hssfSheet = hssfWorkbook.getSheetAt(0);

        //Виводимо кількість процесів
        n = hssfSheet.getLastRowNum();
        System.out.println("\nTotal number of Process " + n);

        Object[] arrayObjects = new Object[2];

        // Парсинг часу пакету
        for (int i = 1; i <= n; i++){
            Row row = hssfSheet.getRow(i);
            String cell = (new DataFormatter().formatCellValue(row.getCell(1)));
            burstTime[i - 1] = Integer.parseInt(cell);
            arrayObjects[0] = burstTime;
        }

        // Парсинг пріоритетів
        for (int i = 1; i <= n; i++) {
            Row row = hssfSheet.getRow(i);
            String cell = (new DataFormatter().formatCellValue(row.getCell((2))));
            priority[i - 1] = Integer.parseInt(cell);
            arrayObjects[1] = priority;
        }

        hssfWorkbook.close();
        fileInputStream.close();

        return arrayObjects;
    }

}