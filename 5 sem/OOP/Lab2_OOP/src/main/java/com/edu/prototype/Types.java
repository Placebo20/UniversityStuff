package com.edu.prototype;

public class Types {
    private Boolean peripheral;
    private Short energyConsumption;
    private Boolean cooler;
    private String port;
    private String group;

    @Override
    public String toString() {
        return "Options{" +
                "peripherals=" + peripheral +
                ", energyConsumption=" + energyConsumption +
                ", presenceCooler=" + cooler +
                ", port=" + port +
                ", group=" + group +
                '}';
    }

    public boolean isPeripherals() {return peripheral;}
    public void setPeripherals(boolean value) {this.peripheral = value;}

    public int getEnergyConsumption() {return energyConsumption;}
    public void setEnergyConsumption(short value) {this.energyConsumption = value;}

    public boolean isCooler() {return cooler;}
    public void setCooler(boolean value) {this.cooler = value;}

    public String getPort() {return port;}
    public void setPort(String value) {this.port = value;}

    public String getGroup(){return group;}
    public void  setGroup(String value){this.group = value;}
}
