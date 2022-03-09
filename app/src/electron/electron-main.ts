/** 
 * Initial script executed when electron starts 
 * running.
*/
import { app, ipcMain, BrowserWindow, contextBridge } from "electron";
import { initialize, enable } from '@electron/remote/main'
import { getCurrentWindow } from "@electron/remote";



initialize();

let mainWindow: BrowserWindow;
let sceneWindow: BrowserWindow;
let collisonBoxEditorWindow: BrowserWindow;
let playWindow: BrowserWindow;
let discordWindow: BrowserWindow;

app.on("ready", createWindows);

function createWindows(): void {
    mainWindow = new BrowserWindow({
        width: 900, height: 600,
        webPreferences: {
            preload: __dirname + "/preload.js"
        },
        show: false
    });
    mainWindow.loadFile("./app/index.html");
    mainWindow.on("ready-to-show", () => mainWindow.show())
    enable(mainWindow.webContents)

    discordWindow = new BrowserWindow({
        width: 450 * 1.5, height: 300 * 1.5,
        webPreferences: {
            preload: __dirname + "/preload.js"
        },
        show: false
    });
    discordWindow.loadFile("./app/views/discord.html");
    discordWindow.on("ready-to-show", () => discordWindow.show())
}