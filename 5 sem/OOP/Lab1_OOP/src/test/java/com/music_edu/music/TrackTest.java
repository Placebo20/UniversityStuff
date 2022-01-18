package com.music_edu.music;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class TrackTest {
    Track testTrack = new Track("testTrackName", 0,1, MusicGenre.POP);

    @Test
    void getTrackName() {
        testTrack.getTrackName();
    }

    @Test
    void getTrackDuration() {
        testTrack.getTrackDuration();
    }

    @Test
    void getTrackGenre() {
        testTrack.getTrackGenre();
    }

    @Test
    void setTrackName() {
        testTrack.setTrackName("testTrackNameNew");
    }

    @Test
    void setTrackDuration() {
        testTrack.setTrackDuration(0,2);
    }

    @Test
    void setTrackGenre() {
        testTrack.setTrackGenre(MusicGenre.HIPHOP);
    }

    @Test
    void testToString() {
        testTrack.toString();
    }
}