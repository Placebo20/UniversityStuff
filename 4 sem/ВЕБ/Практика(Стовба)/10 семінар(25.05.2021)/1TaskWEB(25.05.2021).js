function init() {
    var button = document.getElementById("addButton");
    button.onclick = handleButtonClick;
    button = document.getElementById("ClearButton");
    button.onclick = clearStore;
    button = document.getElementById("DeleteButton");
    button.onclick = deleteStoreElement;
    loadPlaylist();
}
    
function handleButtonClick() {
    var textInput = document.getElementById("songTextInput");
    var songName = textInput.value;
    let q = save(songName);
    console.log(q);
    if (q) {
        var li = document.createElement("li");
        li.innerHTML = songName; 
        var ul = document.getElementById("playlist");
        ul.appendChild(li);
    } 
    else { alert("Данний елемент вже знаходиться в списку"); } 
}
    window.onload = init;