"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
/**
 * Initial script executed when electron starts
 * running.
*/
const electron_1 = require("electron");
const main_1 = require("@electron/remote/main");
const { contextBridge } = require('electron');
(0, main_1.initialize)();
let mainWindow;
let sceneWindow;
let collisonBoxEditorWindow;
let playWindow;
let discordWindow;
electron_1.app.on("ready", createWindows);
function createWindows() {
    mainWindow = new electron_1.BrowserWindow({
        width: 900, height: 600,
        webPreferences: {
            preload: __dirname + "/preload.js"
        },
        show: false
    });
    mainWindow.loadFile("./index.html");
    mainWindow.on("ready-to-show", () => mainWindow.show());
    (0, main_1.enable)(mainWindow.webContents);
    discordWindow = new electron_1.BrowserWindow({
        width: 450, height: 300,
        webPreferences: {
            preload: __dirname + "/preload.js"
        },
        show: false
    });
    discordWindow.loadFile("./views/discord.html");
    discordWindow.on("ready-to-show", () => discordWindow.show());
}
