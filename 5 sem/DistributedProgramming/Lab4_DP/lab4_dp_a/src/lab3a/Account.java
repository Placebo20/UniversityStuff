package lab3a;

public class Account {
    private String name;
    private String surname;
    private String phoneNumber;
    private String father;

    public Account(String name, String surname, String father, String number) {
        this.name = name;
        this.surname = surname;
        this.phoneNumber = number;
        this.father = father;
    }

    public String getName() {return name;}
    public void setName(String name) {this.name = name;}

    public String getSurname() {return surname;}
    public void setSurname(String surname) {this.surname = surname;}

    public String getPhoneNumber() {return phoneNumber;}
    public void setPhoneNumber(String phoneNumber) {this.phoneNumber = phoneNumber;}

    public String getFather() {return father;}
    public void setFather() {this.father = father;}

    @Override
    public String toString(){
        return "Name: " + name + " " + surname + ", Phone number: " + phoneNumber + ", Father: " + father + "\n";
    }
}
