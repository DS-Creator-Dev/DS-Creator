/** 
 * Initial script executed when electron starts 
 * running.
*/
import { app, ipcMain, BrowserWindow, ipcRenderer } from "electron";
import { initialize, enable } from '@electron/remote/main'
import { getCurrentWindow } from "@electron/remote";
const { contextBridge } = require('electron')




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
    mainWindow.loadFile("./index.html");
    mainWindow.on("ready-to-show", () => mainWindow.show())
    enable(mainWindow.webContents)

    discordWindow = new BrowserWindow({
        width: 450, height: 300,
        webPreferences: {
            preload: __dirname + "/preload.js"
        },
        show: false
    });
    discordWindow.loadFile("./views/discord.html");
    discordWindow.on("ready-to-show", () => discordWindow.show())
}