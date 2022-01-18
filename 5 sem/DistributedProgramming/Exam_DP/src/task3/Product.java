package task3;

public class Product {

    private int id;
    private String name;
    private String manufacturer;
    private double price;
    private int expitationDate;
    private int number;


    public Product(){
        this.id = 0;
        this.name = "";
        this.manufacturer = "";
        this.price = 0;
        this.expitationDate = 0;
        this.number = 0;
    }

    public Product(int id, String name, String manufacturer, double price, int shelf_life, int number) {
        this.id = id;
        this.name = name;
        this.manufacturer = manufacturer;
        this.price = price;
        this.expitationDate = shelf_life;
        this.number = number;
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

    public int getExpitationDate() {
        return expitationDate;
    }
    public void setExpitationDate(int expitationDate) {
        if(expitationDate >0) {
            this.expitationDate = expitationDate;
        } else System.out.println("The shelf life cannot be negative or zero !");
    }

    public int getNumber() {
        return number;
    }
    public void setNumber(int number) {
        if (number>0) {
            this.number = number;
        } else System.out.println("Количество товара не может быть отрицательным или нулевым!!");
    }

    @Override
    public String toString() {
        return "Product - " +
                "ID = " + id +
                ", Name = " + name +
                ", Manufacturer = " + manufacturer  +
                ", Price = " + price +
                ", Expireation Date = " + expitationDate +
                ", Quantity = " + number;
    }
}