package task2;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;


public class ClientSocketTask9 {
    private Socket sock = null;
    private ObjectOutputStream out = null;
    private ObjectInputStream in = null;

    public ClientSocketTask9(String ip, int port) throws IOException {
        sock = new Socket(ip,port);
        out = new ObjectOutputStream(sock.getOutputStream());
        in = new ObjectInputStream(sock.getInputStream());
    }

    public void addId(int id, int ID) throws IOException {
        out.writeObject("addID");
        out.writeObject(id);
        out.writeObject(ID);
    }
    public void deleteID(int id) throws IOException {
        out.writeObject("deleteID");
        out.writeObject(id);
    }

    public void addName(int id, String name) throws IOException {
        out.writeObject("addName");
        out.writeObject(id);
        out.writeObject(name);
    }
    public void deleteName(int id) throws IOException {
        out.writeObject("deleteName");
        out.writeObject(id);
    }

    public void addManufacturer(int id, String manufacturer) throws IOException {
        out.writeObject("addmanufacturer");
        out.writeObject(id);
        out.writeObject(manufacturer);
    }
    public void deleteManufacturer(int id) throws IOException {
        out.writeObject("deleteManufacturer");
        out.writeObject(id);
    }

    public void addUPC(int id, int UPC) throws IOException {
        out.writeObject("addUPC");
        out.writeObject(id);
        out.writeObject(UPC);
    }
    public void deleteUPC(int id) throws IOException {
        out.writeObject("deleteUPC");
        out.writeObject(id);
    }

    public void addPrice(int id, int price) throws IOException {
        out.writeObject("addPrice");
        out.writeObject(id);
        out.writeObject(price);
    }
    public void deletePrice(int id) throws IOException {
        out.writeObject("deletePrice");
        out.writeObject(id);
    }

    public void addExpirationDate(int id, int expirationDate) throws IOException {
        out.writeObject("addExpirationDate");
        out.writeObject(id);
        out.writeObject(expirationDate);
    }
    public void deleteExpirationDate(int id) throws IOException {
        out.writeObject("deleteExpirationDate");
        out.writeObject(id);
    }

    public void addQuantity(int id, int quantity) throws IOException {
        out.writeObject("addQuantity");
        out.writeObject(id);
        out.writeObject(quantity);
    }
    public void deleteQuantity(int id) throws IOException {
        out.writeObject("deleteQuantity");
        out.writeObject(id);
    }

    public ArrayList<Product> getProductById(int id) throws IOException, ClassNotFoundException {
        out.writeObject("getNewsById");
        out.writeObject(id);
        return (ArrayList<Product>)in.readObject();
    }

    public ArrayList<Product> getProducts() throws IOException, ClassNotFoundException {
        out.write("getProducts");
        return (ArrayList<Product>)in.readObject();
    }

    public void disconnect() throws IOException {
        sock.close();
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        ClientSocketTask9 client = new ClientSocketTask9("localhost",12345);
        ArrayList<Product> products = client.getProducts();
        for (Product product: products){
            System.out.println(product.getId() + "  " + product.getName() + " " + product.getManufacturer() + " " +
                    + product.getUPC() + " " + product.getPrice() + " " + product.getExpirationDate() + " " + product.getQuantity());
        }
        client.disconnect();
    }
}
