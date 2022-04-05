declare var api: any;

//@ts-expect-error
document.getElementById('hi').textContent = localStorage.getItem('ProjectDir');

(() => {
    document.querySelector('#CompileButton')?.addEventListener('click', () => {
        api.OpenCmd(localStorage.getItem('ProjectDir'));
        console.log("done Compile");
    })
})()
