"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var Events;
let ReloadBtn = document.getElementById("ReloadButton");
ReloadBtn === null || ReloadBtn === void 0 ? void 0 : ReloadBtn.addEventListener('click', () => {
    LoadTheEvents();
});
LoadTheEvents();
function LoadTheEvents() {
    return __awaiter(this, void 0, void 0, function* () {
        Events = undefined;
        yield api.GetAppPath();
        yield api.LoadEvents();
        setTimeout(function () {
            //@ts-expect-error
            Events = JSON.parse(localStorage.getItem("Events"));
        }, 1000);
    });
}
;
