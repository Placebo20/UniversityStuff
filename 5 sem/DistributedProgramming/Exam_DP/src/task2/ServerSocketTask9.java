package task2;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.SQLException;
import java.util.ArrayList;

public class ServerSocketTask9 {
    private ServerSocket server = null;
    private Socket sock = null;
    private ObjectOutputStream out = null;
    private ObjectInputStream in = null;
    private ProductDAO productDAO = null;

    public void start(int port) throws Exception {
        server = new ServerSocket(port);
        productDAO = new ProductDAO();
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
                    productDAO.addProduct(id, name);
                }
                break;
                case "deleteProduct": {
                    int id = (int) in.readObject();
                    productDAO.deleteProduct(id);
                }
                break;

                break;
                case "getProductsById": {
                    int id = (int) in.readObject();
                    ArrayList<Product> products = productDAO.getProducts();
                    Product result = null;
                    for (Product roduct : products) {
                        if (products.getId() == id) {
                            result = products;
                            break;
                        }
                    }
                    out.writeObject(result);
                }
                break;
                case "getProducts":
                {
                    ArrayList<Product> products = productDAO.getProducts();
                    out.writeObject(products);
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
            ServerSocketTask9 srv = new ServerSocketTask9();
            srv.start(12345);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
