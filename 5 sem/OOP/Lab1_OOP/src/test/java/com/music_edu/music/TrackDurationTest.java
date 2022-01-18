package com.music_edu.music;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class TrackDurationTest {
    TrackDuration trackDurationTest = new TrackDuration("trackDurationTest",0,1);
    @Test
    void getMinutes() {
        trackDurationTest.getMinutes();
    }

    @Test
    void getSeconds() {
        trackDurationTest.getSeconds();
    }

    @Test
    void setMinutes() {
        trackDurationTest.setMinutes(1);
    }

    @Test
    void setSeconds() {
        trackDurationTest.setSeconds(2);
    }

    @Test
    void testToString() {
        trackDurationTest.toString();
    }
}