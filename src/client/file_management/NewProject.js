"use strict";
function OpenProject() {
    const files = api.showOpenFileDialog();
    console.log("Done");
}
function NewProject() {
    //Sending the logs but not doing the api function
    console.log("Before");
    api.NewProject();
    console.log("After");
}
(() => {
    var _a, _b;
    (_a = document.querySelector('#btn-open-project')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        OpenProject();
    });
    (_b = document.querySelector('#btn-new-project')) === null || _b === void 0 ? void 0 : _b.addEventListener('click', () => {
        NewProject();
    });
})();
