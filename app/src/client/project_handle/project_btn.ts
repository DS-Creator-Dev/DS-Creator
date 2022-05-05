declare var api: any;

var ProName: any;
var ProPath: any;

(() => {
    let NameObject = document.getElementById("name-input");
    let PathObject = document.getElementById("path-input");

    NameObject?.addEventListener('input', () => {
        //@ts-expect-error
        ProName = NameObject?.value.replaceAll(' ', '_');
        //@ts-expect-error
        NameObject.value = ProName;
    });

    PathObject?.addEventListener('input', () => {
        //@ts-expect-error
        ProPath = PathObject?.value.replaceAll(' ', '_');
        //@ts-expect-error
        PathObject.value = ProPath;
    });

    document.querySelector('#back-btn')?.addEventListener('click', () => {
        window.location.href = '../index.html';
    }),
    document.querySelector('#sample-proj-btn')?.addEventListener('click', () => {
        
    }),
    document.querySelector('#blank-proj-btn')?.addEventListener('click', () => {
        NameObject = document.getElementById("name-input");
        PathObject = document.getElementById("path-input");
        //@ts-expect-error
        ProName = NameObject?.value.replaceAll(' ', '_');
        //@ts-expect-error
        NameObject.value = ProName;
        //@ts-expect-error
        ProPath = PathObject?.value.replaceAll(' ', '_');
        //@ts-expect-error
        PathObject.value = ProPath;
        api.MakeBlankProject(ProName, ProPath);
    })
})()