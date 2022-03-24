"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const electron_1 = require("electron");
const remote_1 = require("@electron/remote");
const { exec } = require('child_process');
electron_1.contextBridge.exposeInMainWorld("api", {
    showOpenFileDialog: () => remote_1.dialog.showOpenDialogSync({
        properties: ["openFile"],
        filters: [
            {
                name: "DSC Projects",
                extensions: ["DSCProj"],
            },
        ],
    }),
    OpenCmd: (path) => exec(`cd ${path} && make`, (error, stdout, stderr) => {
        if (error) {
            console.log(`error: ${error.message}`);
            return;
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
            return;
        }
        console.log(`Output: ${stdout}`);
    })
});
