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
    mainWindow.loadFile("./index.html");
    mainWindow.on("ready-to-show", () => mainWindow.show())


    discordWindow = new BrowserWindow({
        width: 450, height: 300,
        webPreferences: {
            preload: __dirname + "/preload.js"
        },
        show: false
    });
    discordWindow.loadFile("./html/discord.html");
    discordWindow.on("ready-to-show", () => discordWindow.show())
}

/*
const btn = document.querySelector("button");
btn.addEventListener("click", function () {
    NewProject()
});

function NewProject() : void{
    const files = dialog.showOpenDialogSync({
        properties: ["openFile"],
        filters: [
          {
            name: "Projects",
            extensions: ["DSCProj"],
          },
        ],
    });
}
*/