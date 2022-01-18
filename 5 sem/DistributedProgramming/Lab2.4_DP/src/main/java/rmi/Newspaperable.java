package rmi;

import news.Category;
import news.News;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.sql.SQLException;
import java.util.ArrayList;

public interface Newspaperable extends Remote {
    public String hello() throws RemoteException;

    public void addCategory(int id, String name) throws RemoteException, SQLException;

    public void deleteCategory(int id) throws RemoteException, SQLException;

    public void addNews(int id, int id_cat, String name) throws RemoteException, SQLException;

    public void deleteNews(int id) throws RemoteException, SQLException;

    public void editNews(int id, int id_cat, String name) throws RemoteException, SQLException;

    public int countNews() throws RemoteException;

    public News getNewsById(int id) throws RemoteException;

    public ArrayList<News> getNewsByCategory(int id_cat) throws RemoteException;

    public ArrayList<Category> getCategories() throws RemoteException;
}