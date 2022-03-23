declare var api: any;

(() => {
    document.querySelector('#CompileButton') ?. addEventListener('click', () => {
        api.OpenCmd();
    })
})()
