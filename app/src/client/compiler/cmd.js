"use strict";
const Store = require('electron-store');
const store = new Store('project');
//@ts-expect-error
document.getElementById('hi').textContent = store.get('ProjectDir');
(() => {
    var _a;
    (_a = document.querySelector('#CompileButton')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        api.OpenCmd(localStorage.getItem('DirPath'));
    });
})();
