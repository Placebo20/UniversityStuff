package com.edu.parsers;

import com.edu.prototype.*;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class DeviceHandler extends DefaultHandler{

    private String valueOfElement;
    private List<Device> deviceList = new ArrayList<>();

    // Отримуємо повідомлення коли елемент починається
    @Override
    public void startElement(String url, String name, String attributeName, Attributes attributes) {
        switch(attributeName){
            case Elements.DEVICE:
                Device device = new Device();
                deviceList.add(device);
                break;
            case Elements.TYPES:
                Types types = new Types();
                getLastDevice().setTypes(types);
                break;
        }
    }

    // Отримуємо повідомлення коли елемент закінчується
    @Override
    public void endElement(String uri, String name, String attributeName) {
        switch(attributeName) {
            case Elements.ID -> getLastDevice().setId(valueOfElement);
            case Elements.NAME -> getLastDevice().setName(valueOfElement);
            case Elements.ORIGIN -> getLastDevice().setOrigin(valueOfElement);
            case Elements.PRICE -> getLastDevice().setPrice(Integer.valueOf(valueOfElement));
            case Elements.CRITICAL -> getLastDevice().setCritical(Boolean.parseBoolean(valueOfElement));
            case Elements.PERIPHERAL -> getLastDevice().getTypes().setPeripherals(Boolean.parseBoolean(valueOfElement));
            case Elements.ENERGY_CONSUMPTION -> getLastDevice().getTypes().setEnergyConsumption(Short.parseShort(valueOfElement));
            case Elements.COOLER -> getLastDevice().getTypes().setCooler(Boolean.parseBoolean(valueOfElement));
            case Elements.GROUP -> getLastDevice().getTypes().setGroup(valueOfElement);
            case Elements.PORT -> getLastDevice().getTypes().setPort(valueOfElement);
        }
    }

    public void setField(String attributeName, String str, Map<String, String> attributes) {
        switch(attributeName) {
            case Elements.DEVICE -> {
                Device device = new Device();
                deviceList.add(device);
            }
            case Elements.NAME -> getLastDevice().setName(str);
            case Elements.ID -> getLastDevice().setId(str);
            case Elements.ORIGIN -> getLastDevice().setOrigin(str);
            case Elements.PRICE -> getLastDevice().setPrice(Integer.valueOf(str));
            case Elements.CRITICAL -> getLastDevice().setCritical(Boolean.parseBoolean(str));
            case Elements.PERIPHERAL -> getLastDevice().getTypes().setPeripherals(Boolean.parseBoolean(str));
            case Elements.ENERGY_CONSUMPTION -> getLastDevice().getTypes().setEnergyConsumption(Short.parseShort(str));
            case Elements.COOLER -> getLastDevice().getTypes().setCooler(Boolean.parseBoolean(str));
            case Elements.PORT -> getLastDevice().getTypes().setPort(str);
            case Elements.GROUP -> getLastDevice().getTypes().setGroup(str);
            case Elements.TYPES -> {
                Types types = new Types();
                getLastDevice().setTypes(types);
            }

        }
    }

    public List<Device> getDeviceList() { return deviceList; }
    // Отримуємо повідомлення про початок документу
    @Override
    public void startDocument() throws SAXException {deviceList = new ArrayList<>();}
    // Отримуємо повідомлення про символьні дані всередині елементу
    @Override
    public void characters(char[] ch, int start, int length) throws SAXException { valueOfElement = new String(ch, start, length);}
    private Device getLastDevice() {return deviceList.get(deviceList.size() - 1);}
    public String getName() {return Elements.DEVICE;};
}
