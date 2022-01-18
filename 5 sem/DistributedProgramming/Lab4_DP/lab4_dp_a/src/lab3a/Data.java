package lab3a;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Data {
    public ArrayList<Account> accounts;
    private ReadWriteLock readWriteLock;

    public Data(){
        accounts = startAccountsInit();
        readWriteLock = new ReentrantReadWriteLock();
    }

    private ArrayList<Account> startAccountsInit(){
        ArrayList<Account> acc = new ArrayList<>();
        acc.add(new Account("Dmytro", "Hushcha","Serhiy","+380000000000"));
        acc.add(new Account("Karyna", "Dubovets","Viktor","+380111111111"));
        acc.add(new Account("Serhyi", "Hushcha","Mykola","+380222222222"));
        acc.add(new Account("Iryna", "Hushcha","Vasil","+380333333333"));
        acc.add(new Account("Mykola", "Hushcha","Serhiy","+380444444444"));
        acc.add(new Account("Stephen", "Hawking", "William", "paradise"));
        return acc;
    }
    public void lockRead() {readWriteLock.readLock().lock();}
    public void lockWrite() {readWriteLock.writeLock().lock();}

    public void unlockRead() {readWriteLock.readLock().unlock();}
    public void unlockWrite() {readWriteLock.writeLock().unlock();}
}
