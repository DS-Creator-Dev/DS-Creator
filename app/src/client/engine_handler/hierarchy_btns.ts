declare var api: any;

(() => {
    document.querySelector('#bgBtn')?.addEventListener('click', () => {
        console.log('#bgBtn');
    }),
    document.querySelector('#sprBtn')?.addEventListener('click', () => {
        console.log('#sprBtn');
    }),
    document.querySelector('#sceneBtn')?.addEventListener('click', () => {
        console.log('#sceneBtn');
    }),
    document.querySelector('#actorBtn')?.addEventListener('click', () => {
        console.log('#actorBtn');
    }),
    document.querySelector('#musicBtn')?.addEventListener('click', () => {
        console.log('#musicBtn');
    }),
    document.querySelector('#sfxBtn')?.addEventListener('click', () => {
        console.log('#sfxBtn');
    })
})()
