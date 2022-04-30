// Import the necessary Electron components.
const contextBridge = require('electron').contextBridge;
const ipcRenderer = require('electron').ipcRenderer;
const { exec } = require('child_process');
const { dialog } = require('electron');
const fs = require('fs/promises');
const remote_1 = require('@electron/remote');

const nodePath = require("path");

const Store = require('electron-store');
const store = new Store('project');

// White-listed channels.
const ipc = {
    'render': {
        // From render to main.
        'send': [],
        // From main to render.
        'receive': [],
        // From render to main and back again.
        'sendReceive': [
            'getPath',
            'openEmu'
        ]
    }
};

// Exposed protected methods in the render process.
contextBridge.exposeInMainWorld(
    // Allowed 'ipcRenderer' methods.
    'ipcRender', {
        // From render to main.
        send: (channel, args) => {
            let validChannels = ipc.render.send;
            if (validChannels.includes(channel)) {
                ipcRenderer.send(channel, args);
            }
        },
        // From main to render.
        receive: (channel, listener) => {
            let validChannels = ipc.render.receive;
            if (validChannels.includes(channel)) {
                // Deliberately strip event as it includes `sender`.
                ipcRenderer.on(channel, (event, ...args) => listener(...args));
            }
        },
        // From render to main and back again.
        invoke: (channel, args) => {
            let validChannels = ipc.render.sendReceive;
            if (validChannels.includes(channel)) {
                return ipcRenderer.invoke(channel, args);
            }
        }
    }
);

contextBridge.exposeInMainWorld("api", {
    OpenCmd: (path, isPlay) => exec(`cd ${path} && make && exit`, (error, stdout, stderr) => {
        if (error) {
            console.log(`error: ${error.message}`);
            document.getElementById('Console-Text').textContent = error.message;
            return;
        }
        if (stderr) {
            console.log(`stderr: ${stderr}`);
            return;
        }
        console.log(`Output: ${stdout}`);
        if(!error){
            document.getElementById('Console-Text').textContent = stdout;
        }
        if(isPlay){
            ipcRenderer.invoke('openEmu')
                .then((ROM) => {
                    localStorage.setItem('ROMPath', localStorage.getItem('ProjectDir') + "\\" + localStorage.getItem('ProjectFileName') + '.nds');
                    console.log(localStorage.getItem('ROMPath'));
                });
        }
    }),
    SaveProject: () => void(() => {
        localStorage.setItem('Contents', "No");
        console.log("\nFile Contents of file before append:",
        fs.readFile(localStorage.getItem('ProjectFile'), "utf8"));
  
        fs.appendFile(localStorage.getItem('ProjectFile'), "World", (err) => {
        if (err) {
            console.log(err);
        }
        else {
            console.log("\nFile Contents of file after append:",
            fs.readFile(localStorage.getItem('ProjectFile'), "utf8"));
        }
    });
    })(),
    Settings: () => void(() => {
        console.log('Settings');
    })(),
    GetPaths: (filePath) => void(() => {
        //Sets the localStorage
        localStorage.setItem('ProjectFile', filePath)
        localStorage.setItem('ProjectDir', store.get('ProjectDir'));
        localStorage.setItem('ProjectFileName', nodePath.parse(filePath).name);
        console.log("Done Setting localStorage!")
    })(),
    saveBox: () => void(() => {
        dialog.showSaveDialog(window, options, (path) => {
            console.log(path);
          });
    })
});