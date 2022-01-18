package com.edu.prototype;

import java.util.Comparator;

public class DeviceComparator implements Comparator<Device> {
    @Override
    public int compare(Device o1, Device o2) {
        return o1.getPrice().compareTo(o2.getPrice());
    }
}
