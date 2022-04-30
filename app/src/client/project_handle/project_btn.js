"use strict";
(() => {
    var _a, _b, _c;
    (_a = document.querySelector('#back-btn')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        window.location.href = '../index.html';
    }),
        (_b = document.querySelector('#sample-proj-btn')) === null || _b === void 0 ? void 0 : _b.addEventListener('click', () => {
        }),
        (_c = document.querySelector('#blank-proj-btn')) === null || _c === void 0 ? void 0 : _c.addEventListener('click', () => {
            api.saveBox();
        });
})();
