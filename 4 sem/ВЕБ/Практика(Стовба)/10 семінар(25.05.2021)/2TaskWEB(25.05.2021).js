function save(item) {
    var playlistArray = getStoreArray("playlist");
    let q = true;
    for (let i = 0; i < playlistArray.length; i++) {
        if (playlistArray[i] == item) q = false;
    }
    if (q) {
        playlistArray.push(item);
        localStorage.setItem("playlist", JSON.stringify(playlistArray)); }
        return q;
}
    
function loadPlaylist() {
    var playlistArray = getSavedSongs();
    var ul = document.getElementById("playlist");
    ul.innerHTML = "";
    if (playlistArray !=null) {
        for (var i=0; i<playlistArray.length; i++) {
            var li = document.createElement("li");
            li.innerHTML = playlistArray[i];
            ul.appendChild(li);
        }
    }
} 
    
function getSavedSongs() { return getStoreArray("playlist"); } 
    
function getStoreArray(key) {
    var playlistArray = localStorage.getItem(key);
    if (playlistArray == null || playlistArray == "") { playlistArray = new Array(); } 
    else { playlistArray = JSON.parse(playlistArray);} 
    return playlistArray;
}
    
function clearStore() {
    localStorage.clear();
    var ul = document.getElementById("playlist");
    ul.innerHTML = "";
}
    
function deleteStoreElement() {
    let item = document.getElementById("songTextInput").value;
    var playlistArray = getStoreArray("playlist");
    let q = true;
    for (let i = 0; i < playlistArray.length; i++) {
    if (playlistArray[i] == item) { playlistArray.splice(i, 1); q = false; break; } }
    if (q) alert("Елемент не існує");
    localStorage.setItem("playlist", JSON.stringify(playlistArray));
    loadPlaylist();
}