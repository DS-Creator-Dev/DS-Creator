"use strict";
function NewProject() {
    const files = api.showOpenFileDialog();
    console.log("Done");
}
(() => {
    var _a;
    (_a = document.querySelector('#btn-open-project')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        NewProject();
    });
})();
