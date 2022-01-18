package rmi;

import news.Category;
import news.News;
import dao.NewspaperDAO;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.sql.SQLException;
import java.util.ArrayList;


public class NewspaperableImpl extends UnicastRemoteObject
        implements Newspaperable {
    private NewspaperDAO newspaperDAO;

    public NewspaperableImpl() throws Exception {
        newspaperDAO = new NewspaperDAO();
    }

    public String hello() throws RemoteException {
        return "Hello from server!";
    }

    @Override
    public void addCategory(int id, String name) throws RemoteException, SQLException {
        newspaperDAO.addCategory(id, name);
    }

    @Override
    public void deleteCategory(int id) throws RemoteException, SQLException {
        newspaperDAO.deleteCategory(id);
    }

    @Override
    public void addNews(int id, int id_cat, String name) throws RemoteException, SQLException {
        newspaperDAO.addNews(id, id_cat, name);
    }

    @Override
    public void deleteNews(int id) throws RemoteException, SQLException {
        newspaperDAO.deleteNews(id);
    }

    @Override
    public void editNews(int id, int id_cat, String name) throws RemoteException, SQLException {
        newspaperDAO.deleteNews(id);
        newspaperDAO.addNews(id, id_cat, name);
    }

    @Override
    public int countNews() throws RemoteException {
        return newspaperDAO.getNews().size();
    }

    @Override
    public News getNewsById(int id) throws RemoteException {
        ArrayList<News> allnews = newspaperDAO.getNews();
        for (News news : allnews) {
            if (news.getId() == id) return news;
        }
        return null;
    }

    @Override
    public ArrayList<News> getNewsByCategory(int id_cat) throws RemoteException {
        ArrayList<News> allNews = newspaperDAO.getNews();
        ArrayList<News> newsByCategory = new ArrayList<>();
        for(News news : allNews){
            if(news.getCategoryId()==id_cat) newsByCategory.add(news);
        }
        return newsByCategory;
    }

    @Override
    public ArrayList<Category> getCategories() throws RemoteException {
        return newspaperDAO.getCategories();
    }
}