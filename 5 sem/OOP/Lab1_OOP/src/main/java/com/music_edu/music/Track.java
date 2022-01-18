package com.music_edu.music;

public class Track {
    private String trackName;
    private TrackDuration trackDuration;
    private MusicGenre trackGenre;

    public Track(String trackName, Integer trackDurationMinutes, Integer trackDurationSeconds, MusicGenre trackGenre){
        this.trackName = trackName;
        this.trackDuration = new TrackDuration(this.trackName ,trackDurationMinutes, trackDurationSeconds);
        this.trackGenre = trackGenre;
    }

    public String getTrackName(){return trackName;}
    public TrackDuration getTrackDuration(){return trackDuration;}
    public MusicGenre getTrackGenre(){return trackGenre;}

    public void setTrackName(String trackName) {this.trackName = trackName;}
    public void setTrackDuration(Integer trackDurationMinutes, Integer trackDurationSeconds) {
        trackDuration.setDuration(trackDurationMinutes, trackDurationSeconds);
    }
    public void setTrackGenre(MusicGenre trackGenre) {this.trackGenre = trackGenre;}

    public String toString(){
        return "Track Name: " + getTrackName() + ", Duration: " + getTrackDuration() + ", Genre: " + getTrackGenre();
    }
}
