declare var api: any;

//@ts-expect-error
document.getElementById('hi').textContent = localStorage.getItem('path');

(() => {
    document.querySelector('#CompileButton') ?. addEventListener('click', () => {
        api.OpenCmd(localStorage.getItem('path'));
    })
})()
