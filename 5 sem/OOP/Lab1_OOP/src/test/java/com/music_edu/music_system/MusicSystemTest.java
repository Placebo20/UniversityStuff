package com.music_edu.music_system;

import com.music_edu.music.MusicGenre;
import com.music_edu.music.Track;
import com.music_edu.music.TrackDuration;

import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.List;

class MusicSystemTest {
    MusicSystem musicSystemTest = new MusicSystem();
    List<Track> testTracks = new ArrayList<>();

    MusicSystemTest() {
        // TOTAL DURATION IS 6:01
        testTracks.add(new Track("testTrackName1", 0,1, MusicGenre.POP));
        testTracks.add(new Track("testTrackName2", 0,10, MusicGenre.ROCK));
        testTracks.add(new Track("testTrackName3", 1,0, MusicGenre.ALTERNATIVE_ROCK));
        testTracks.add(new Track("testTrackName4", 1,100, MusicGenre.ALTERNATIVE_ROCK));
        testTracks.add(new Track("testTrackName5", 1, 70, MusicGenre.ALTERNATIVE_ROCK));
    }

    @Test
    void getTracks() {
        musicSystemTest.getTracks(testTracks);
    }

    @Test
    void getTotalDuration() {
        musicSystemTest.getTotalDuration(testTracks);
    }

    @Test
    void sortingByStyle() {
        musicSystemTest.sortingByStyle(testTracks, MusicGenre.ALTERNATIVE_ROCK);
    }

    @Test
    void findByRange() {
        TrackDuration trackDurationTestStart = new TrackDuration("trackDurationTestStart",0,1);
        TrackDuration trackDurationTestFinish = new TrackDuration("trackDurationTestFinish", 1, 0);
        musicSystemTest.findByRange(trackDurationTestStart, trackDurationTestFinish, testTracks);
    }
}