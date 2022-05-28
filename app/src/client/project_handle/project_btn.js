"use strict";
var ProName;
var ProPath;
var PathLastChar;
let NameObject = document.getElementById("name-input");
let PathObject = document.getElementById("path-input");
(() => {
    var _a, _b, _c;
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
        PathLastChar = ProPath.slice(-1);
    });
    (_a = document.querySelector('#back-btn')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        window.location.href = '../index.html';
    }),
        (_b = document.querySelector('#sample-proj-btn')) === null || _b === void 0 ? void 0 : _b.addEventListener('click', () => {
        }),
        (_c = document.querySelector('#blank-proj-btn')) === null || _c === void 0 ? void 0 : _c.addEventListener('click', () => {
            api.GetAppPath();
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
            PathLastChar = ProPath.slice(-1);
            if (PathLastChar == "\\") {
                ProPath = ProPath.slice(0, -1);
            }
            api.MakeBlankProject(ProName, ProPath);
        });
})();
