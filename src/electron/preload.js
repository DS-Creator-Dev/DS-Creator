"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const electron_1 = require("electron");
const remote_1 = require("@electron/remote");
const os_1 = require("os");
electron_1.contextBridge.exposeInMainWorld("api", {
    threads: (0, os_1.cpus)().length,
    showOpenFileDialog: () => remote_1.dialog.showOpenDialogSync({
        properties: ["openFile"],
        filters: [
            {
                name: "Projects",
                extensions: ["DSCProj"],
            },
        ],
    }),
    NewProject: () => ({})
});
