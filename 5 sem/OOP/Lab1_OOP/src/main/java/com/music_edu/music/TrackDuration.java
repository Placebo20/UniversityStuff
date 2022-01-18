package com.music_edu.music;

public class TrackDuration {
    private Integer minutes = 0;
    private Integer seconds = 0;

    public TrackDuration(String trackName, Integer minutes, Integer seconds){
        if(seconds >= 0 && seconds <= 60 && minutes >= 0) {
            this.minutes = minutes;
            this.seconds = seconds;
        } else if (seconds > 59){
            Integer addMinutes = seconds / 60;
            System.out.println("\nSeconds > 59, so it converted to minutes.");
            this.minutes = minutes;
            this.minutes += addMinutes;
            this.seconds = seconds % 60;
        } else {
            System.out.println("Incorrect value. TrackName: " + trackName + "(TrackDuration constructor)");
        }
    }

    public Integer getMinutes() {return minutes;}
    public Integer getSeconds() {return seconds;}

    public void setDuration(Integer minutes, Integer seconds){
        if(minutes >= 0 && seconds >= 0 && seconds <= 59){
            this.minutes = minutes;
            this.seconds = seconds;
        } else if (seconds > 59){
            Integer addMinutes = seconds / 60;
            System.out.println("Seconds > 59, so it converted to minutes.");
            this.minutes = minutes;
            this.minutes += addMinutes;
            this.seconds = seconds % 60;
        } else System.out.println("Incorrect value. (setMinutes(Integer minutes))");
    }
    public void setMinutes(Integer minutes) {
        if(minutes >= 0) this.minutes = minutes;
        else System.out.println("Incorrect value. (setMinutes(Integer minutes))");
    }
    public void setSeconds(Integer seconds) {
        if(seconds >= 0 && seconds <= 60) this.seconds = seconds;
        else System.out.println("Incorrect value. (setSeconds(Integer seconds))");
    }

    public String toString(){
        if(seconds >= 10) return(minutes + ":" + seconds);
        else return(minutes + ":0" + seconds);
    }
}
