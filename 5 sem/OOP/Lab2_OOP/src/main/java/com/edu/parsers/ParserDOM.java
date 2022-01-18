package com.edu.parsers;

import com.edu.prototype.Device;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ParserDOM {

    public List<Device> parseDOM(File xml){
        // Визначаємо API, який дозволяє програмам отримувати синтаксичний аналізатор, який створює дерева об’єктів DOM з документів XML.
        DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
        try {
            // Визначаємо API для отримання екземплярів документа DOM з документа XML.
            DocumentBuilder documentBuilder = documentBuilderFactory.newDocumentBuilder();
            Document document = documentBuilder.parse(xml);
            document.getDocumentElement().normalize();
            Element rootNode = document.getDocumentElement();
            DeviceHandler deviceHandler = new DeviceHandler();
            NodeList listOfDevices = rootNode.getElementsByTagName(deviceHandler.getName());

            // Проходимо по дереву об'єктів DOM
            for (int i = 0; i < listOfDevices.getLength(); i++) {
                Element deviceElement = (Element) listOfDevices.item(i);
                detouringNodes(deviceElement,deviceHandler);
            }
            return deviceHandler.getDeviceList();
        } catch (Exception e) {e.getStackTrace();}
        return null;
    }

    // Проходимо по вузлу дерева та витягуємо дані про девайси (рекурсивно)
    private void detouringNodes(Node node, DeviceHandler deviceHandler) {
        if(node.getNodeType() == Node.ELEMENT_NODE) {
            Map<String, String> attributes = new HashMap<>();
            if (node.getAttributes() != null) {
                for (int i = 0; i < node.getAttributes().getLength(); i++) {
                    attributes.put(node.getAttributes().item(i).getNodeName(), node.getAttributes().item(i).getTextContent());

                }
            }
            deviceHandler.setField(node.getNodeName(), node.getTextContent(), attributes);
            if(node.getChildNodes() != null){
                for(int i = 0; i < node.getChildNodes().getLength(); i++){
                    detouringNodes(node.getChildNodes().item(i), deviceHandler);
                }
            }
        }
    }

}
