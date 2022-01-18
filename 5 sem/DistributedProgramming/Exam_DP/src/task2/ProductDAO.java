package task2;

import java.sql.*;
import java.util.ArrayList;

public class ProductDAO {

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
    public boolean addProduct(Product product) throws SQLException {
        return addProduct(product.getId(), product.getName());
    }

    public boolean addID(int id, String ID) throws SQLException {
        String sql = "INSERT INTO categories (id_cat, name)" +
                "VALUES (" + id + ", '" + ID + "')";
        try {
            stmt.executeUpdate(sql);
            System.out.println("You have successfully added category: " + ID);
            return true;
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());

            return false;
        }
    }

    public boolean deleteID(Product product) throws SQLException {
        return deleteCategory(product.getId());
    }

    public boolean deleteProduct(int id) throws SQLException {
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

    public void showProducts() {
        String sql = "SELECT id_cat, name FROM categories";
        try {
            ResultSet rs = stmt.executeQuery(sql);
            System.out.println("List of products:");
            while (rs.next()) {
                int id = rs.getInt("id_meat");
                String name = rs.getString("product");
                System.out.println(" >> " + id + " - " + name);
            }
            rs.close();
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());
        }
    }

    public ArrayList<Product> getProducts() {
        ArrayList<Product> product = null;
        String sql = "SELECT id_cat, name FROM product";
        try {
            ResultSet rs = stmt.executeQuery(sql);
            System.out.println("List of categories:");
            product = new ArrayList<>();
            while (rs.next()) {
                int id = rs.getInt("id_cat");
                String name = rs.getString("name");
                product.add(new Product(id, name));
                System.out.println(" >> " + id + " - " + name);
            }
            rs.close();
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());
        }

        return products;
    }

    public boolean addProduct(Product product) throws SQLException {
        return addProduct(product.getId(), product.getProductId(), product.getName());
    }

    public boolean addProducts(int id, int id_cat, String name) throws SQLException {
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

    public boolean deleteProducts(Product product) throws SQLException {
        return deleteProducts(product.getId());
    }

    public boolean deleteProducts(int id) throws SQLException {
        String sql = "DELETE FROM news WHERE id_news = " + id;
        try {
            int c = stmt.executeUpdate(sql);
            if (c > 0) {
                System.out.println("You have successfully deleted news with id " + id);
                return true;
            } else {
                System.out.println("Products not found!");
                return false;
            }
        } catch (SQLException e) {
            System.out.println("Error!");
            System.out.println(" >> " + e.getMessage());
            return false;
        }
    }


    public static void main(String[] args) throws Exception {
        ProductDAO n = new  ProductDAO();

        n.showProducts();
        n.addProduct(3, "Meat");
        n.addProduct(4, "Corn");
        n.deleteProducts(3);
        n.showProducts();
        n.stop();

    }

}
