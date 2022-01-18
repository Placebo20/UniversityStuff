package lab4c;

import java.util.ArrayList;
import java.util.Random;

public class Matrix {
    private ArrayList<ArrayList<Integer>> integers;
    private ArrayList<ArrayList<RWLock>> locks;

    public Matrix(int num) {
        locks = new ArrayList<>(num);
        for (int i = 0; i < num; i++) {
            ArrayList<RWLock> tmp = new ArrayList<>(num);
            for (int j = 0; j < num; j++)
                tmp.add(new RWLock());
            locks.add(tmp);
        }

        Random random = new Random();
        integers = new ArrayList<>(num);
        for (int i = 0; i < num; i++) {
            ArrayList<Integer> tmp = new ArrayList<>(num);
            for (int j = 0; j < num; j++)
                tmp.add(Math.abs(random.nextInt()) % 100);
            integers.add(tmp);
        }

    }
    public int getSizeOfIntegers() {return integers.size();}

    public int getInteger(int i, int j) throws Exception {
        if (i < 0 || j < 0) throw new Exception();
        return integers.get(i).get(j);
    }

    public int setInteger(int i, int j, int value) throws Exception {
        if (i < 0 || j < 0) throw new Exception();
        return integers.get(i).set(j, value);
    }


    public void LockRead(int i, int j) {locks.get(i).get(j).ReadLock();}
    public void UnlockRead(int i, int j) {locks.get(i).get(j).ReadUnlock();}
    public void LockWrite(int i, int j) {locks.get(i).get(j).WriteLock();}
    public void UnlockWrite(int i, int j) {locks.get(i).get(j).WriteUnlock();}

    public void LockRead() {
        for (int i = 0; i < locks.size(); i++)
            for (int j = 0; j< locks.get(0).size(); j++)
                LockRead(i ,j);
    }
    public void UnlockRead() {
        for (int i = 0; i < locks.size(); i++)
            for (int j = 0; j< locks.get(0).size(); j++)
                UnlockRead(i ,j);
    }

    public void matrixOutput() {
        try {
            for (int i = 0; i < getSizeOfIntegers(); i++){
                for (int j = 0; j < getSizeOfIntegers(); j++) {
                    System.out.print(getInteger(i, j) + " ");
                }
                System.out.println();
            }
        } catch (Exception e) {e.printStackTrace();}
    }
}
