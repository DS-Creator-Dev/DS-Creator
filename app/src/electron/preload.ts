import { ipcRenderer, contextBridge } from "electron";
import { dialog } from '@electron/remote'

const { exec } = require('child_process');
let commandOne = 'E:/Repos/DS-Creator/DSTest/AutorunnerTests/A_Autorunner';
let commandTwo = "make";

contextBridge.exposeInMainWorld("api", {
    showOpenFileDialog: () => dialog.showOpenDialogSync({
        properties: ["openFile"],
        filters: [
            {
                name: "DSC Projects",
                extensions: ["DSCProj"],
            },
        ],
    }),
    OpenCmd: () => exec(`cd ${commandOne} && make`, (error : any, stdout : any, stderr : any) => {
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