"use strict";
function OpenProject() {
    const file = api.showOpenFileDialog();
    console.log("Done");
    if (file != null) {
        location.href = './views/projectOpen.html';
    }
}
//NewProject() is no longer needed.
//Note to self. Remove these comments after this commit.
(() => {
    var _a;
    (_a = document.querySelector('#btn-open-project')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        OpenProject();
    });
})();
