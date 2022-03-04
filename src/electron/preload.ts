import { ipcRenderer, contextBridge } from "electron";
import { dialog } from '@electron/remote'

contextBridge.exposeInMainWorld("api", {
    showOpenFileDialog: () => dialog.showOpenDialogSync({
        properties: ["openFile"],
        filters: [
            {
                name: "DSC Projects",
                extensions: ["DSCProj"],
            },
        ],
    })
});