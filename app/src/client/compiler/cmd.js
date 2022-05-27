"use strict";
document.title = "DSC : " + localStorage.getItem('ProjectFileName');
(() => {
    var _a, _b, _c, _d;
    (_a = document.querySelector('#CompileButton')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        api.OpenCmd(localStorage.getItem('ProjectDir'), false);
        console.log("Compiled!");
    }),
        (_b = document.querySelector('#SaveButton')) === null || _b === void 0 ? void 0 : _b.addEventListener('click', () => {
            api.SaveProject();
        }),
        (_c = document.querySelector('#SettingsButton')) === null || _c === void 0 ? void 0 : _c.addEventListener('click', () => {
            api.Settings();
        }),
        (_d = document.querySelector('#PlayButton')) === null || _d === void 0 ? void 0 : _d.addEventListener('click', () => {
            api.OpenCmd(localStorage.getItem('ProjectDir'), true);
        });
})();
