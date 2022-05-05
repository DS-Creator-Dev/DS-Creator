"use strict";
var ProName;
var ProPath;
(() => {
    var _a, _b, _c;
    let NameObject = document.getElementById("name-input");
    let PathObject = document.getElementById("path-input");
    NameObject === null || NameObject === void 0 ? void 0 : NameObject.addEventListener('input', () => {
        //@ts-expect-error
        ProName = NameObject === null || NameObject === void 0 ? void 0 : NameObject.value.replaceAll(' ', '_');
        //@ts-expect-error
        NameObject.value = ProName;
    });
    PathObject === null || PathObject === void 0 ? void 0 : PathObject.addEventListener('input', () => {
        //@ts-expect-error
        ProPath = PathObject === null || PathObject === void 0 ? void 0 : PathObject.value.replaceAll(' ', '_');
        //@ts-expect-error
        PathObject.value = ProPath;
    });
    (_a = document.querySelector('#back-btn')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        window.location.href = '../index.html';
    }),
        (_b = document.querySelector('#sample-proj-btn')) === null || _b === void 0 ? void 0 : _b.addEventListener('click', () => {
        }),
        (_c = document.querySelector('#blank-proj-btn')) === null || _c === void 0 ? void 0 : _c.addEventListener('click', () => {
            NameObject = document.getElementById("name-input");
            PathObject = document.getElementById("path-input");
            //@ts-expect-error
            ProName = NameObject === null || NameObject === void 0 ? void 0 : NameObject.value.replaceAll(' ', '_');
            //@ts-expect-error
            NameObject.value = ProName;
            //@ts-expect-error
            ProPath = PathObject === null || PathObject === void 0 ? void 0 : PathObject.value.replaceAll(' ', '_');
            //@ts-expect-error
            PathObject.value = ProPath;
            api.MakeBlankProject(ProName, ProPath);
        });
})();
