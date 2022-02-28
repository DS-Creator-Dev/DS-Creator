import { ipcRenderer, contextBridge } from "electron";
import { dialog } from '@electron/remote'

import { cpus } from "os";
import { NewProject } from './electron-main.js';

contextBridge.exposeInMainWorld("api", {
    threads: cpus().length,
    showOpenFileDialog: () => dialog.showOpenDialogSync({
        properties: ["openFile"],
        filters: [
            {
                name: "Projects",
                extensions: ["DSCProj"],
            },
        ],
    }),
    NewProject: () => ({
        //This is where the function wil go that will load projectNew.html into mainWindow
        //It is being loaded from the bottom of electron-main.ts/electron-main.js
        //As you can see it is giving an error. It needs a "{"
        NewProject();
    })
});
