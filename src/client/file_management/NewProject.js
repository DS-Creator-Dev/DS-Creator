"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const { contextBridge, ipcRenderer } = require('electron');
function OpenProject() {
    const files = api.showOpenFileDialog();
    console.log("Done");
}
function NewProject() {
    console.log("Done");
}
(() => {
    var _a, _b;
    //TODO: After a file is chosen, open the file and read contents. Then use the contents to know how many scenes, and what is on those scenes.
    (_a = document.querySelector('#btn-open-project')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        OpenProject();
    });
    (_b = document.querySelector('#btn-new-project')) === null || _b === void 0 ? void 0 : _b.addEventListener('click', () => {
        NewProject();
    });
})();
