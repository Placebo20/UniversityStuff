package com.music_edu.music_system;

import com.music_edu.music.MusicGenre;
import com.music_edu.music.Track;
import com.music_edu.music.TrackDuration;

import java.util.List;

public class MusicSystem {
    private static final String TOTAL_DURATION = "Total duration of all tracks: ";
    private Double duration = 0.0;

    public void getTracks(List<Track> tracks) {
        for(Track track : tracks)
            System.out.println(track.toString());
        System.out.println();
    }

    public void getTotalDuration(List<Track> tracks){
        System.out.println("Get total duration method.");
        Integer durationMinutes = 0;
        Integer durationSeconds = 0;
        for(int i = 0; i < tracks.size(); i++) {
            durationMinutes += tracks.get(i).getTrackDuration().getMinutes();
            durationSeconds += tracks.get(i).getTrackDuration().getSeconds();
            if (durationSeconds >= 60) {
                durationMinutes++;
                durationSeconds -= 60;
            }
        }
        TrackDuration buff = new TrackDuration("totalDuration", durationMinutes, durationSeconds);
        System.out.println(TOTAL_DURATION + buff.toString() + '\n');
    }

    public void sortingByStyle(List<Track> tracks, MusicGenre genre){
        System.out.println("\nSorting by Style method.");
        for(Track track : tracks) {
            if (track.getTrackGenre() == genre)
                System.out.println(track.toString());
        }
        for(Track track : tracks) {
            if(track.getTrackGenre() != genre)
                System.out.println(track.toString());
        }
        System.out.println();
    }

    public void findByRange(TrackDuration start, TrackDuration finish, List<Track> tracks){
        System.out.println("Find by Range method.");
        Boolean isEmpty = true;
        for(int i = 0; i < tracks.size(); i++){

            Integer trackToFind = 0;
            trackToFind += tracks.get(i).getTrackDuration().getMinutes() * 60;
            trackToFind += tracks.get(i).getTrackDuration().getSeconds();

            Integer startSum = 0;
            startSum += start.getMinutes() * 60;
            startSum += start.getSeconds();

            Integer finishSum = 0;
            finishSum += finish.getMinutes() * 60;
            finishSum += finish.getSeconds();

            if(trackToFind >= startSum && trackToFind <= finishSum) {
                System.out.println(tracks.get(i).toString());
                isEmpty = false;
            }
        }
        if(isEmpty){
            System.out.println("There are no such tracks that would satisfy the condition (>" + start.toString() + ", <" + finish.toString() + ")");
        }
    }
}
