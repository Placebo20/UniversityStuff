package com.edu.parsers;

import com.edu.prototype.Device;
import com.edu.prototype.Elements;
import org.junit.jupiter.api.Test;

import javax.xml.stream.XMLStreamException;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;


import static org.junit.jupiter.api.Assertions.*;

class ParserStAXTest {

    @Test
    void parseStAX() throws NullPointerException, FileNotFoundException, XMLStreamException {
        ParserStAX parserStAX = new ParserStAX();
        File xmlFile = new File("src/main/resources/devices.xml");
        List<Device> deviceList = parserStAX.parseStAX(xmlFile);

        Device firstDevice = deviceList.get(0);

        assertEquals(firstDevice.getTypes().getEnergyConsumption(), 6);
        assertEquals(firstDevice.getTypes().getPort(), "USB");
        assertEquals(firstDevice.getTypes().getGroup(), "Multimedia");
        assertTrue(firstDevice.getTypes().isPeripherals());
        assertTrue(firstDevice.getTypes().isCooler());

        assertEquals(Elements.FirstDeviceID, firstDevice.getId());
        assertEquals(Elements.FirstDeviceName, firstDevice.getName());

        assertEquals(firstDevice.getOrigin(), "United States");
        assertEquals(firstDevice.getPrice(), 1000);
        assertTrue(firstDevice.isCritical());

        Device secondDevice = deviceList.get(1);

        assertEquals(secondDevice.getTypes().getEnergyConsumption(), 1);
        assertEquals(secondDevice.getTypes().getPort(), "false");
        assertEquals(secondDevice.getTypes().getGroup(), "Sound");
        assertTrue(secondDevice.getTypes().isPeripherals());
        assertFalse(secondDevice.getTypes().isCooler());

        assertEquals(Elements.SecondDeviceID, secondDevice.getId());
        assertEquals(Elements.SecondDeviceName, secondDevice.getName());

        assertEquals(secondDevice.getOrigin(), "China");
        assertEquals(secondDevice.getPrice(), 50);
        assertTrue(secondDevice.isCritical());
    }
}