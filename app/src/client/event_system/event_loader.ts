declare var api: any;

let ReloadBtn = document.getElementById("ReloadButton");

ReloadBtn?.addEventListener('click', () => {
    LoadTheEventsWait();
});

LoadTheEventsWait();

async function LoadTheEvents() {
}
  
async function LoadTheEventsWait(){
    await api.GetAppPath();
    await api.LoadEvents();
    //@ts-expect-error
    var Events = JSON.parse(localStorage.getItem("Events"));
    console.log(Events);
};