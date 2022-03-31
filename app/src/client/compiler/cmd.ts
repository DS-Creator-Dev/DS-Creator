declare var api: any;

//@ts-expect-error
document.getElementById('hi').textContent = localStorage.getItem('DirPath');

(() => {
    document.querySelector('#CompileButton') ?. addEventListener('click', () => {
        api.OpenCmd(localStorage.getItem('DirPath'));
    })
})()
