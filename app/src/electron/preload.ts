import { ipcRenderer, contextBridge } from "electron";
import { dialog } from '@electron/remote'

const { exec } = require('child_process');

contextBridge.exposeInMainWorld("api", {
    showOpenFileDialog: () => dialog.showOpenDialogSync({
        title: "Open Your Project File",
        properties: ["openFile"],
        filters: [
            {
                name: "DSC Projects",
                extensions: ["DSCProj"],
            },
        ],
    }),
    showOpenDirDialog: (path: string) => dialog.showOpenDialogSync({
        title: "Open Folder of Your Project",
        properties: ["openDirectory"],
    }),
    OpenCmd: (path: string) => exec(`cd ${path} && make`, (error : any, stdout : any, stderr : any) => {
        if (error) {
            console.log(`error: ${
                error.message
            }`);
            return;
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
            return;
        }
        console.log(`Output: ${stdout}`);
    })
});