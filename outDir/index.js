"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const electron_1 = require("electron");
let mainWindow;
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
    discordWindow = new electron_1.BrowserWindow({
        width: 450, height: 300,
        webPreferences: {
            preload: __dirname + "/preload.js"
        },
        show: false
    });
    discordWindow.loadFile("./html/discord.html");
    discordWindow.on("ready-to-show", () => discordWindow.show());
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
