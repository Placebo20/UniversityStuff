package dao;
import news.Category;
import news.News;

import java.sql.*;
import java.util.ArrayList;

public class NewspaperDAO {

    private Connection conn = null;
    private Statement stmt = null;

    public NewspaperDAO() throws Exception {
        final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        final String DB_URL = "jdbc:mysql://localhost/newspaper?autoReconnect=true&useSSL=false";
        final String USER = "root";
        final String PASS = "admin";

        Class.forName(JDBC_DRIVER).newInstance();
        conn = DriverManager.getConnection(DB_URL, USER, PASS);
        stmt = conn.createStatement();
    }
    public void stop() throws SQLException {
        conn.close();
    }
    public boolean addCategory(Category category) throws SQLException {
        return addCategory(category.getId(), category.getName());
    }

    public boolean addCategory(int id, String name) throws SQLException {
        String sql = "INSERT INTO categories (id_cat, name)" +
                "VALUES (" + id + ", '" + name + "')";
        try {
            stmt.executeUpdate(sql);
            System.out.println("You have successfully added category: " + name);
            return true;
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());

            return false;
        }
    }

    public boolean deleteCategory(Category category) throws SQLException {
        return deleteCategory(category.getId());
    }

    public boolean deleteCategory(int id) throws SQLException {
        String sql = "DELETE FROM categories WHERE id_cat = " + id;
        try {
            int c = stmt.executeUpdate(sql);
            if (c > 0) {
                System.out.println("You have successfully deleted category with id " + id);
                return true;
            } else {
                System.out.println("Category not found!");
                return false;
            }
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());
            return false;
        }
    }

    public void showCategories() {
        String sql = "SELECT id_cat, name FROM categories";
        try {
            ResultSet rs = stmt.executeQuery(sql);
            System.out.println("List of categories:");
            while (rs.next()) {
                int id = rs.getInt("id_cat");
                String name = rs.getString("name");
                System.out.println(" >> " + id + " - " + name);
            }
            rs.close();
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());
        }
    }

    public ArrayList<Category> getCategories() {
        ArrayList<Category> categories = null;
        String sql = "SELECT id_cat, name FROM categories";
        try {
            ResultSet rs = stmt.executeQuery(sql);
            System.out.println("List of categories:");
            categories = new ArrayList<>();
            while (rs.next()) {
                int id = rs.getInt("id_cat");
                String name = rs.getString("name");
                categories.add(new Category(id, name));
                System.out.println(" >> " + id + " - " + name);
            }
            rs.close();
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());
        }

        return categories;
    }

    public boolean addNews(News news) throws SQLException {
        return addNews(news.getId(), news.getCategoryId(), news.getName());
    }

    public boolean addNews(int id, int id_cat, String name) throws SQLException {
        String sql = "INSERT INTO news (id_news, id_cat, name)" +
                "VALUES (" + id + ", " + id_cat + ", '" + name + "')";
        try {
            stmt.executeUpdate(sql);
            System.out.println("You have successfully added news: " + name);
            return true;
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());

            return false;
        }
    }

    public boolean deleteNews(News news) throws SQLException {
        return deleteNews(news.getId());
    }

    public boolean deleteNews(int id) throws SQLException {
        String sql = "DELETE FROM news WHERE id_news = " + id;
        try {
            int c = stmt.executeUpdate(sql);
            if (c > 0) {
                System.out.println("You have successfully deleted news with id " + id);
                return true;
            } else {
                System.out.println("News not found!");
                return false;
            }
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());
            return false;
        }
    }

    public ArrayList<News> getNews() {
        ArrayList<News> news = null;
        String sql = "SELECT id_news, id_cat, name FROM news";
        try {
            ResultSet rs = stmt.executeQuery(sql);
            System.out.println("List of news:");
            news = new ArrayList<>();
            while (rs.next()) {
                int id = rs.getInt("id_news");
                int id_cat = rs.getInt("id_cat");
                String name = rs.getString("name");
                news.add(new News(id, id_cat, name));
                System.out.println(" >> " + id + " - " + id_cat + "-" + name);
            }
            rs.close();
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());
        }

        return news;
    }

    public void showNews() {
        String sql = "SELECT id_news, id_cat, name FROM news";
        try {
            ResultSet rs = stmt.executeQuery(sql);
            System.out.println("List of news:");
            while (rs.next()) {
                int id = rs.getInt("id_news");
                int id_cat = rs.getInt("id_cat");
                String name = rs.getString("name");
                System.out.println(" >> " + id + " - " + id_cat + "-" + name);
            }
            rs.close();
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());
        }
    }


    public static void main(String[] args) throws Exception {
        NewspaperDAO n = new NewspaperDAO();

        n.showCategories();
        n.addCategory(3, "Sport");
        n.addCategory(4, "Soccer");
        n.deleteCategory(3);
        n.showCategories();
        n.addNews(4, 4, "Sevilla won!");
        n.addNews(5, 4, "Liverpool lost!");
        n.showNews();
        n.deleteNews(5);
        n.showNews();
        n.stop();

    }

}
