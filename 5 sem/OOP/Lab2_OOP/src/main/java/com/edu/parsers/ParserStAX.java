package com.edu.parsers;

import com.edu.prototype.Device;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;

public class ParserStAX {
    public List<Device> parseStAX(File xml) throws XMLStreamException, FileNotFoundException {

        // Визначає абстрактну реалізацію фабрики для отримання потоків
        XMLInputFactory xmlInputFactory = XMLInputFactory.newInstance();
        // XMLEventReader зчитує файл XML як потік подій, а також надає методи, необхідні для розбору XML.
        XMLEventReader reader;

        DeviceHandler deviceHandler = new DeviceHandler();
        reader = xmlInputFactory.createXMLEventReader(new FileInputStream(xml));


        while(reader.hasNext()) {
            XMLEvent nextXMLEvent = reader.nextEvent();
            // Перевіряє, чи є поточний вузол вмісту тегом, що відкриває.
            if(nextXMLEvent.isStartElement()){
                StartElement startElement = nextXMLEvent.asStartElement();

                nextXMLEvent = reader.nextEvent();
                String name = startElement.getName().getLocalPart();
                if(nextXMLEvent.isCharacters()) {
                    List<Attribute> attributesList = new ArrayList<>();
                    Iterator<Attribute> iter = startElement.getAttributes();
                    while(iter.hasNext()) {
                        attributesList.add(iter.next());
                    }
                    Map<String, String> attributeMap = new HashMap<>();

                    for(Attribute attribute : attributesList){
                        attributeMap.put(attribute.getName().getLocalPart(), attribute.getValue());
                    }
                    deviceHandler.setField(name, nextXMLEvent.asCharacters().getData(), attributeMap);
                }
            }
        }
        return deviceHandler.getDeviceList();
    }
}
