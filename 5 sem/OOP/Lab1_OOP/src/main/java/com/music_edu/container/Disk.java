package com.music_edu.container;

import static com.music_edu.music.MusicGenre.*;
import com.music_edu.music.Track;
import com.music_edu.music.TrackDuration;
import com.music_edu.music_system.MusicSystem;

import java.util.ArrayList;
import java.util.List;

public class Disk {
    private List<Track> tracks = new ArrayList<>();
    private MusicSystem system = new MusicSystem();

    public Disk() {
        tracks.add(new Track("Boulevard Depo - Angry Toys", 2, 6, HIPHOP));
        tracks.add(new Track("масло чёрного тмина - chemotherapy", 2, 49, HIPHOP));
        tracks.add(new Track("Океан Ельзи - Місто Весни(feat. Один в Каное)", 4,13, ALTERNATIVE_ROCK));
        tracks.add(new Track("Palina - Месяц", 2, 37, ELECTRO));
        tracks.add(new Track("Скрябін - Говорили і курили", 3, 32, POP_ROCK));
        tracks.add(new Track("JMi - Сигарет дым", 4, 9, POP_ROCK));
        tracks.add(new Track("Loqiemean - Одинокий каннибал", 3, 28, ALTERNATIVE_ROCK));
        tracks.add(new Track("Loqiemean - Хоровод(feat. Tatyana Shmalyuk)", 5, 49, ALTERNATIVE_ROCK));

        system.getTracks(tracks);
        system.getTotalDuration(tracks);
        system.sortingByStyle(tracks, ALTERNATIVE_ROCK);
        TrackDuration start = new TrackDuration("startDuration",2,20);
        TrackDuration finish = new TrackDuration("finishDuration",3,3);
        system.findByRange(start, finish, tracks);
    }
}
