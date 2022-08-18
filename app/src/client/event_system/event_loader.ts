declare var api: any;
var Events;

let ReloadBtn = document.getElementById("ReloadButton");

ReloadBtn?.addEventListener('click', () => {
    LoadTheEvents();
});

LoadTheEvents();
  
async function LoadTheEvents(){
    Events = undefined;
    await api.GetAppPath();
    await api.LoadEvents();
    setTimeout(function() {
        //@ts-expect-error
        Events = JSON.parse(localStorage.getItem("Events"));
    }, 1000)
};