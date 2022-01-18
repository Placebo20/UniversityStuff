package lab4c;

import java.util.Random;

public class WorkThread extends Thread {
    private Matrix matrix;
    private int task;

    public WorkThread(Matrix matrix, int task) {
        this.matrix = matrix;
        this.task = task;
    }

    @Override
    public void run() {
        switch (task) {
            case 1: changePrice(); break;
            case 2: AddingDeletingWay(); break;
            case 3: showPrice(); break;
            case 4: showMatrix(); break;
            default:
                System.out.println("There is not task like that");
        }
    }

    public void changePrice() {
        Random random = new Random();
        while (true) {
            int i = Math.abs(random.nextInt()) % matrix.getSizeOfIntegers();
            int j = Math.abs(random.nextInt()) % matrix.getSizeOfIntegers();
            int priceToChange = Math.abs(random.nextInt()) % 100;

            try {
                while (matrix.getInteger(i, j) == -1) {
                    i = Math.abs(random.nextInt()) % matrix.getSizeOfIntegers();
                    j = Math.abs(random.nextInt()) % matrix.getSizeOfIntegers();
                    priceToChange = Math.abs(random.nextInt()) % 100;
                }
            } catch (Exception e) {e.printStackTrace();}

            matrix.LockWrite(i, j);
            System.out.println("Changing price.");
            try {
                matrix.setInteger(i, j, priceToChange);
                System.out.println("Changing price from " + i + " to " + j + " is " + priceToChange);
            } catch (Exception e) {e.printStackTrace();}
            System.out.println("Finished to change price");
            matrix.UnlockWrite(i, j);

            try {Thread.sleep(8000);}
            catch (InterruptedException e) {e.printStackTrace();}
        }
    }
    public void AddingDeletingWay() {
        Random rand = new Random();
        while (true) {
            int i = Math.abs(rand.nextInt()) % matrix.getSizeOfIntegers();
            int j = Math.abs(rand.nextInt()) % matrix.getSizeOfIntegers();
            boolean addBool = rand.nextBoolean();

            if (addBool) {
                try {
                    while (matrix.getInteger(i, j) == -1) {
                        i = Math.abs(rand.nextInt()) % matrix.getSizeOfIntegers();
                        j = Math.abs(rand.nextInt()) % matrix.getSizeOfIntegers();
                    }
                } catch (Exception e) {e.printStackTrace();}
            } else {
                try {
                    while (matrix.getInteger(i, j) != -1) {
                        i = Math.abs(rand.nextInt()) % matrix.getSizeOfIntegers();
                        j = Math.abs(rand.nextInt()) % matrix.getSizeOfIntegers();
                    }
                } catch (Exception e) {e.printStackTrace();}
            }

            matrix.LockWrite(i, j);
            System.out.println("Add/Delete way: Start");
            try {
                if (addBool) {
                    int new_price = Math.abs(rand.nextInt()) % 100;
                    try {
                        matrix.setInteger(i, j, new_price);
                        System.out.println("Changing price: Added from " + i + " to " + j + " is " + new_price);
                    } catch (Exception e) {e.printStackTrace();}
                } else {
                    try {
                        matrix.setInteger(i, j, -1);
                        System.out.println("Changing price: Deleted from " + i + " to " + j);
                    } catch (Exception e) {e.printStackTrace();}
                }
                matrix.setInteger(i, j, -1);
            } catch (Exception e) {e.printStackTrace();}
            System.out.println("Add/Delete way: Finish");
            matrix.UnlockWrite(i, j);

            try {Thread.sleep(6000);}
            catch (InterruptedException e) {e.printStackTrace();}
        }
    }
    public void showPrice() {
        Random rand = new Random();
        while (true) {
            int i = Math.abs(rand.nextInt()) % matrix.getSizeOfIntegers();
            int j = Math.abs(rand.nextInt()) % matrix.getSizeOfIntegers();
            try {
                while (matrix.getInteger(i, j) < 0)
                    j = Math.abs(rand.nextInt()) % matrix.getSizeOfIntegers();
            } catch (Exception e) {e.printStackTrace();}

            matrix.LockRead(i, j);
            System.out.println("Price: Start");
            try {System.out.println("Price: from " + i + " to " + j + " costs = " + matrix.getInteger(i, j));}
            catch (Exception e) {e.printStackTrace();}
            System.out.println("Price: End");
            matrix.UnlockRead(i, j);

            try {Thread.sleep(4000);}
            catch (InterruptedException e) {e.printStackTrace();}
        }
    }

    public void showMatrix() {
        while (true) {
            matrix.LockRead();
            matrix.matrixOutput();
            matrix.UnlockRead();
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
