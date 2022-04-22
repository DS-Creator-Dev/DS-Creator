declare var api: any;

document.title = "DSC : " + localStorage.getItem('ProjectFileName');

(() => {
    document.querySelector('#CompileButton')?.addEventListener('click', () => {
        api.OpenCmd(localStorage.getItem('ProjectDir'));
        console.log("Compiled!");
    }),
    document.querySelector('#SaveButton')?.addEventListener('click', () => {
        api.SaveProject();
    }),
    document.querySelector('#SettingsButton')?.addEventListener('click', () => {
        api.Settings();
    })
})()
