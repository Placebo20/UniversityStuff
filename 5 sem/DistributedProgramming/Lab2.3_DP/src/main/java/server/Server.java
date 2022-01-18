package server;

import news.Category;
import news.News;
import dao.NewspaperDAO;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Calendar;


public class Server {

    private ServerSocket server = null;
    private Socket sock = null;
    private ObjectOutputStream out = null;
    private ObjectInputStream in = null;
    private NewspaperDAO newspaperDAO = null;

    public void start(int port) throws Exception {
        server = new ServerSocket(port);
        newspaperDAO = new NewspaperDAO();
        while (true) {
            sock = server.accept();
            in = new ObjectInputStream(sock.getInputStream());
            out = new ObjectOutputStream(sock.getOutputStream());
            while (processQuery()) ;
        }
    }

    private boolean processQuery() throws SQLException {
        try {
            String command = (String) in.readObject();
            switch (command) {
                case "addCategory": {
                    int id = (int) in.readObject();
                    String name = (String) in.readObject();
                    newspaperDAO.addCategory(id, name);
                }
                break;
                case "deleteCategory": {
                    int id = (int) in.readObject();
                    newspaperDAO.deleteCategory(id);
                }
                break;
                case "addNews": {
                    int id = (int) in.readObject();
                    int id_cat = (int) in.readObject();
                    String name = (String) in.readObject();
                    newspaperDAO.addNews(id, id_cat, name);
                }
                break;
                case "deleteNews": {
                    int id = (int) in.readObject();
                    newspaperDAO.deleteNews(id);
                }
                break;
                case "editNews": {
                    int id = (int) in.readObject();
                    int id_cat = (int) in.readObject();
                    String name = (String) in.readObject();
                    newspaperDAO.deleteNews(id);
                    newspaperDAO.addNews(id, id_cat, name);
                }
                break;
                case "countNews": //count News
                {
                    out.writeObject(newspaperDAO.getNews().size());
                }
                break;
                case "getNewsById": {
                    int id = (int) in.readObject();
                    ArrayList<News> newses = newspaperDAO.getNews();
                    News result = null;
                    for (News news : newses) {
                        if (news.getId() == id) {
                            result = news;
                            break;
                        }
                    }
                    out.writeObject(result);
                }
                break;
                case "getNewsForCategory": //get ArrayList of news for category
                {
                    int id_cat = (int) in.readObject();
                    ArrayList<News> newses = newspaperDAO.getNews();
                    ArrayList<News> newsByCategory = new ArrayList<>();
                    for (News news : newses) {
                        if (news.getCategoryId() == id_cat) {
                            newsByCategory.add(news);
                        }
                    }
                    out.writeObject(newsByCategory);
                }
                break;
                case "getCategories": //get ArrayList of all categories
                {
                    ArrayList<Category> categories = newspaperDAO.getCategories();
                    out.writeObject(categories);
                }
                break;
            }
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static void main(String[] args) {
        try {
            Server srv = new Server();
            srv.start(12345);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}