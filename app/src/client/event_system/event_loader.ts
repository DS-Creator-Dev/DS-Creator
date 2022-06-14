declare var api: any;
var Events;

let ReloadBtn = document.getElementById("ReloadButton");

ReloadBtn?.addEventListener('click', () => {
    LoadTheEventsWait();
});

LoadTheEventsWait();
  
async function LoadTheEventsWait(){
    Events = undefined;
    await api.GetAppPath();
    await api.LoadEvents();
    //@ts-expect-error
    Events = JSON.parse(localStorage.getItem("Events"));
};