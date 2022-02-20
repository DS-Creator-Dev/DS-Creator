import {app, ipcMain, BrowserWindow} from "electron";

let mainWindow : BrowserWindow;
let discordWindow : BrowserWindow;

app.on("ready", createWindows);

function createWindows (): void {
    mainWindow = new BrowserWindow({
        width: 900, height: 600,
        webPreferences: {
            preload: __dirname + "/preload.js"
        },
        show: false
    });
    discordWindow = new BrowserWindow({
        width: 900, height: 600,
        webPreferences: {
            preload: __dirname + "/preload.js"
        },
        show: false
    });

    mainWindow.loadFile("./index.html");
    mainWindow.on("ready-to-show", () => mainWindow.show())
    discordWindow.loadFile("./html/discord.html");
    discordWindow.on("ready-to-show", () => discordWindow.show())
}