import { ipcRenderer, contextBridge } from "electron";
import { dialog } from '@electron/remote'

import { cpus } from "os";

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
    })
});