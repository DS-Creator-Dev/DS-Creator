"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const electron_1 = require("electron");
const remote_1 = require("@electron/remote");
electron_1.contextBridge.exposeInMainWorld("api", {
    showOpenFileDialog: () => remote_1.dialog.showOpenDialogSync({
        properties: ["openFile"],
        filters: [
            {
                name: "DSC Projects",
                extensions: ["DSCProj"],
            },
        ],
    })
});
