const { app } = require('electron')
const electronBrowserWindow = require('electron').BrowserWindow;
const electronDialog = require('electron').dialog;
const electronIpcMain = require('electron').ipcMain;

const nodePath = require("path");

const Store = require('electron-store');

const store = new Store('project');

let window;

function createMainWindow() {
    const mainWindow = new electronBrowserWindow({
        width: 900,
        height: 600,
        show: false,
        webPreferences: {
            nodeIntegration: false,
            contextIsolation: true,
            preload: nodePath.join(__dirname, 'preload.js')
        }
    });

    mainWindow.loadFile('index.html')
        .then(() => { mainWindow.show(); });

    return mainWindow;
}

function createDiscordWindow() {
    const discordWindow = new electronBrowserWindow({
        width: 450 * 1.5, 
        height: 300 * 1.5,
        show: false,
        webPreferences: {
            nodeIntegration: false,
            contextIsolation: true,
            preload: nodePath.join(__dirname, 'preload.js')
        }
    });

    discordWindow.loadFile('./views/discord.html')
        .then(() => { discordWindow.show(); });

    return discordWindow;
}

app.on('ready', () => {
    mainWindow = createMainWindow();
    discordWindow = createDiscordWindow();
});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

app.on('activate', () => {
    if (electronBrowserWindow.getAllWindows().length === 0) {
        createWindow();
    }
});

// -----

// Let's listen for a call on the 'getPath' channel
electronIpcMain.handle('getPath', async () => {
    // Dialog options.
    const options = {
        properties: ["openFile"],
        filters: [
            {
                name: "DSC Projects",
                extensions: ["DSCProj"],
            }
        ]
    }

    // When available, return the modified path back to the render thread via IPC
    return await openDialog(mainWindow, options)
        .then((result) => {
            // User cancelled the dialog
            if (result.canceled === true) { return; }

            // Modify and return the path
            let path = result.filePaths[0];
            let modifiedPath = nodePath.parse(path).dir; // Here's the magic.
            console.log(modifiedPath); // Testing

            if(path != null){
                export var path;
                mainWindow.loadFile('./views/projectOpen.html');
            }

            return modifiedPath;
        })
})

// Create an open dialog
function openDialog(parentWindow, options) {
    return electronDialog.showOpenDialog(parentWindow, options)
        .then((result) => { if (result) { return result; } })
        .catch((error) => { console.error('Show open dialog error: ' + error); });
}