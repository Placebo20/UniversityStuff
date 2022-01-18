package server;

import news.Category;
import news.News;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;


public class Client {

    private Socket sock = null;
    private ObjectOutputStream out = null;
    private ObjectInputStream in = null;

    public Client(String ip, int port) throws IOException {
        sock = new Socket(ip,port);
        out = new ObjectOutputStream(sock.getOutputStream());
        in = new ObjectInputStream(sock.getInputStream());
    }

    public void addCategory(int id, String category) throws IOException {
        out.writeObject("addCategory");
        out.writeObject(id);
        out.writeObject(category);
    }

    public void deleteCategory(int id) throws IOException {
        out.writeObject("deleteCategory");
        out.writeObject(id);
    }

    public void addNews(int id, int id_cat, String name) throws IOException {
        out.writeObject("addNews");
        out.writeObject(id);
        out.writeObject(id_cat);
        out.writeObject(name);
    }

    public void deleteNews(int id) throws IOException {
        out.writeObject("deleteNews");
        out.writeObject(id);
    }

    public void editNews(int id, int id_cat, String name) throws IOException {
        out.writeObject("editNews");
        out.writeObject(id);
        out.writeObject(id_cat);
        out.writeObject(name);
    }

    public int countNews() throws IOException, ClassNotFoundException {
        out.writeObject("countNews");
        return (int)in.readObject();
    }

    public ArrayList<News> getNewsById (int id) throws IOException, ClassNotFoundException {
        out.writeObject("getNewsById");
        out.writeObject(id);
        return (ArrayList<News>)in.readObject();
    }

    public ArrayList<News> getNewsForCategory (int id) throws IOException, ClassNotFoundException {
        out.writeObject("getNewsForCategory");
        out.writeObject(id);
        return (ArrayList<News>)in.readObject();
    }

    public ArrayList<Category> getCategories() throws IOException, ClassNotFoundException {
        out.writeObject("getCategories");
        return (ArrayList<Category>)in.readObject();
    }

    public void disconnect() throws IOException {
        sock.close();
    }


    public static void main(String[] args) throws IOException, ClassNotFoundException {
        Client client = new Client("localhost",12345);
        ArrayList<Category> categories = client.getCategories();
        for (Category category: categories){
            System.out.println(category.getId()+"  " +category.getName());
        }
        client.disconnect();
    }
}
