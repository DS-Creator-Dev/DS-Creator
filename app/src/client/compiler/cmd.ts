const Store = require('electron-store');

const store = new Store('project');

declare var api: any;

//@ts-expect-error
document.getElementById('hi').textContent = store.get('ProjectDir');

(() => {
    document.querySelector('#CompileButton') ?. addEventListener('click', () => {
        api.OpenCmd(localStorage.getItem('DirPath'));
    })
})()
