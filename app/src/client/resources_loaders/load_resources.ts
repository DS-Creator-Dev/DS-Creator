declare var api: any;
var Backgrounds;
var Sprites;
var Sfx;
var Music;

ReloadBtn?.addEventListener('click', () => {
    LoadTheResourcesWait();
});

LoadTheResourcesWait();
  
async function LoadTheResourcesWait(){
    Events = undefined;
    await api.GetAppPath();
    await api.LoadMusicAndSfx();
    //@ts-expect-error
    Music = JSON.parse(localStorage.getItem(".MODs"));
    //@ts-expect-error
    Sfx = JSON.parse(localStorage.getItem(".WAVs"));
};