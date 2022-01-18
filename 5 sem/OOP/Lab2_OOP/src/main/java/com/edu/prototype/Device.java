package com.edu.prototype;

import java.util.ArrayList;
import java.util.List;

public class Device{

    private String name;
    private String id;
    private String origin;
    private Integer price;
    private Boolean critical;
    private Types types;

    public String getName() {return name;}
    public void setName(String value) {this.name = value;}

    public String getOrigin() {return origin;}
    public void setOrigin(String value) {this.origin = value;}

    public Integer getPrice() {return price;}
    public void setPrice(Integer value) {this.price = value;}

    public Types getTypes() {return types;}
    public void setTypes(Types value) {this.types = value;}

    public boolean isCritical() {return critical;}
    public void setCritical(boolean value) {this.critical = value;}

    public String getId() {return id;}
    public void setId(String value) {this.id = value;}
}
