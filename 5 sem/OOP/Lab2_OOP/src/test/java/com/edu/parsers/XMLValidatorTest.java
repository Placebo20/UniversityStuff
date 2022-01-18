package com.edu.parsers;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class XMLValidatorTest {

    @Test
    public void xmlValidate() {
        assertTrue(XMLValidator.validate("src/main/resources/devices.xml", "src/main/resources/devices.xsd"));
    }
}