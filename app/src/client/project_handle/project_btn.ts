declare var api: any;

(() => {
    document.querySelector('#back-btn')?.addEventListener('click', () => {
        window.location.href = '../index.html';
    }),
    document.querySelector('#sample-proj-btn')?.addEventListener('click', () => {
        
    }),
    document.querySelector('#blank-proj-btn')?.addEventListener('click', () => {
        api.saveBox();
    })
})()