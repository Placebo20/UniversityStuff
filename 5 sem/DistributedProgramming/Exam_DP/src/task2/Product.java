package task2;

public class Product {

    private int id;
    private String name;
    private String manufacturer;
    private int UPC;
    private double price;
    private int expirationDate;
    private int quantity;


    public Product(){
        this.id = 0;
        this.name = "";
        this.manufacturer = "";
        this.UPC = 0;
        this.price = 0;
        this.expirationDate = 0;
        this.quantity = 0;
    }

    public Product(int id, String name, int UPC, String manufacturer, double price, int expirationDate, int number) {
        this.id = id;
        this.name = name;
        this.UPC = UPC;
        this.manufacturer = manufacturer;
        this.price = price;
        this.expirationDate = expirationDate;
        this.quantity = number;
    }

    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public int getUPC() {
        return UPC;
    }
    public void setUPC(int UPC) {
        if(UPC>0) {
            this.UPC = UPC;
        } else System.out.println("UPC не может быть отрицательным или нулевым!!");
    }

    public String getManufacturer() {
        return manufacturer;
    }
    public void setManufacturer(String manufacturer) {
        this.manufacturer = manufacturer;
    }

    public double getPrice() {
        return price;
    }
    public void setPrice(double price) {
        if(price>0) {
            this.price = price;
        } else System.out.println("The price cannot be negative or zero!");
    }

    public int getExpirationDate() {
        return expirationDate;
    }
    public void setExpirationDate(int expitationDate) {
        if(expitationDate >0) {
            this.expirationDate = expitationDate;
        } else System.out.println("The shelf life cannot be negative or zero !");
    }

    public int getQuantity() {
        return quantity;
    }
    public void setQuantity(int quantity) {
        if (quantity >0) {
            this.quantity = quantity;
        } else System.out.println("Количество товара не может быть отрицательным или нулевым!!");
    }

    @Override
    public String toString() {
        return "Product - " +
                "ID = " + id +
                ", Name = " + name +
                ", UPC=" + UPC +
                ", Manufacturer = " + manufacturer  +
                ", Price = " + price +
                ", Expiration Date = " + expirationDate +
                ", Quantity = " + quantity;
    }
}