package com.edu.parsers;

import com.edu.prototype.Device;
import com.edu.prototype.Elements;

import org.junit.jupiter.api.Test;

import java.io.File;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class ParserDOMTest {

    @Test
    void parseDOM() throws NullPointerException {
        ParserDOM domParser = new ParserDOM();
        File xmlFile = new File("src/main/resources/devices.xml");
        List<Device> devices = domParser.parseDOM(xmlFile);
        Device firstDevice = devices.get(0);

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

        Device secondDevice = devices.get(1);

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